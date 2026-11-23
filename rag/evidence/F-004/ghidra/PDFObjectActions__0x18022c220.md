---
modulo: PDFObjectActions.dll
funcao: GOVCloneSelection::ConfigChangeMatrix
endereco: 0x18022c220
versao: 24.03.10017
confianca: media
xrefs: [0x18022bfb0]
strings: []
---

# GOVCloneSelection::ConfigChangeMatrix @ 0x18022c220

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x18022c220` |
| Nome no binario | `GOVCloneSelection::ConfigChangeMatrix` |
| Assinatura (Ghidra) | `GOVisitorBase * __thiscall ConfigChangeMatrix(void)` |
| Parametros | 1 |
| Bytes de corpo | 190 |
| Chamadores | 1 |
| Chamadas diretas | 4 |

## Papel provavel

Fato: `GOVCloneSelection::ConfigChangeMatrix()` cria/caches um
`GOVChangeMatrix` a partir de `GOLocation::GetCurrentToUserMatrix`
pos-concatenada com a matriz em `+0x1f8` (`GMatrixBase<double>::PostConcat`),
com id de mudanca `0x3ea`; o cache fica na tabela em `+0x290` indexada por
`*(int*)(this+0x29c)`.

Inferencia: e a matriz usada para clonar/copiar a selecao mantendo-a no mesmo
lugar em coordenadas de usuario; o unico chamador direto e
`GOVCloneSelection::AddContentObjectToCurrentContent`.

## Xrefs de entrada (quem chama)

- `0x18022bfb0 GOVCloneSelection::AddContentObjectToCurrentContent`

## Chamadas diretas (quem esta funcao chama)

- `0x1803cefc4 FUN_1803cefc4`
- `EXTERNAL:0000089f PDFOBJECTLAYER.DLL::GOLocation::GetCurrentToUserMatrix`
- `0x180339f40 GOVChangeMatrix::GOVChangeMatrix`
- `EXTERNAL:00000ee9 BASICFRAMEWORKCORELAYER.DLL::GMatrixBase<double>::PostConcat`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- nenhum ponteiro absoluto encontrado (funcao pode ser chamada so por `call rel32`)

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* private: class GOVisitorBase * __ptr64 __cdecl GOVCloneSelection::ConfigChangeMatrix(void)
   __ptr64 */

GOVisitorBase * __thiscall GOVCloneSelection::ConfigChangeMatrix(GOVCloneSelection *this)

{
  GOVChangeMatrix *this_00;
  undefined8 uVar1;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 uStack_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 uStack_10;

                    /* 0x22c220  6228
                       ?ConfigChangeMatrix@GOVCloneSelection@@AEAAPEAVGOVisitorBase@@XZ */
  if (*(longlong *)(*(longlong *)(this + 0x290) + -8 + (longlong)*(int *)(this + 0x29c) * 8) == 0) {
    local_20 = DAT_18040a028;
    local_38 = DAT_18040a028;
    local_18 = 0;
    uStack_10 = 0;
    local_30 = 0;
    uStack_28 = 0;
    GOLocation::GetCurrentToUserMatrix((GMatrixBase<double> *)&local_38);
    GMatrixBase<double>::PostConcat
              ((GMatrixBase<double> *)&local_38,(GMatrixBase<double> *)(this + 0x1f8));
    this_00 = (GOVChangeMatrix *)FUN_1803cefc4(0x2a0);
    if (this_00 == (GOVChangeMatrix *)0x0) {
      uVar1 = 0;
    }
    else {
      uVar1 = GOVChangeMatrix::GOVChangeMatrix(this_00,(GMatrixBase<double> *)&local_38,false,0x3ea)
      ;
    }
    *(undefined8 *)(*(longlong *)(this + 0x290) + -8 + (longlong)*(int *)(this + 0x29c) * 8) = uVar1
    ;
  }
  return *(GOVisitorBase **)
          (*(longlong *)(this + 0x290) + -8 + (longlong)*(int *)(this + 0x29c) * 8);
}


```

Raw completo: `_raw/PDFObjectActions__18022c220.txt`.

