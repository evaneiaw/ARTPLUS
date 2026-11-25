# F-006 — regressão D1/E5 (2026-11-24)

Suíte: `SaveDocumentTests` (`tests/unit/test_save_document.cpp`)
Build: `build_f008` (CMake Kitware, preset `mingw-msvcrt`, Release/MinGW POSIX MSVCRT, Qt 6.8.3)
Cenário CTest: `ctest --test-dir build_f008 -R ^SaveDocumentTests$`

## Testes novos

| Teste | Achado coberto | Asserção central | Estado |
|---|---|---|---|
| `testD1aEncryptionGuardRunsBeforeBackup` | D1a (cripto antes do backup) | `ok==false`, `errorCode==0` (E8), destino existente com sha256 inalterado, `backupPath` vazio, nenhum `*.bak` | PASS |
| `testD1bFlavourGuardRunsBeforeBackup` | D1b (flavour antes do backup) | `ok==false`, `errorCode==8` (E9), destino com sha256 inalterado, nenhum `*.bak` | PASS |
| `testE5SaveToNonExistentPathBehavesAsSaveAs` | E5 (destino inexistente ⇒ Save As) | `ok==true`, arquivo criado, `doc.filePath()` atualizado, `modified()==false`, JSON `format=="artplus"` | **FAIL** |
| `testE5BothPathsNonExistentForcesSaveAsNoBackup` | E5 (linha `if (!destinationInfo.exists()) isSaveAs = true`) | `ok==true`, `backupPath` vazio e nenhum `.bak` apesar de `needBackupOnSave=true` | PASS |

## Resultado da execução (2026-11-24 10:13)

```
test_save_document.exe: Totals: 25 passed, 1 failed, 0 skipped, 0 blacklisted
FAIL!  : TestSaveDocument::testE5SaveToNonExistentPathBehavesAsSaveAs() 'r.ok' returned FALSE.
         (save failed: Erro (TODO F-006): O arquivo original não pôde ser copiado para o arquivo de trabalho.)
tests/unit/test_save_document.cpp(406)
```

`ctest --test-dir build_f008`: 10/11 passed, 1 failed (`SaveDocumentTests`) — a única falha é a
asserção E5 acima.

## Causa da falha E5 (src, não corrigível no escopo de `testes`)

`src/document/document_save_manager.cpp:167-178` — `switchToWorkingFile()` devolve `false`
quando `doc_.filePath()` está vazio e `save()` trata isso como E1 (`errorCode = 8`, retorno antes
de qualquer gravação) em `:30-35`.

Consequência: um documento sem `filePath` (nunca salvo) **não** pode ser salvo, e a rota de UI
`src/ui/main_window.cpp:1046-1048` (`saveArtPlus()` sem `filePath` → `saveArtPlusAs()`)
termina sempre em "Save failed: O arquivo original não pôde ser copiado para o arquivo de trabalho".

Contradição registrada: a spec `docs/features/F-006.md:347` afirma "sem `filePath` o primeiro save
é sempre Save As", enquanto `:354-355` declara a simulação de `switchToWorkingFile()`
("devolve `false` apenas quando `doc_.filePath()` está vazio"). Os dois enunciados não podem
ser verdadeiros ao mesmo tempo.

Correção proposta (dono: `implementacao`; **não aplicada** por este agente): tratar o documento
sem original como "nada a copiar" (não é E1) e reservar o estado `this+0x78 == 2` para falha real
de cópia; atualizar `docs/features/F-006.md` §9.1.

## O que a suíte prova e o que não prova

- Prova: os guards de criptografia (E8) e de flavour (E9) retornam **antes** de qualquer
  backup/escrita — nenhum `.bak`, destino byte a byte intacto (sha256 comparado).
- Prova: `isSaveAs` é forçado por destino inexistente (observável: com `needBackupOnSave=true`
  não há derivação de backup).
- Não prova: o fluxo E5 de ponta a ponta para documento **sem** `filePath` (bloqueado pelo E1
  simulado, ver acima).
