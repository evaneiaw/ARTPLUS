# Reconciliação de manifests F-006 / F-007 (v24.03.10017)

**Data:** 2026-11-24  
**Agente:** `rea`  
**Escopo:** metadados de evidência (`rag/evidence/F-006/manifest.json`, `rag/evidence/F-007/manifest.json`)
e capturas brutas de DIE. Nenhum arquivo de `src/`, `tests/`, `docs/features/` ou `docs/decisions/` foi tocado.

Referência única: **Esko ArtPro+ 24.03.10017**, em
`C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows`.

---

## 1. F-006 — Save Document (Document.dll)

### Estado anterior (incorreto)

| Campo | Valor anterior | Problema |
|---|---|---|
| `sha256` | `DA91E285...9E21` | já coincidia com o binário real (mantido) |
| `tamanho` | `4922408` | não corresponde ao arquivo-alvo (4421040) |
| `compiler` / `linker` / `tool` | `19.41.34435` / `14.41.34435` / VS 2022 17.11 | de outro build; DIE do binário real reporta 19.38.33134 / 14.38.33134 / VS 2022 17.8 |
| `imports_critical` | `"Document.dll (732), DocumentEdit.dll (66), ..."` | Document.dll listando a si mesma como import — lido de outro módulo |
| `exports_critical` | `"2268 exports ..."` | não reverificado para este binário |
| `estatico[]` | `GHIDRA-Document-0x...`, `GHIDRA-PDFAccessLayer-0x...`, `GHIDRA-PDFObjectLayer-0x...` | placeholders; nenhum resolve; módulos inexistentes em `ghidra/` |
| `bloqueios[]` | vazio | GUI v24 sem captura de Save |

A origem do desvio está em `rag/sources/Document.die.json`, que antes continha `"size": "4447272"`,
linker `14.41.34435`, compilador `19.41.34435` e VS `17.11` — ou seja, outro build/arquivo.
O arquivo foi regravado com a saída atual de `diec -j` sobre o binário-alvo.

### Binário conferido

```
C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\Document.dll
SHA-256 : DA91E28574C877D392D3E6BEF9CCBB7C4DCF3117EBD03655DE89834FC8FA9E21
Tamanho : 4421040 bytes
Get-FileHash -Algorithm SHA256  ->  coincidiu com o manifest (sem alteração de hash)
```

DIE (v240): PE32+, Microsoft Visual C/C++ (19.38.33134) [C++], Microsoft Linker (14.38.33134),
Microsoft Visual Studio (2022, 17.8), runtime C/C++ dinâmico, Authenticode PKCS #7 (2.0),
debug data POGO. 9 seções reais: `.text`, `.textidx`, `.rdata`, `.data`, `.pdata`, `.fnp_dir`,
`.fnp_mar`, `.rsrc`, `.reloc` (as 6 seções do manifest antigo não existem neste arquivo).

### `estatico[]` corrigido — 21 IDs, todos resolvendo para arquivo existente

Document (11): `0x180016730`, `0x180099690`, `0x180099710`, `0x1800a20e0`, `0x1800a2110`,
`0x18013f240`, `0x1801954e0`, `0x180195c10`, `0x18023b8e0`, `0x1802ad561` (Save),
`0x1802ad5eb`.

NDLModel (10): `0x1800208f0`, `0x180020920`, `0x180021990` (SaveDocument), `0x1800428b0`,
`0x180042900`, `0x180042a40`, `0x180042b80`, `0x180042bb0`, `0x18004b420`, `0x1800508d0`.

Cada ID foi conferido contra os nomes de arquivo em `rag/evidence/F-006/ghidra/` — nenhum
placeholder, nenhuma referência a `PDFAccessLayer`/`PDFObjectLayer`.

Os cinco arquivos `DocumentMarks__*.md` ainda presentes em `rag/evidence/F-006/ghidra/`
(`CutMark`, `GradationMark_ColorBar`, `updatePdfPropertiesDictImp_BarcodeMark`,
`updatePdfPropertiesDictImp_BearerBar`, `wrapMarkSelection`, `versao: 25.0`) são evidência
histórica de outro módulo. Foram **preservados**, mas ficam fora de `estatico[]`.

### Bloqueio registrado

- `CAP-BLOCKED-006`: fluxo Save na GUI v24.03.10017 não capturado (GUI inativa);
  `rag/evidence/F-006/behavior/` vazio.
- `BLO-005`: build/testes e criptografia de Save Document em aberto (`docs/agents/BLOQUEIOS.md`).

---

## 2. F-007 — Step & Repeat (LayoutEngine.dll)

### Binário conferido

```
C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\LayoutEngine.dll
SHA-256 : 7BB0ACD6CFE3AC669CBCCD4B99A634687F0B660608A244070FEEED15016497A5
Tamanho : 533424 bytes
Get-FileHash -Algorithm SHA256  ->  coincidiu com o manifest (sem alteração de hash)
```

