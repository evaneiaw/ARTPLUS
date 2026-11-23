---
modulo: DocumentMarks.dll
funcao: DocumentMarks::PDFPlusBearerBar::regenerateMarkImp
endereco: 0x18012F6E0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x180132A70
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18012F6E0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180132A70`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18012F6E0`
- simbolo: `DocumentMarks::PDFPlusBearerBar::regenerateMarkImp`
- assinatura: `void regenerateMarkImp(PDFPlusBearerBar * this)`
- corpo: `0x18012F6E0`..`0x180130003` (2340 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180132A70`

## O que faz

Pipeline de geracao PDF+ (corpo de 2340 bytes): UpdateDirection -> ValidateAnchors -> UpdateSizeReference, limpeza do conteudo gerado, montagem do grupo (Group com mascara 0x1FF) e do Expander, transformacao com guarda de 0.01 mm, insercao no topo do conteudo e ApplyPDFPlusColor. Nao referencia strings.

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (28):

- `18006e460 DocumentMarks::DynamicMark::ApplyPDFPlusColor`
- `18012e7d0 DocumentMarks::PDFPlusBearerBar::UpdateDirection`
- `18012d960 FUN_18012d960`
- `180016510 FUN_180016510`
- `EXTERNAL:000000cc DOCUMENTEDIT.DLL::DocumentEdit::Expander::~Expander`
- `EXTERNAL:000000ce DOCUMENTEDIT.DLL::DocumentEdit::Delete`
- `EXTERNAL:00000246 DOCUMENT.DLL::ArtDoc::Transformable::SetTransformation`
- `EXTERNAL:000004af YAGL.DLL::YAGL::ToHorizontal`
- `180071630 DocumentMarks::DynamicMark::GetSourceContent`
- `18012db30 FUN_18012db30`
- ... mais 18 no bruto

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* protected: virtual void __cdecl DocumentMarks::PDFPlusBearerBar::regenerateMarkImp(void) __ptr64
    */

void __thiscall DocumentMarks::PDFPlusBearerBar::regenerateMarkImp(PDFPlusBearerBar *this)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined4 uVar5;
  double dVar6;
/* ... 344 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012F6E0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
