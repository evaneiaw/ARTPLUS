---
modulo: PDFObjectActions.dll
funcao: module-identity
endereco: PE-image
versao: 24.03.10017
confianca: alta
---

# PDFObjectActions.dll - identidade do binario (v24.03.10017)

Todos os dados abaixo foram medidos nesta maquina, hoje, sobre o arquivo de
referencia. Nada foi copiado de relatorio anterior.

## 1. Arquivo

| Campo | Valor |
|---|---|
| Caminho | `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\PDFObjectActions.dll` |
| Tamanho | 8004528 bytes |
| SHA-256 | `8F6A23C1533E45AF657D91E62C18379AF3FE5B59C947C04A068A42E43573184D` |
| MD5 | `9B2542E6BC3304C05B2CDDF12636BAF1` |
| Machine | 0x8664 (x64) |
| ImageBase | 0x180000000 |
| TimeDateStamp | 1710261423 |
| Exportacoes | 10024 nomes (C++ mangled, MSVC) |
| Data/hora do arquivo | 2024-03-12 18:42:30 |

Comando de medicao: ver `ghidra/_probe/identity.py` (pefile 2024.8.26) e
`Get-FileHash -Algorithm SHA256`.

## 2. Secoes

| Secao | VA | VirtualSize | RawSize | Entropia |
|---|---|---|---|---|
| .text | 0x1000 | 4167379 | 4167680 | 6.331 |
| .rdata | 0x3FB000 | 3207078 | 3207168 | 5.764 |
| .data | 0x70A000 | 210168 | 163840 | 4.603 |
| .pdata | 0x73E000 | 206712 | 206848 | 6.265 |
| .rsrc | 0x771000 | 480 | 512 | 4.725 |
| .reloc | 0x772000 | 245996 | 246272 | 5.439 |

Nenhum sinal de packer: entropia de .text 6.33, .rsrc de 480 bytes, imports
legiveis, 10024 exports nomeados. Compactador: Microsoft Linker 14.38.33134,
compilador MSVC 19.38.33134 (Visual Studio 2022 17.8), runtime MSVC dinamico,
biblioteca zlib, assinatura Authenticode e debug data POGO (DIE, ver `die.json`).

## 3. Dependencias (18 DLLs importadas)

`adt.dll`, `basicframeworkcorelayer.dll`, `certifiedpdflayer.dll`,
`colormanipulationlayer.dll`, `curveapprox.dll`, `fontlayer.dll`,
`geomapper.dll`, `imagesupportlayer.dll`, `jpxsupportlayer.dll`, `offset.dll`,
`pdfaccesslayer.dll`, `pdfbarcodescanlayer.dll`, `pdfgeometrylayer.dll`,
`pdfobjectlayer.dll`, `pdfobjecttoolslayer.dll`, `pdfrenderinglayer.dll`,
`reportdatabaselayer.dll`, `yagl.dll`.

Relevante para F-004: `PDFOBJECTLAYER.DLL` e a origem dos simbolos
`GOSelectable::*` (IsSelected, PushSelection, PopSelection, AndSelection,
OrSelection, XorSelection, InvertSelection, DupSelection, RollSelection,
CopySelectionStack, ClearSelectionStack) importados por este modulo; ou seja,
o *estado* de selecao do objeto mora no PDFObjectLayer, e PDFObjectActions
apenas o manipula.

## 4. Classes/strings observadas no proprio binario (strings64 -n 6)

Cadeia de selecao e transformacao:

- `Select %1 images`, `Select images`, `Select objects %1`, `Select subpaths`,
  `Select pages`, `Select annotations' appearance streams contents according to annotation selection`,
  `Select form contents according to form selection`,
  `Select tiling pattern contents according to parent object selection`
- `Remove selection`, `Move selection`, `Scale selection`, `Rotate selection`,
  `Shear selection`, `Transform selection`, `Flip selection`, `Clone selection`
- `Duplicate top of selection stack`, `Remove top of selection stack`,
  `Put selection in form`, `Save selection`, `Restore selection`,
  `Rasterize selection`, `Grab Selection`, `Grab Area from Selection`,
  `Grab Sample from Selection`
- `selection`, `Selections`, `Selection color`, `selection bounding box`,
  `visible area of selection`
- `Resize %1 box`, `Resize %1 box by (%2, %3)`, `Resize %1 box by (%2, %3, %4, %5)`,
  `Resize %1 box to selection`, `Resize page box to fit the selection`,
  `Resized %BoxType% by %RequiredDimensions%`, `Resized %BoxType% to %RequiredDimensions%`
- `LeftResize`, `RightResize`, `TopResize`, `BottomResize` e os atributos
  `?cAttr_LeftResize@GOVChangePageBox@@2VGBuffer@@B` (idem Right/Top/Bottom)
- R4 da spec: as strings citadas existem de fato no binario -
  `WhatWithCropBox`, `CropBox size %1 of page %2 is not equal to %3`,
  `CropBox rectangle %1 of page %2 is not equal to %3`, `ArtBox size ...`
  (verificado por busca exata). O pertencimento delas a um operador de
  Selection Mark nao foi provado; os atributos `?cAttr_*Resize@GOVChangePageBox`
  indicam que o resize de caixa de pagina e do operador `GOVChangePageBox`
  (inferencia a partir do nome do atributo).

