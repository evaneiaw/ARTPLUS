# ADR-015 — Trapping (F-010)

## Contexto

A spec `docs/features/F-010.md` (status `spec`, confiança `media`) descreve a funcionalidade Trapping
no módulo PDFObjectLayer.dll v24.03.10017. O checkbox "Trapping" na toolbar alterna o estado de trapping do
documento; não existe diálogo de parâmetros (largura, choke, spread). A evidência estática sustenta sete funções
GHIDRA em PDFObjectLayer.dll (`GetInfoDictTrappedFlag`, `SetTrappedFlag`, `GetXMPTrappedFlag`, `GetInfoDictTrappedFlagValue`,
`SetInfoDictTrappedFlagValue`) e a classe `GOAnnotTrapNet`; a evidência comportamental `CAP-20261127-01` confirma o checkbox
e a ausência de interface de parâmetros. As flags são gravadas no dicionário Info do documento e/ou metadados XMP; a
anotação GOAnnotTrapNet pode ser adicionada ao documento como objeto de anotação PDF.

## Decisão

### D1 — Onde a funcionalidade vive: `TrappingFlag` + `TrappingManager` em `src/prepress/trapping_flag.h/.cpp`

Nova unidade `src/prepress/trapping_flag.h/.cpp` com duas classes, em conformidade com o módulo
`prepress` (trapping é responsabilidade da camada prepress por `docs/architecture/DocumentMarks.md`):

- `struct TrappingFlag` — valor booleano `trapped` com procedência (`Source::Default`,
  `Source::InfoDict`, `Source::Xmp`) e tokens de persistência para roundtrip.
- `class TrappingManager` — dono do estado de trapping de um `Document`, criação/toggling, sincronização
  com metadados do documento e gravação em PDF Info dict / XMP.
- `class TrappingToggleCommand : public Command` — uma ação de undo por alteração de estado.

**Não** se estende o `TrappingEngine` existente em `src/prepress/trapping.*`:

1. `TrappingEngine` é um motor de geometria (spread/choke) com `Settings`, `TrapZone`, `Result` — é um
   engine de cálculo de trapagem de objetos, enquanto F-010 trata apenas do flag binário de estado do
   documento; as responsabilidades são disjuntas (geometria vs. metadado).
2. `TrappingEngine` é um stub (`calculateTraps` devolve success=true, vazio) e não tem estado observável
   no checkbox; estendê-lo introduziria acoplamento desnecessário entre estado de flag e cálculo de
   contorno.
3. O flag toggle não gera geometria, não tem parâmetros de width/choke/spread, e sua persistência
   (`Info dict` + `XMP`) é distinta da geometria de trap zones.

O que é reutilizado do existente:

- `Document`/`Page`/`PageBoxes`/`PageBoxType`, `GroupObject` + `PathObject`, `Color`/`FillStroke`,
  `Command`/`UndoStack`, `Document::metadata()`/`setMetadata()` (ja existe em `document_model.h:431-433`,
  usado por `CutMarkManager`/`BearerBarManager`), e o padrão `setUndoStack(UndoStack*)`.
- O protocolo de persistência `.artplus` via metadados (`root["metadata"]`) herdado de F-001/F-003.

### D2 — Modelo de parâmetros v1

```cpp
struct TrappingFlag {
    bool trapped = false;                // estado efetivo do documento
    enum class Source { Default, InfoDict, Xmp };
    Source source = Source::Default;     // onde o valor foi definido
    QString infoDictToken;               // token bruto lido do dicionário Info
    QString xmpToken;                    // token bruto lido dos metadados XMP
};
```

Regras do modelo:

- **Default**: ao abrir novo documento, `trapped = false`, `source = Default`, tokens vazios.
- **Unidade explícita**: flag booleana; não há parâmetros numéricos (largura/choke/spread) expostos,
  em linha com spec R5 "não há parâmetros de trapping observáveis".
- **Proveniência (`source`)**: registra se a flag veio do dicionário Info do PDF, metadados XMP, ou está
  no valor default. Isso garante fidelidade em save/load roundtrips.
- **Tokens (`infoDictToken`, `xmpToken`)**: stringas brutas lidas/escritas para preservar a fonte;
  ao gravar, prioriza XMP se presente, senão Info dict.

### D3 — Integração com Documento

