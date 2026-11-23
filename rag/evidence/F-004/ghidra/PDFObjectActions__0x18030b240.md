---
modulo: PDFObjectActions.dll
funcao: GOVGetSelectedObjects::GetObjects
endereco: 0x18030b240
versao: 24.03.10017
confianca: alta
xrefs: [0x1800adc30]
strings: []
---

# GOVGetSelectedObjects::GetObjects @ 0x18030b240

Modulo: PDFObjectActions.dll, versao de referencia 24.03.10017.

## Identidade

| Campo | Valor |
|---|---|
| Endereco | `0x18030b240` |
| Nome no binario | `GOVGetSelectedObjects::GetObjects` |
| Assinatura (Ghidra) | `GTable<GOObject*___ptr64> * __thiscall GetObjects(void)` |
| Parametros | 1 |
| Bytes de corpo | 11 |
| Chamadores | 1 |
| Chamadas diretas | 0 |

## Papel provavel

Fato: `GOVGetSelectedObjects::GetObjects()` tem 11 bytes e retorna
`**(undefined8**)(this+0x1e0)` - ou seja, desreferencia o campo `+0x1e0` e
devolve a `GTable<GOObject*>` corrente.

Fato: o unico chamador direto e `GOVChangeIsolateClippaths::Visit`
(0x1800ADc30).

Inferencia: accessor da selecao corrente usada pelos operadores; nao
produz nem altera o estado de selecao.

## Xrefs de entrada (quem chama)

- `0x1800adc30 GOVChangeIsolateClippaths::Visit`

## Chamadas diretas (quem esta funcao chama)

- nenhuma

## Strings referenciadas pela propria funcao

- nenhuma string literal referenciada diretamente

## Ponteiros para esta funcao em dados nao executaveis (vtable/RTTI)

- nenhum ponteiro absoluto encontrado (funcao pode ser chamada so por `call rel32`)

## Pseudocodigo (extrato do Ghidra, cortado em 110 linhas)

```c

/* public: class GTable<class GOObject * __ptr64> const & __ptr64 __cdecl
   GOVGetSelectedObjects::GetObjects(void)const __ptr64 */

GTable<GOObject*___ptr64> * __thiscall
GOVGetSelectedObjects::GetObjects(GOVGetSelectedObjects *this)

{
                    /* 0x30b240  7866
                       ?GetObjects@GOVGetSelectedObjects@@QEBAAEBV?$GTable@PEAVGOObject@@@@XZ */
  return (GTable<GOObject*___ptr64> *)**(undefined8 **)(this + 0x1e0);
}


```

Raw completo: `_raw/PDFObjectActions__18030b240.txt`.

