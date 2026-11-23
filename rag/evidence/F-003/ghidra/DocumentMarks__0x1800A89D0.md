---
modulo: DocumentMarks.dll
funcao: DocumentMarks::SetBearerBarOffset
endereco: 0x1800A89D0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x1800AA3C0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x1800A89D0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x1800AA3C0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x1800A89D0`
- simbolo: `DocumentMarks::SetBearerBarOffset`
- assinatura: `void SetBearerBarOffset(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> * param_2, CoordinateBase<YAGL::MilliPointCoordinateSystem> * param_3)`
- corpo: `0x1800A89D0`..`0x1800A8B38` (361 bytes), convencao `__cdecl`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x1800AA3C0`

## O que faz

Setter transacional de Offset, gemeo do setter de Extend: mesma construcao de std::function + Action + ActionList::DoAction, com o ponteiro de metodo membro 0x8001E750 (relativo 0x1E750). Nao referencia strings.

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (6):

- `1802cbfd0 __security_check_cookie`
- `180016520 FUN_180016520`
- `1802cbe68 FUN_1802cbe68`
- `1800a81c0 FUN_1800a81c0`
- `EXTERNAL:0000027b DOCUMENT.DLL::ArtDoc::Action::GetActionList`
- `EXTERNAL:0000027a DOCUMENT.DLL::ArtDoc::ActionList::DoAction`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetBearerBarOffset(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusBearerBar const & __ptr64)> const &
   __ptr64,class YAGL::CoordinateBase<struct YAGL::MilliPointCoordinateSystem> const & __ptr64) */

void __cdecl
DocumentMarks::SetBearerBarOffset
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> *param_2,
          CoordinateBase<YAGL::MilliPointCoordinateSystem> *param_3)

{
  Action **ppAVar1;
  longlong lVar2;
/* ... 77 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_1800A89D0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
