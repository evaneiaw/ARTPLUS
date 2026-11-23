# Análise Estática Ghidra — ColorManipulationLayer.dll (F-004)

**Binário:** `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ColorManipulationLayer.dll`  
**SHA-256:** `92a8b38fa14ac6480a036acadf76c4563da49109805418e9e5688659c7de72a9`  
**Versão:** ArtPro+ 25.0  
**Projeto Ghidra:** `tools/ghidra_projects/ArtProPlus_ColorManipulationLayer.rep`  
**Exports:** `rag/ghidra/exports/ColorManipulationLayer.dll/` (functions.csv, symbols.csv, xrefs.csv, callgraph_simplified.csv, strings.csv)  
**Evidências:** `rag/evidence/F-004/ghidra/`

> Nota de caminho: a pasta `C:\Esko\bg_prog_artpro+_v240` existe apenas como `.rar` nesta máquina; o binário v240 real está em `C:\bg_prog_artpro+_v240\...` (não localizado). A triagem e os exports foram gerados a partir do binário copiado no projeto Ghidra. A v240 está em `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ColorManipulationLayer.dll`.

---

## Funções analisadas (5 de 5)

| ID | Endereço | Nome | Confiança | Pseudocódigo | Xrefs de entrada |
|----|----------|------|-----------|--------------|------------------|
| GHIDRA-ColorManipulationLayer-0x180014b80 | `0x180014b80` | `GCColorManipulationLayer::Initialize` | alta | `ColorManipulationLayer__0x180014b80.json` | `0x180040760`, `0x18005162c` |
| GHIDRA-ColorManipulationLayer-0x1800132f0 | `0x1800132f0` | `GCColorManipulation::GetInstance` | alta | `ColorManipulationLayer__0x1800132f0.json` | `0x1800405c8` |
| GHIDRA-ColorManipulationLayer-0x180012bf0 | `0x180012bf0` | `GCColorManipulation::GetActiveICCProfile` | alta | `ColorManipulationLayer__0x180012bf0.json` | `0x180040490`, `0x18005132c` |
| GHIDRA-ColorManipulationLayer-0x180014980 | `0x180014980` | `GCColorManipulation::SetLevelICCProfile` | alta | `ColorManipulationLayer__0x180014980.json` | `0x180040860` |
| GHIDRA-ColorManipulationLayer-0x18000a2f0 | `0x18000a2f0` | `GCCallbackConverter::ConvertColor` | media | *não disponível* (falha REA) | `0x180040430`, `0x18005093c` |

---

## Detalhes por função

### Initialize — `0x180014b80`
- **Arquivo:** `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x180014b80.md`
- **Resumo:** Ponto de entrada de inicialização da camada de cor. Singleton com contador de reentrância (`sInitialized`). Chama `GCICCProfileCache::CreateInstance`, `FUN_180027c40`, `FUN_1800269b0`, `InitializeStrings`, `InitializeXYZProfile`.
- **Confiança:** alta — símbolo demangled confirmado; pseudocódigo do decompiler Ghidra registrado na sessão.

### GetInstance — `0x1800132f0`
- **Arquivo:** `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x1800132f0.md`
- **Resumo:** Acesso ao singleton `GCColorManipulation`. Retorna `sInstance`.
- **Confiança:** alta — pseudocódigo direto do decompiler Ghidra via REA.

### GetActiveICCProfile — `0x180012bf0`
- **Arquivo:** `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x180012bf0.md`
- **Resumo:** Resolve o perfil ICC ativo (`GSharedObject<GCICCProfile>`) por `ColorType` e `CategoryType`. Itera sobre `GCColorLibInfo` para encontrar match; lança `GCSimpleException` (código `0x124f85`) se não houver perfil.
- **Strings relacionadas:** `Enfocus XYZ Profile.icc`, `AdobeRGB1998.icc`, `WAN-IFRA/ISOcoated_v2_eci.icc`, `No XYZ ICC profile has been defined`, `Invalid ICC profile`.
- **Confiança:** alta — pseudocódigo completo do decompiler Ghidra via REA.

### SetLevelICCProfile — `0x180014980`
- **Arquivo:** `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x180014980.md`
- **Resumo:** Define perfil ICC por nível (stack de perfis). Seleciona nível por `CategoryType` (0 = `this+0x20`, senão `this+8`) e chama `FUN_1800161c0` para definir o perfil no array interno.
- **Confiança:** alta — pseudocódigo do decompiler Ghidra via REA.

### ConvertColor (GCCallbackConverter) — `0x18000a2f0`
- **Arquivo:** `rag/evidence/F-004/ghidra/ColorManipulationLayer__0x18000a2f0.md`
- **Resumo:** Conversão de cor via callback (`GTable<GFunction*>`). Função virtual (`UEBA`) de `GCCallbackConverter`.
- **Limitação:** Pseudocódigo não disponível — `rea decompile` falhou com `target_unavailable` (caminho do binário não encontrado). Registrado com confiança `media`.
- **Confiança:** media — símbolo demangled confirmado; comportamento exato não verificado por decompiler.

---

## Imports críticos (da triagem)

| DLL | Funções relevantes |
|-----|-------------------|
| `mscms.dll` | `OpenColorProfileA`, `CloseColorProfile`, `GetColorProfileHeader`, `GetColorDirectoryW` |
| `lcms.dll` | `cmsDeltaE`, `cmsCIE94DeltaE`, `cmsOpenProfileFromMem`, `cmsCreateTransform`, `cmsDoTransform`, `cmsDeleteTransform`, `cmsGetHeaderRenderingIntent`, `cmsGetColorSpace`, `cmsGetPCS` |
| `MD5SupportLayer.dll` | `GMD5Digest` |
| `BasicFrameworkCoreLayer.dll` | strings, buffers, paths, streams, allocators, file system, exceptions, UTF/encoding |

---

## Limitações

1. O caminho `C:\bg_prog_artpro+_v240\...` não existe neste ambiente; a segunda execução do `rea decompile` falhou para `Initialize` e `ConvertColor`. O pseudocódigo de `Initialize` foi reconstruído do terminal da sessão anterior; `ConvertColor` ficou sem pseudocódigo.
2. Nomes `FUN_*` (ex: `FUN_180027c40`, `FUN_1800269b0`, `FUN_1800161c0`) são placeholders do Ghidra sem símbolo demangled disponível no export.
3. Não foi realizado diff v240 × v240.

---

## Próximos passos

1. Reexecutar `rea decompile` para `0x18000a2f0` (`ConvertColor`) e `0x180014b80` (`Initialize`) com o caminho do binário corrigido, para preencher os pseudocódigos em falta.
2. Comparar com `ColorManipulationLayer.dll` v240 (`C:\Esko\bg_prog_artpro+_v240\...`) para confirmar estabilidade de comportamento entre versões.
3. Consolidar em `docs/features/F-004.md` com rastreabilidade `GHIDRA-ColorManipulationLayer-0x...`.

---