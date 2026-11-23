---
modulo: DocumentMarks.dll
funcao: DocumentMarks::SetBearerBarSizeReference
endereco: 0x1800A8B40
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x1800AA520
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x1800A8B40

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x1800AA520`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x1800A8B40`
- simbolo: `DocumentMarks::SetBearerBarSizeReference`
- assinatura: `void SetBearerBarSizeReference(Content * param_1, function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> * param_2, SizeReference param_3)`
- corpo: `0x1800A8B40`..`0x1800A8C9F` (352 bytes), convencao `__cdecl`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x1800AA520`

## O que faz

Setter transacional de SizeReference (enum PDFPlusBearerBar::SizeReference): mesma construcao de std::function + Action + ActionList::DoAction, com o ponteiro de metodo membro 0x8012E7C0 (relativo 0x12E7C0, o SetSizeReference citado na nota do ID historico). Nao referencia strings.

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (6):

- `1800a8380 FUN_1800a8380`
- `1802cbfd0 __security_check_cookie`
- `180016520 FUN_180016520`
- `1802cbe68 FUN_1802cbe68`
- `EXTERNAL:0000027b DOCUMENT.DLL::ArtDoc::Action::GetActionList`
- `EXTERNAL:0000027a DOCUMENT.DLL::ArtDoc::ActionList::DoAction`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* void __cdecl DocumentMarks::SetBearerBarSizeReference(class ArtDoc::Content & __ptr64,class
   std::function<bool __cdecl(class DocumentMarks::PDFPlusBearerBar const & __ptr64)> const &
   __ptr64,enum DocumentMarks::PDFPlusBearerBar::SizeReference) */

void __cdecl
DocumentMarks::SetBearerBarSizeReference
          (Content *param_1,
          function<bool___cdecl(DocumentMarks::PDFPlusBearerBar_const&___ptr64)> *param_2,
          SizeReference param_3)

{
  ActionList *pAVar1;
  undefined1 auStack_f8 [32];
/* ... 65 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_1800A8B40.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