- `TrappingManager` recebe `Document&` no ctor; o estado é armazenado como chave `Trapping`
  dentro do `metadata` existente do documento (`QJsonObject`), sem necessidade de adicionar
  novos campos a `Document` (reutiliza contrato já aprovado em F-001/F-003).
- **Importação PDF**: ao abrir PDF, o módulo `src/pdf` lê as strings `/Trapped` do dicionário Info
  e o token XMP `pdf:Trapped` (se houver) e chama `TrappingManager::loadFromPdfTokens(bool fromInfo,
  bool fromXmp)`. O manager grava o resultado em `metadata["Trapping"]` e atualiza `source`/`tokens`.
- **Exportação PDF**: ao salvar, o módulo `src/pdf` lê `metadata["Trapping"]` e grava `/Trapped`
  no dicionário Info e o token XMP `pdf:Trapped`, chamando `TrappingManager::saveToPdfTokens()`.
- **Interface UI**: o checkbox "Trapping" na toolbar está ligado a `TrappingManager::isTrapped()` /
  `TrappingManager::setTrapped(bool)`. O clique alterna o estado e empilha `TrappingToggleCommand`
  no undo stack se presente.

### D4 — Contrato de interface (API mínima)

```cpp
class TrappingFlag {
public:
    bool trapped() const;
    TrappingFlag::Source source() const;
    QString infoDictToken() const;
    QString xmpToken() const;
    void setTrapped(bool);          // grava; agenda undo se stack presente
private:
    bool m_trapped = false;
    Source m_source = Source::Default;
    QString m_infoDictToken;
    QString m_xmpToken;
};

class TrappingManager {
public:
    explicit TrappingManager(Document& document);
    void setUndoStack(UndoStack* stack);
    bool isTrapped() const;
    void setTrapped(bool trapped);          // UMA ação de undo

    // Sincronização com PDF (chamado por src/pdf)
    void loadFromPdfTokens(bool fromInfo, bool fromXmp, const QString& infoToken,
                          const QString& xmpToken);
    void saveToPdfTokens(QString& infoToken, QString& xmpToken) const;

    // Persistência .artplus via Document metadata
    QJsonObject toMetadata() const;
    bool loadFromMetadata(const QJsonObject& json);
private:
    Document* m_document = nullptr;
    UndoStack* m_undoStack = nullptr;
    TrappingFlag m_flag;
};
```

## Consequências

### O que pode ser implementado (v1)

- Checkbox "Trapping" na toolbar alterna estado gravável do documento.
- Estado persistente em `.artplus` metadados (`metadata["Trapping"]`).
- Leitura de flag ao abrir PDF: Info dict `/Trapped` + XMP `pdf:Trapped`.
- Escrita ao salvar PDF: Info dict + XMP atualizados.
- Undo único por toggle (via `TrappingToggleCommand`).
- Integração mínima: nenhum novo campo em `Document` core; reutiliza `metadata()` existente.
- Evidência comportamental `CAP-20261127-01` replicada: checkbox existe, sem diálogo.

### O que fica fora do escopo v1 (não implementado)

- Geometria de trap (spread, choke, centerline) — fica para feature futura (possivelmente F-010a ou
  módulo `TrappingEngine` aprofundado).
- Diálogo de parâmetros de trap (largura, offset, extend, location mask, direction, sizeReference,
  color) — spec F-010 §3 afirma expressamente "não existe diálogo de parâmetros".
- Animação visual de linhas de trap — sem renderização de contornos de trap na GUI.
- Menu `Prepress > Trapping` com parâmetros — dropdown custom-drawn, não acessível via UI Automation;
  pode ser abordado em feature de painel/inspector separado.
- Efeito visual de sobreposição de trap na renderização — dependente de engine de trap geometry,
  fora de v1.
