---
modulo: DocumentMarks.dll
funcao: "ID historico da v25; equivalente v240 = DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog em 0x180245380"
endereco: 0x18024E9B0
versao: 24.03.10017
confianca: alta
xrefs: ['0x180245380']
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Registro de ID - `0x18024E9B0` (ID historico da v250 citado pela spec F-002)

## Resultado neste binario (v24.03.10017)

- `isFunctionEntry=false` em `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
  (sha256 `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`).
- O endereco cai dentro de outra funcao na v240 (ver `containingFunction` no bruto).
- Origem do ID: tabela de exports do `DocumentMarks.dll` de instalacao historica
  (dump em `rag/evidence/F-006/exports.txt`), ordinal 939, onde o VA `0x18024E9B0`
  corresponde ao simbolo exportado
  `?CopyMarksToPageWithLog@TaskMarkSets@DocumentMarks@@QEAAXAEAVPage@ArtDoc@@0_N@Z`.

## Equivalente v240

- funcao: **DocumentMarks::TaskMarkSets::CopyMarksToPageWithLog**
- endereco: **0x180245380** (entrada de funcao confirmada na v240)
- analise real: `DocumentMarks__0x180245380.md`

## Por que este arquivo existe

O ID foi escrito na spec F-002 a partir do layout historico. Ele **nao** identifica
funcao na v24.03.10017, versao de referencia do projeto. A equivalencia foi
estabelecida pelo nome exportado (mesmo simbolo C++ demangled) e confirmada pela
assinatura e pelo corpo da funcao v240.

## Confianca

`alta` para o deslocamento de endereco (export historico com o mesmo simbolo; funcao
v240
localizada por simbolo e conferida por assinatura). Nenhuma conclusao de comportamento
deve ser lida deste arquivo: use o equivalente v240.

## Fonte

- bruto: `rag/evidence/F-002/ghidra/raw_v240/_probe.txt`
- tabela de exports historica: `rag/evidence/F-006/exports.txt`
- script: `tools/ghidra_analysis/scripts/F002MarkSetProbe.java`