RTTI (`.?AV...`) de classes de selecao/transformacao presentes:
`GOVSelect`, `GOVSelectObjects`, `GOVSelectOverlappingObjects`,
`GOVDefaultSelect`, `GOVSelectStackToUser`, `GOSelectable`,
`GOVGetSelectedObjects`, `GOVSelectHitElement`,
`GOVChangeScaleSelection`, `GOVChangeRotateSelection`,
`GOVChangeFlipSelection`, `GOVChangeRasterizeSelection`,
`GOVChangeSelectionToForm`, `GOVSelectConcealedObjects`,
`GOVSelectForSandwich`, `GOVNodeSelectionToUser`, `GOVSelectType`
(contagem medida sobre a lista completa de strings do binario; amostra filtrada
em `rag/evidence/F-004/strings64.txt`).

## 5. O que este modulo NAO contem (fato negativo medido)

- Nao existe nenhuma string `SelectionMark`, `Selection Mark` ou
  `Selection mark` em PDFObjectActions.dll (busca exata em 37006 strings,
  `strings64 -n 6`). O texto de status `"Selection Mark ativo"` citado na spec
  F-004 nao pode vir deste modulo; a origem e a camada de UI/executavel.
- Nao existem strings de UI de toolbar/atalho (`Ctrl+Shift+S`) neste DLL.
  Consequencia: a parte "icone + atalho + status bar" de F-004 precisa de
  evidencia de outro binario (ArtPro+.exe / *ViewLayer), nao deste.

## 6. Projeto Ghidra usado nesta extracao

| Campo | Valor |
|---|---|
| Projeto | `H:\Desktop\ArtPlus\tools\ghidra_projects\PDFObjectActions_v240` |
| Programa | `PDFObjectActions.dll` |
| `executableSHA256` no programa | `8f6a23c1533e45af657d91e62c18379af3fe5b59c947c04a068a42e43573184d` |
| `executablePath` no programa | `/C:/Esko/bg_prog_artpro+_v240/ArtPro+.app/Contents/Windows/PDFObjectActions.dll` |
| Data de criacao do programa | 2026-11-21 19:18:52 |
| Funcoes apos analise padrao | 23804 |

Log do import: `ghidra/_probe/import_v240.log` (EXITCODE=0).
Scripts usados (reproduziveis): `ghidra/_scripts/F004Probe.java`,
`ghidra/_scripts/F004Extract.java`, `ghidra/_scripts/F004Titles.java`.

> O projeto antigo `PDFObjectActions_New` NAO foi usado: contem o binario da v25
> (`executablePath=/C:/Esko/bg_prog_artpro+_v250/...`,
> `executableSHA256=73ab2d7b...`). Ver secao 7.

## 7. Divergencia registrada (nao corrigida aqui, fora do escopo)

`docs/reverse-engineering/PDFObjectActions_AUTO_TRIAGE.md` declara
`SHA-256: 73ab2d7b7df5ea73272eb5bdafb3408a90f6d471680300d3debf0b2294273bf4` e
`Tamanho: 8299560 bytes` para o caminho v240. O arquivo v240 real tem
8004528 bytes e SHA-256 `8F6A23C1...`. O hash 73ab... e o do
`PDFObjectActions.dll` da **v25** (confirmado: projeto Ghidra
`PDFObjectActions_New` criado em 2026-11-20 tem
`executablePath=/C:/Esko/bg_prog_artpro+_v250/...` e `executableSHA256=73ab...`).
A triagem foi feita sobre o binario da v25 e rotulada como v240; por isso
nenhum endereco dela entra neste manifest.

## 8. Deslocamento v25 -> v240 dos simbolos citados no manifest anterior

Os simbolos existem nas duas versoes, mas com enderecos diferentes. Medido:

| Simbolo | v25 (projeto `PDFObjectActions_New`) | v240 (projeto `PDFObjectActions_v240`) |
|---|---|---|
| `GOVSelectOverlapping::GOVSelectOverlapping` (2 args) | 0x1802a6e30 | 0x18028bee0 |
| `GOVSelectOverlapping::GOVSelectOverlapping` (1 arg) | 0x1802a6ed0 | 0x18028bf80 |
| `GOVSelectOverlappingObjects::GOVSelectOverlappingObjects` (2 args) | 0x1802a7690 | 0x18028cc70 |
| `GOVSelectOverlappingObjects::GOVSelectOverlappingObjects` (2 args) | 0x1802a7780 | 0x18028cd60 |
| `GOVSelectOverlapping::Select(GOElement&)` | (nao medido) | 0x18028c310 |
| `GOVSelectOverlapping::Select(GOPage&)` | (nao medido) | 0x18028c410 |
| `GOVSelectOverlappingObjects::Select(GOPage&)` | (nao medido) | 0x18028df80 |

Conclusao: os IDs `GHIDRA-PDFObjectActions-0x1802a6e30`, `...-0x1802a6ed0`,
`...-0x1802a7690` e `...-0x1802a7780` do manifest anterior eram **v25**.
`0x1802a7060` e `0x1802a79e0` caiam no meio de funcoes (nao eram inicios de
funcao) e foram descartados.

Os outros 10 IDs antigos (`0x1806dc21e`, `0x1806dc254`, `0x1806dc287`,
`0x1806dc2c4`, `0x18068447e`, `0x1806844b4`, `0x180688437`, `0x1806ac7c5`,
`0x1806e8f62`, `0x1807015ed`) apontam para o **interior de nomes mangled** na
`.rdata` do v240, por exemplo `0x1806dc21e` -> `ChangeNodesBase@@QEAA@AEBV0@@Z`
e `0x180688437` -> `ializeAttributes@GOVSelectByFontName@@UE...`. Nao sao
funcoes nem strings de UI; sao restos de varredura de bytes. Nenhum foi
reaproveitado.

