---
modulo: DocumentMarks.dll
funcao: "DocumentMarks::DynamicMark::Accept"
endereco: 0x18001A340
versao: 24.03.10017
confianca: alta
xrefs: []
strings: []
fonte: "Ghidra 12.2 headless; projeto DocMarks_v240; programa DocumentMarks.dll (v24.03.10017)"
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001A340

## Identificacao lida no programa v240

- endereco: `0x18001a340`
- simbolo: `DocumentMarks::DynamicMark::Accept`
- assinatura: `void __thiscall Accept(VisitorBase * param_1)`
- corpo: `18001a340..18001a3e0`, convencao `__thiscall`, thunk=false, external=false
- parametros: 2
- referencias apontando para a entrada: 4 (DATA/vtable/export; detalhe em `refTo` no bruto)

## O que faz

`DocumentMarks::DynamicMark::Accept(ArtDoc::VisitorBase&)` -- despacho de visitor
virtual de `DynamicMark` (nao tem relacao semantica com Mark Set; este endereco e o unico dos
10 IDs herdados que e entrada de funcao real na v240).

Corpo `0x18001A340`..`0x18001A3E0`:
1. `__RTDynamicCast(param_1, 0, VisitorBase::RTTI, ArtDoc::Visitor<DynamicMark>::RTTI, 0)`.
2. Se o cast falha: `FUN_180013750(&local_res8, this-0x20, param_1)` e, se retornar 0, chama
   o slot `*(*this + 0x20)` (Accept da classe base).
3. Se o cast funciona: chama o primeiro slot do visitor (`(**plVar2)(plVar2)`) e, se retornar
   != 0, tambem o slot `+0x20`; depois chama `(**(plVar2 + 8))(plVar2, this-0x20)`.

Mostra o idioma padrao de double dispatch do ArtDoc: visitor especializado
(`ArtDoc::Visitor<DynamicMark>`) com fallback para o Accept da base.

## Chamadores (xrefs de chamada)

- nenhum chamador interno registrado (funcao de entrada/exportada; ver `refTo` do bruto)

## Chamadas diretas (2)

- `1802ccf7a __RTDynamicCast`
- `180013750 FUN_180013750`

## Strings referenciadas no corpo

- nenhuma (o corpo referencia vftables, dados ou outras funcoes)

## Lacunas

- Nenhuma.

## Confianca

`alta` - endereco, simbolo, assinatura, corpo, xrefs e strings lidos diretamente no programa v240 (Ghidra 12.2 headless, projeto DocMarks_v240). As ressalvas de leitura estao em 'Lacunas'.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- sha256: `E47328BD25B01B6EB36E54D8E5AA5D799F088AFC772D4FE06ED0F14B3C0FA102`
- bruto: `rag/evidence/F-002/ghidra/raw_v240/_detail.txt` e `_decompile_detail.txt`
- script: `tools/ghidra_analysis/scripts/F002DetailProbe.java`
