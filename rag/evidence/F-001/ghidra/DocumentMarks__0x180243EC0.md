---
modulo: DocumentMarks.dll
versao: 24.03.10017
funcao: 0x180243EC0
endereco: 0x180243EC0
nome: "DocumentMarks::TaskMarkSets::ApplyMarksFromSet"
confianca: alta
xrefs: ["0x180243EB1", "0x1803AAD68"]
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# TaskMarkSets::ApplyMarksFromSet — v24.03.10017

## Identificacao

- Endereco: `0x180243EC0` (corpo `0x180243EC0`–`0x180243F2D`, 109 bytes)
- Assinatura: `bool __thiscall ApplyMarksFromSet(TaskMarkSets *this, const std::vector<std::unique_ptr<ArtDoc::Document>> &documents, ArtDoc::Page &target, bool flag)`
- Chamado por `ApplyExtraMarkSet` (`0x180243EB1`).

## O que a funcao faz

1. Itera o vetor de documentos.
2. Para cada documento, `ArtDoc::Document::GetPagesBegin` pega a **primeira
   pagina**.
3. Chama `TaskMarkSets::CopyMarksToPageWithLog(this, firstPage, target, flag)`.

## Por que sustenta F-001 (Cut Mark)

- Sustenta R13: a aplicacao por mark set copia o conteudo da primeira pagina de
  cada documento para a pagina alvo. Esse fluxo pertence a **F-002 (Mark Sets)**,
  nao a criacao da marca em F-001.
- Confirma que a entrada de marcas por mark set e um caminho separado da criacao
  direta (`Add Cut Mark`).

## Confianca

Alta: fluxo curto e integralmente legivel.