DIE: MSVC 19.38.33134 (VS 2022 17.8), linker 14.38.33134, PE64 assinado (PKCS #7) — igual
ao que o manifest já declarava. Captura bruta nova em `rag/sources/LayoutEngine.die.json`.

### Correções

- `versao_ref`: `"24.0"` → `"24.03.10017"`.
- `bloqueios[]`: `[]` → `BLO-003` (sem CAP da v24; a UI v24 não produziu fluxo de Step & Repeat;
  `rag/evidence/F-007/behavior/` vazio).
- `comportamental[]`: mantido `[]`.
- `estatico[]`: 10 IDs mantidos (`0x180013d00`, `0x18002d570`, `0x18001d5a0`, `0x180028490`,
  `0x180022600`, `0x18000c1f0`, `0x180025820`, `0x1800261f0`, `0x18002d610`, `0x180009fc0`),
  todos resolvendo para os 10 arquivos `LayoutEngine__*.md` existentes.

### Correções em `versao:` dos arquivos de evidência

Os 31 arquivos `.md` de evidência de F-006/F-007 (11 `Document__*`, 10 `NDLModel__*`,
10 `LayoutEngine__*`) tinham `versao: 24.03.10017.10017`. O campo foi normalizado para
`versao: 24.03.10017`. Nenhum conteúdo técnico (assinatura, xrefs, pseudocódigo) foi alterado.
Os `DocumentMarks__*.md` (`versao: 25.0`) não foram tocados.

`docs/reverse-engineering/LayoutEngine_GHIDRA.md` linha 4: `**Versão de referência:** 24.0`
→ `24.03.10017` (substituição restrita à sequência ASCII, sem reescrever o arquivo, que
contém bytes não-UTF-8 legados).

---

## 3. Resultado do gate

```
python scripts/gate.py --feature F-006 --stage evidence   -> exit 1
python scripts/gate.py --feature F-007 --stage evidence   -> exit 1
```

O que **passa** agora (conferido por script equivalente a `manifest_errors`):

- `GATE 0 versão`: `ok` nos dois casos.
- `versao_ref == "24.03.10017"` nos dois manifests.
- `sha256` do manifest == hash recalculado do binário real (F-006 e F-007).
- `estatico[]`: 21/21 (F-006) e 10/10 (F-007) IDs resolvem para arquivo em `ghidra/`;
  sem placeholder `0x...`.
- Sem erro de "sha256 não confere", "binário inexistente", "id estático inválido"
  ou "evidência estática não resolve".

O que **continua reprovado** (GATE 3, `estágio evidence`):

1. `nenhuma evidência comportamental válida` — esperado: F-006 e F-007 estão bloqueadas
   (`CAP-BLOCKED-006`, `BLO-003`) e `comportamental[]` é vazio por contrato.
2. Formato dos arquivos de evidência (defeito pré-existente, **não** do manifest):
   - F-006: os 21 `.md` abrem com um título `# ...` seguido de bloco ```yaml, sem
     frontmatter `---`; o gate exige `---` na primeira linha → 21 × "sem cabeçalho YAML '---'".
   - F-007: os 10 `.md` são YAML puro sem delimitadores `---` e sem campo `confianca:`
     → 10 × "sem cabeçalho YAML '---'" + 10 × "sem campo 'confianca:'".
   Comparação: F-001, F-002, F-003, F-004, F-005 e F-008 usam `---` e passam nessa checagem.

Esses itens 2 são normalização estrutural de arquivo de evidência (dono: `ghidra`).
Não foram alterados aqui além do campo `versao:`, conforme limite de escopo desta triagem.

---

## 4. Arquivos tocados

| Arquivo | Ação |
|---|---|
| `rag/evidence/F-006/manifest.json` | regravado (metadados v240, 21 IDs reais, bloqueios) |
| `rag/evidence/F-007/manifest.json` | regravado (`versao_ref` exato, BLO-003) |
| `rag/sources/Document.die.json` | regravado com `diec -j` do binário v240 |
| `rag/sources/LayoutEngine.die.json` | criado |
| `rag/evidence/F-006/ghidra/{Document,NDLModel}__*.md` (21) | apenas `versao:` normalizado |
| `rag/evidence/F-007/ghidra/LayoutEngine__*.md` (10) | apenas `versao:` normalizado |
| `docs/reverse-engineering/LayoutEngine_GHIDRA.md` | `Versão de referência: 24.0` → `24.03.10017` |

Preservados: os 5 `DocumentMarks__*.md` (25.0) em `rag/evidence/F-006/ghidra/`,
`.writetest`, `enrich_xrefs.ps1`, `test.ps1`, e todos os `behavior/` (vazios).
