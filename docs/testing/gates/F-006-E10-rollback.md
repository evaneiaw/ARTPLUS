# F-006 — E10 + needBackupOnSave (rollback) — mecanismo de teste

Alvo: `DocumentSaveManager::save` com `needBackupOnSave=true` e `isIncrementalSave=false`
(backup por **rename**, R3.4) quando `DocumentSerializer::save` falha.

Testes em `tests/unit/test_save_document.cpp`:

- `testE10NeedBackupRollbackRestoresOriginalOnSerializerFailure` (ramo de rollback bem-sucedido)
- `testE10IncrementalBackupDoesNotRollbackNorDeleteDestination` (ramo de backup incremental)

## Como a falha do serializer é forçada DEPOIS do rename

`DocumentSerializer::save` só devolve `false` em `QFile::open(QIODevice::WriteOnly)`
(`src/document/document_serializer.cpp:463`). Logo, o cenário exige que o **rename
`<dest>` → `<dest>.bak` já tenha ocorrido** e que a **criação/abertura do destino falhe**.

O `DocumentSaveManager` emite `progressStatus("STATUS_SAVE")` de forma **síncrona, na
mesma thread**, imediatamente antes de chamar o serializer e depois do bloco R3
(`src/document/document_save_manager.cpp:117`). O teste conecta um slot nesse sinal:

1. confirma que o destino **não existe mais** e que `<dest>.bak` existe
   (prova de que o rename R3.4 aconteceu antes da falha);
2. cria um arquivo *placeholder* no destino;
3. nega `FILE_WRITE_DATA` (`WD`) ao usuário atual no placeholder:
   `icacls <placeholder> /deny "<DOMINIO\usuario>:(WD)"`;
4. verifica a injeção de forma real: `QFile::open(QIODevice::WriteOnly)` **tem que falhar**.

Como `DELETE` não é negado, o rollback do manager consegue `QFile::remove(placeholder)`
e `QFile::rename(<dest>.bak → <dest>)`, exercitando o ramo de rollback bem-sucedido
(`backupPath` vazio, mensagem "…restaurado…"). Não há `sleep`, timer ou corrida: o sinal
é síncrono.

## Semântica verificada no ambiente (Windows 11, usuário proprietário do diretório temp)

| Operação no arquivo com ACE `DENY(WD)` | Resultado |
|---|---|
| `QFile::open(WriteOnly)` / `CreateFile(GENERIC_WRITE)` | falha (access denied) |
| `DeleteFile` (usado por `QFile::remove`) | sucesso (DELETE continua concedido) |

Descartado: negar `(AD)` no diretório — na prática bloqueia criação de **subdiretórios**,
não de arquivos (sonda: criação de arquivo continuou OK). Negar `(WD)` no diretório
também bloqueia o **rename** do backup, o que impediria o cenário (não há separação
possível entre rename e criação por ACL de diretório). Negar `WD` apenas no arquivo de
destino é o que separa as duas operações.

## Condicionalidade declarada

Se `icacls` não existir/não puder aplicar o ACE, ou se a escrita **não** ficar bloqueada
(verificado por tentativa real de `open`), os dois testes terminam em `QSKIP` com
mensagem explícita — nunca em verde vazio. No ambiente atual os dois testes **executam
e passam** (`28 passed, 0 failed, 0 skipped` na suíte `SaveDocumentTests`).

## Cobertura por teste

`testE10NeedBackupRollbackRestoresOriginalOnSerializerFailure` afirma:
`ok == false`, `errorCode == 8`, `errorMessage` não vazia e contendo "restaurado"
(sem "rollback do backup falhou"), `backupPath` **vazio**, destino **existe** com
bytes e SHA-256 iguais ao original, **nenhum `.bak` remanescente**, `doc.filePath()`
inalterado e `doc.modified() == true` (documento não corrompido nem marcado como salvo).

`testE10IncrementalBackupDoesNotRollbackNorDeleteDestination` afirma:
`ok == false`, `errorCode == 8`, `backupPath == <dest>.bak`, `.bak` preservado com os
bytes/SHA originais, destino **nunca apagado** pelo caminho de falha (segue sendo o
placeholder), `doc.modified() == true`.
