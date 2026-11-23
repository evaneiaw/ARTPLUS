---
modulo: PDFObjectActions.dll
funcao: GOVSelectOverlappingObjects::Expand
endereco: 0x18028d3b0
versao: 24.03.10017
confianca: media
xrefs: []
strings: []
---

# GOVSelectOverlappingObjects::Expand @ 0x18028d3b0

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x18028d3b0` |
| Nome no binario | `GOVSelectOverlappingObjects::Expand` |
| Assinatura (Ghidra) | `void __thiscall Expand(GTable<GOVisitorBase*___ptr64> * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 205 |
| Chamadores | 0 |
| Chamadas diretas | 6 |

## Papel provavel

Fato: `GOVSelectOverlappingObjects::Expand(GOPage&)` (205 bytes) e chamado a
partir do proprio operador para expandir a selecao corrente; usa
`GOVSelectOperator` e `GOPage::Accept`.

Inferencia: aplica o conjunto sobreposto a selecao existente (expansao),
sem substituir os objetos ja selecionados. Nao foi decompilado linha a linha
para confirmar a semantica exata de uniao vs. substituicao.

## Xrefs de entrada (quem chama)

- nenhuma chamada direta detectada (provavel entrada por vtable/export)

## Chamadas diretas (quem esta funcao chama)

- `EXTERNAL:0000019c PDFOBJECTTOOLSLAYER.DLL::GOVSelectOperator::GOVSelectOperator`
- `0x18002a130 FUN_18002a130`
- `EXTERNAL:0000019d PDFOBJECTTOOLSLAYER.DLL::GOVSelectOperator::~GOVSelectOperator`
- `0x1800ad100 FUN_1800ad100`
- `EXTERNAL:0000019b PDFOBJECTTOOLSLAYER.DLL::GOVDefaultInform::~GOVDefaultInform`
- `0x18030af90 GOVGetSelectedObjects::GOVGetSelectedObjects`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:1804f20b8`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* public: virtual void __cdecl GOVSelectOverlappingObjects::Expand(class GTable<class GOVisitorBase
   * __ptr64> & __ptr64)const __ptr64 */

void __thiscall
GOVSelectOverlappingObjects::Expand
          (GOVSelectOverlappingObjects *this,GTable<GOVisitorBase*___ptr64> *param_1)

{
  int iVar1;
  longlong *plVar2;
  undefined8 uVar3;
  GOVGetSelectedObjects local_1f8 [480];
  undefined1 local_18 [16];

                    /* 0x28d3b0  7386
                       ?Expand@GOVSelectOverlappingObjects@@UEBAXAEAV?$GTable@PEAVGOVisitorBase@@@@@Z
                        */
  iVar1 = *(int *)(this + 0x1e0);
  if (((iVar1 != 0) && (iVar1 != 1)) && ((iVar1 == 2 || (iVar1 == 3)))) {
    plVar2 = (longlong *)
             GOVGetSelectedObjects::GOVGetSelectedObjects
                       (local_1f8,(GSmartPtr<GTable<GOObject*___ptr64>_> *)(this + 0x1e8));
    (**(code **)(*plVar2 + 0x1f8))(plVar2,param_1);
    FUN_1800ad100(local_18);
    GOVDefaultInform::~GOVDefaultInform((GOVDefaultInform *)local_1f8);
    plVar2 = (longlong *)GOVSelectOperator::GOVSelectOperator((GOVSelectOperator *)local_1f8,7);
    (**(code **)(*plVar2 + 0x1f8))(plVar2,param_1);
    GOVSelectOperator::~GOVSelectOperator((GOVSelectOperator *)local_1f8);
  }
  uVar3 = (**(code **)(*(longlong *)this + 0x1d8))(this);
  FUN_18002a130(param_1,*(undefined4 *)(param_1 + 0xc),uVar3);
  return;
}


```

Raw completo: `_raw/PDFObjectActions__18028d3b0.txt`.