- Suporte a documentos sem DeviceN/NChannel — flag toggle funciona, mas efeito observável requer
  espaço de cores compatível (spec R9 "se documento não tiver suporte a trap, checkbox alterna estado
  mas não produz efeito visual").

### Riscos e limitações

- **Risco de perdas em roundtrip**: se um documento tiver flag definida via XMP mas sem Info dict `/Trapped`,
  ou vice-versa, a leitura pode sobrescrever um token ao gravar. O `source` e os `tokens` mitigam isso,
  mas a prioridade (XMP sobre Info) é uma decisão declarada.
- **Contrato que atravessa módulos**: `TrappingManager` lê/escreve `metadata["Trapping"]` (já existente)
  e chama `src/pdf` para gravação de Info/XMP. Isso atravessa os módulos `prepress` ↔ `pdf`; exige
  revisão do orquestrador antes da fase `implementacao` (AGENTS.md §6.8).
- **Undo identidade do grupo**: se houver outras marcas dinâmicas (CutMark, BearerBar) no mesmo
  documento, a identidade do grupo (`m_groupId`) pode mudar após undo/redo, documento que
  `TrappingManager` reindexa; limitação aceitável em v1, documentada.
- **Documentos sem DeviceN**: flag toggle opera, mas efeito visual de trap requer espaços de cor
  compatíveis; especificar limitação na UI (checkbox desabilitado ou dica contextual quando não houver
  suporte a trap) é decisão de UI, não deste ADR.

## Estado

aprovado

## Próximos passos para implementação

1. Criar `src/prepress/trapping_flag.h` e `src/prepress/trapping_flag.cpp` com `TrappingFlag`,
   `TrappingManager`, `TrappingToggleCommand`.
2. Integrar `TrappingManager` ao `Document` via metadados `metadata["Trapping"]` (sem alterar headers
   existentes de `Document`).
3. Atualizar `src/pdf/pdf_importer.cpp` e `src/pdf/pdf_exporter.cpp` para ler/gravar flags Info dict
   `/Trapped` e XMP `pdf:Trapped` usando o protocolo `TrappingManager::loadFromPdfTokens` / `saveToPdfTokens`.
4. Ligar o checkbox "Trapping" na toolbar (coord x=1271, y=47) a `TrappingManager::isTrapped()` /
   `setTrapped(bool)`; empilhar `TrappingToggleCommand` no undo stack.
5. Compilar incremental e validar com `python scripts/gate.py --feature F-010 --stage code` (rc 0).
6. Redigir especificação de teste unitário para `TrappingManager` (entra em fase `testes`).
7. Registrar laudo de auditoria `docs/audit/F-010-audit.md` após primeira build bem-sucedida.

## Mapeamento binário → ArtPlus

| Função (Ghidra / endereço) | Classe/método ArtPlus | Observação |
|---|---|---|
| `0x18001bf40` (`FUN_18001be70`) | `TrappingManager::loadFromPdfTokens` | strings referenciadas: `?GetInfoDictTrappedFlag@GODocument@@`; leitura do dicionário Info do documento |
| `0x18001bf80` (`GetClassType__18001bf80`) | `GOAnnotTrapNet` RTTI | classe de anotação de rede de trap; RTTI presente confirmado |
| `0x1800f4ce0` (`FUN_1800f4b50`) | `TrappingManager::saveToPdfTokens` | funções de valor de flag: `?GetInfoDictTrappedFlagValue@GODocument@@` / `?SetInfoDictTrappedFlagValue@GODocument@@` |
| `0x180062ee0` (`GetRequirement__180062ee0`) | `TrappingManager::isTrapped` / validação | verifica requisitos de trap do documento (DeviceN/NChannel) |
| `0x180069de0` (`SetProperty_Int64__180069de0`) | `TrappingManager::saveToPdfTokens` — escrita XMP | escrita de metadados XMP `pdf:Trapped` |
| `0x18005fd00` (`FUN_18005fbd0__18005fd00`) | `TrappingManager::loadFromPdfTokens` — leitura interna | processamento interno após importação PDF |
| `0x18005fd70` (`GetIndexForPage__18005fd70`) | `TrappingManager::pageOf` | indexação de páginas para sincronização de estado |
| `CAP-20261127-01` | checkbox toolbar "Trapping"; toggle sem diálogo | evidência comportamental; confirma ausência de parâmetros UI |

## Referências cruzadas

- Spec: `docs/features/F-010.md` (status: spec, confiança: media)
- Evidência: `rag/evidence/F-010/` (7 IDs GHIDRA + CAP-20261127-01)
- ADRs anteriores: `ADR-001-cut-mark.md`, `ADR-002-bearer-bar.md`
- Módulo: `src/prepress/trapping_flag.h/.cpp` (nova)
- Integração: `src/document/document_model.h` (metadata já existente), `src/pdf/` (importador/exportador)
- Pipeline: ghidra → documentação → F-010 → arquitetura → ADR → implementacao → testes → auditor