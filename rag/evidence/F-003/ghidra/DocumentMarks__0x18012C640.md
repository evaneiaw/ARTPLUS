---
modulo: DocumentMarks.dll
funcao: DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar
endereco: 0x18012C640
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x18012FAA0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18012C640

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x18012FAA0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18012C640`
- simbolo: `DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar`
- assinatura: `undefined PDFPlusBearerBar(PDFPlusBearerBar * this, shared_ptr<ArtPaint::FormPaint_const_> param_1)`
- corpo: `0x18012C640`..`0x18012C7FA` (443 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x18012FAA0`

## O que faz

Construtor PDF+ (a partir de shared_ptr<ArtPaint::FormPaint const>). Chama DynamicMark(this, false, 0x1CE), instala as vftables e aplica os defaults: +0x758 = 0, +0x768 = 0, +0x770 = 1 (Direction), +0x778 = 3 (referencia PageBox), byte +0x7F0 = 0, +0x7F8 = 0 (SizeReference), +0x800/+0x808/+0x810 = 0 e inicializa o container de +0x818 com 4 elementos (FUN_180024CF0). Consome o shared_ptr recebido. Nao referencia strings.

## Chamadores (xrefs de chamada)

- `1801652b0 FUN_1801652b0`

Chamadas diretas (10):

- `180108450 DocumentMarks::MarkPosition::setAnchors`
- `180090ac0 FUN_180090ac0`
- `180024cf0 FUN_180024cf0`
- `1801089c0 DocumentMarks::MarkPosition::setReferenceObject`
- `18006bd80 DocumentMarks::DynamicMark::DynamicMark`
- `180020c10 FUN_180020c10`
- `180097950 DocumentMarks::DynamicObject::setColorType`
- `180093dd0 DocumentMarks::DynamicObject::SetTargetSeparations`
- `1801f7670 FUN_1801f7670`
- `180071b30 DocumentMarks::DynamicMark::SetSourceContent`

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* public: __cdecl DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar(class std::shared_ptr<class
   ArtPaint::FormPaint const >) __ptr64 */

PDFPlusBearerBar * __thiscall
DocumentMarks::PDFPlusBearerBar::PDFPlusBearerBar(PDFPlusBearerBar *this,undefined8 *param_2)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  variant<std::variant<DocumentMarks::DynamicColorTopFilter,ArtDoc::ProcessingSteps::Key,std::variant<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::Separation::PredefinedPrintingMethod>,DocumentMarks::ColorantNameFilter,DocumentMarks::VariableColorantNameFilter,DocumentMarks::ProcessFilter,DocumentMarks::IndexFilter,DocumentMarks::LogicalFilter,DocumentMarks::ConditionalFilter>,DocumentMarks::UsePrintingUnits>
  *local_res18;
/* ... 68 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012C640.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
