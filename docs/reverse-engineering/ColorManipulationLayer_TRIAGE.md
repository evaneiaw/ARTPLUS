# Triagem Estática — ColorManipulationLayer.dll

**Binário:** `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ColorManipulationLayer.dll`  
**SHA-256:** `92a8b38fa14ac6480a036acadf76c4563da49109805418e9e5688659c7de72a9`  
**Tamanho:** 342.568 bytes  
**Data:** 2025-02-04  
**Versão de referência:** ArtPro+ 25.0

---

## 1. Identidade do Binário

| Campo | Valor |
|-------|-------|
| **Tipo** | PE64 (DLL x64) |
| **Compilador** | Microsoft Visual C/C++ 19.41.34435 (C++) |
| **Linker** | Microsoft Linker 14.41.34435 |
| **Toolchain** | Microsoft Visual Studio 2022 17.11 |
| **Runtime** | Microsoft C/C++ Runtime [dynamic] |
| **Assinatura** | Windows Authenticode 2.0 (PKCS #7) — **assinado** |
| **Dados de debug** | Records [POGO] |

---

## 2. Estrutura de Seções (PE)

| Seção | VA | VSize | RawPtr | RawSize | Descrição |
|-------|-----|--------|--------|---------|-----------|
| `.text` | 0x1000 | 0x12D238B | 0x400 | 0x12D2400 | Código executável (~19 MB virtual) |
| `.textidx` | 0x12D4000 | 0xA7903 | 0x12D2800 | 0xA7A00 | Índice de texto/strings |
| `.rdata` | 0x137C000 | 0x6EE7A8 | 0x137A200 | 0x6EE800 | Dados read-only (vtable, strings, imports) |
| `.data` | 0x1A6B000 | 0x4E9AF8 | 0x1A68A00 | 0x234000 | Dados read-write |
| `.pdata` | 0x1F55000 | 0xA2FD8 | 0x1C9CA00 | 0xA3000 | Exception handling (RUNTIME_FUNCTION) |
| `.fnp_dir` | 0x1FF8000 | 0x78 | 0x1D3FA00 | 0x200 | FNP (FlexNet Publisher) directory |
| `.fnp_mar` | 0x1FF9000 | 0x1 | 0x1D3FC00 | 0x200 | FNP marker |
| `.rsrc` | 0x1FFA000 | 0x3DD98 | 0x1D3FE00 | 0x3DE00 | Recursos (manifest, version info) |
| `.reloc` | 0x2038000 | 0x53730 | 0x1D7DC00 | 0x53800 | Tabela de relocação |

---

## 3. Superfície Funcional (Strings de UI / Domínio)

A DLL contém **strings embutidas** que revelam seu domínio: **gestão de cores ICC, conversão, perfis, simulação de prova, Pantone**.

### Perfis e condições de impressão (ISO 12647-2 / CGATS21-2 / FOGRA)
- OFCOM Printing process definitions (ISO 12647-2:2004, 2013, Amd1)
- FOGRA53 (CMYK exchange space) — 3 requisitos essenciais documentados na string
- CRPC1–CRPC6: COLDSET NEWS, HEATSET NEWS, GRACoL2013-UNC, Universal SuperCal, PubCoated, PremCoated, Extra
- Perfis ICC conhecidos: `Generic Enfocus Gray.icm`, `AdobeRGB1998.icc`, `WAN-IFRA/ISOcoated_v2_eci.icc`, `Generic Enfocus Lab.icm`

### Mensagens de erro (internas, não UI)
- "An internal error has occurred during color conversion"
- "No Color Management support available"
- "Invalid color conversion engine"
- "The system color management could not be accessed"
- "Color conversion failed"
- "No XYZ ICC profile has been defined"
- "Invalid ICC profile", "Invalid color library file"
- "Could not open profile", "bitsPerSample not 8 or 16"

### Pastas de perfis ICC (variáveis de ambiente expandidas)
- `%SystemColorFolder%`, `%LocalColorFolder%`, `%NetworkColorFolder%`, `%UserColorFolder%`, `%EnfocusResourceFolder%`
- Caminhos: `\SysWOW64\`, `\system32\`

---

## 4. Exports Cruciais (símbolos C++ mangled)

Os símbolos exportados (inferidos de `strings64 -n 8` — RTTI/vtable + nomes decorados) indicam as **classes centrais** e **pontos de entrada públicos**:

| Símbolo (mangled) | Classe / Função provável |
|-------------------|---------------------------|
| `??0GCColorManipulation@@IEAA@XZ` | `GCColorManipulation` — construtor protegido (singleton) |
| `?Initialize@GCColorManipulationLayer@@SA_NXZ` | `GCColorManipulationLayer::Initialize()` — **entry point da camada** |
| `?GetInstance@GCColorManipulation@@SAAEAV1@XZ` | `GCColorManipulation::GetInstance()` — acesso ao singleton |
| `?ConvertColor@GCCallbackConverter@@UEBAX...` | `GCCallbackConverter::ConvertColor()` — conversão via callback |
| `?GetActiveICCProfile@GCColorManipulation@@QEBA...` | `GCColorManipulation::GetActiveICCProfile()` — perfil ativo por tipo/categoria |
| `?SetLevelICCProfile@GCColorManipulation@@QEAAX...` | `GCColorManipulation::SetLevelICCProfile()` — define perfil por nível (stack) |

Outras classes exportadas (construtores/destrutores/operadores vistos nas strings):
- `GCCalGray`, `GCCalRGB`, `GCCalibrated` — espaços calibrados (Gray, RGB, Lab)
- `GCICCBased*`: `CMYK`, `Gray`, `Lab`, `RGB` — espaços baseados em ICC
- `GCDevice*`: `CMYK`, `Gray`, `RGB` — device spaces
- `GCLab`, `GCXYZ` — espaços Lab / XYZ
- `GCConverter`, `GCMultiStepConverter`, `GCConverterFactory` — pipeline de conversão
- `GCColorObject`, `GCSourceObjectInfo`, `GCObjectInfo` — objetos de cor com metadados
- `GCICCProfile`, `GCICCProfileCache` — perfis ICC e cache
- `GCDeviceLinkMapping` — mapeamento DeviceLink
- `GCColorLibrary`, `GCColorLibInfo` — bibliotecas de cores (Pantone)
- `GCColorManipulationLayer` — fachada da DLL
- `GCCallbackChangeColor`, `GCCallbackConverter` — extensibilidade via callback
- `GCIlluminantAdapterFromD50/ToD50` — adaptação de iluminante
- `GCVariableSubstitution` — substituição de variáveis em caminhos

---

## 5. Imports Cruciais (DLLs dependentes)

Identificadas nas strings (IAT provável):

| DLL | Função / Propósito |
|-----|-------------------|
| **mscms.dll** | Windows Color System — `OpenColorProfileA`, `CloseColorProfile`, `GetColorProfileHeader`, `GetColorDirectoryW` |
| **lcms.dll** | Little CMS — `cmsDeltaE`, `cmsCIE94DeltaE`, `cmsOpenProfileFromMem`, `cmsCreateTransform`, `cmsDoTransform`, `cmsDeleteTransform`, `cmsGetHeaderRenderingIntent`, `cmsGetColorSpace`, `cmsGetPCS`, etc. |
| **MD5SupportLayer.dll** | Suporte a hash MD5 (`GMD5Digest`) |
| **BasicFrameworkCoreLayer.dll** | Core framework (strings, buffers, paths, streams, allocators, file system, exceptions, UTF/encoding) |
| **VCRUNTIME140.dll**, **VCRUNTIME140_1.dll** | C++ Runtime (exceções, heap, math, thread-local, onexit) |

---

## 6. Dependências Internas (Módulos Esko)

- **BasicFrameworkCoreLayer.dll** — infraestrutura base (containers, streams, paths, encoding, exceptions)
- **MD5SupportLayer.dll** — hashing
- **lcms.dll** (3rd-party, embedded) — engine de conversão ICC primária
- **mscms.dll** (Windows) — fallback / enumeração de perfis do sistema

---

## 7. Alvos Prioritários para Ghidra

| Endereço / Símbolo | Prioridade | Motivo |
|--------------------|------------|--------|
| `GCColorManipulationLayer::Initialize` | **Alta** | Entry point — inicializa singleton, carrega perfis padrão, registra callbacks |
| `GCColorManipulation::GetInstance` | **Alta** | Singleton global — ponto de acesso a toda a API de cor |
| `GCColorManipulation::ConvertColor` / `GCCallbackConverter::ConvertColor` | **Alta** | Caminho principal de conversão de cor |
| `GCColorManipulation::GetActiveICCProfile` / `SetLevelICCProfile` | **Alta** | Gerenciamento de pilha de perfis por nível (override, device-link) |
| `GCICCProfileCache::GetProfile` / `GetDeviceLinkProfile` | **Média** | Cache de perfis — performance e ciclo de vida |
| `GCConverterFactory::GetConverter` | **Média** | Factory de conversores — seleção de engine (lcms vs. built-in) |
| `GCColorLibrary::TrimFromReadLibrary` / Pantone matching | **Baixa** | Bibliotecas de cores spot/Pantone |

---

## 8. Evidência Registrada

| Arquivo | Descrição |
|---------|-----------|
| `rag/evidence/F-004/manifest.json` | Metadados + SHA-256 |
| `rag/evidence/F-004/die.json` | Saída do Detect It Easy (compilador, linker, assinatura) |
| `rag/evidence/F-004/strings64.txt` | Strings brutas (Unicode, ≥ 8 chars) |
| `rag/evidence/F-004/exports.txt` | Símbolos exportados (mangled) |
| `rag/evidence/F-004/imports.txt` | DLLs importadas |

---

## 9. Observações e Bloqueios

- **Binário assinado** — análise dinâmica pode exigir bypass de verificação de assinatura se houver anti-debug.
- **Dependência forte do lcms.dll** — o engine de conversão ICC real reside no Little CMS; a DLL Esko é *wrapper* + gerenciamento de perfis + device-link + Pantone.
- **FNP (FlexNet Publisher)** presente nas seções `.fnp_dir` / `.fnp_mar` — licenciamento/proteção.
- **Nenhum export "C" limpo** — todos os exports são C++ mangled; Ghidra precisará de demangling para vtables/RTTI.
- **POGO (Profile-Guided Optimization)** — código otimizado; descompilação pode ser menos legível.

---

## 10. Próximos Passos Recomendados

1. **Ghidra**: importar a DLL, rodar análise completa, focar nas classes listadas na seção 7.
2. **Diff v240**: comparar `ColorManipulationLayer.dll` v240 vs v240 (exports, strings, tamanhos de seção).
3. **Comportamento**: capturar no ArtPro+ real (v240) a abertura do painel de gestão de cores, conversão de perfil, simulação de prova — gerar `CAP-YYYYMMDD-nn`.
4. **Spec F-004**: consolidar esta triagem + Ghidra + comportamento em `docs/features/F-004.md`.

---

*Triagem realizada com: `diec -j`, `strings64 -n 8`, `scripts/inspect_pe.py`.*  
*Agente: REA (subagent) — sem uso de Ghidra/analyze.*