---
modulo: PDFObjectActions.dll
funcao: GOVSelectObjects::Select
endereco: 0x180341480
versao: 24.03.10017
confianca: media
xrefs: []
strings: []
---

# GOVSelectObjects::Select @ 0x180341480

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x180341480` |
| Nome no binario | `GOVSelectObjects::Select` |
| Assinatura (Ghidra) | `bool __thiscall Select(GOObject * param_1)` |
| Parametros | 2 |
| Bytes de corpo | 32 |
| Chamadores | 0 |
| Chamadas diretas | 1 |

## Papel provavel

Fato: `bool GOVSelectObjects::Select(GOObject&)` tem 32 bytes: se o ponteiro
em `+0x220` for nulo chama `std::_Xbad_function_call` (MSVCP140), caso
contrario invoca o functor no deslocamento `+0x10` do objeto apontado.

Inferencia: `GOVSelectObjects` recebe um predicado (`std::function`) e o
aplica a cada objeto; a funcao aqui e apenas o despacho do predicado.
Confianca media: a logica real esta no functor configurado em tempo de
execucao (nao resolvivel estaticamente).

## Xrefs de entrada (quem chama)

- nenhuma chamada direta detectada (provavel entrada por vtable/export)

## Chamadas diretas (quem esta funcao chama)

- `0x1803ceeec MSVCP140.DLL::std::_Xbad_function_call`

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- `.rdata:180514740`

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* private: virtual bool __cdecl GOVSelectObjects::Select(class GOObject & __ptr64) __ptr64 */

bool __thiscall GOVSelectObjects::Select(GOVSelectObjects *this,GOObject *param_1)

{
  undefined1 uVar1;

                    /* 0x341480  13447  ?Select@GOVSelectObjects@@EEAA_NAEAVGOObject@@@Z */
  if (*(longlong **)(this + 0x220) == (longlong *)0x0) {
                    /* WARNING: Subroutine does not return */
    std::_Xbad_function_call();
  }
                    /* WARNING: Could not recover jumptable at 0x000180341497. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(longlong **)(this + 0x220) + 0x10))();
  return (bool)uVar1;
}


```

Raw completo: `_raw/PDFObjectActions__180341480.txt`.

