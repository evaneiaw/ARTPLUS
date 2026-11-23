# VERSION_CONFIRMATION — versão real dos executáveis ArtPro+

**Tipo**: verificação de ambiente (metadados de versão PE somente).
**Data**: 2026-11-21
**Escopo**: 2 binários — `ArtPro+.exe` das instalações v240 e v250.
**Não executado**: importação no Ghidra, `rea analyze`/`decompile` (fora do limite desta tarefa).

## Objetivo

Validar o mapeamento de versão descrito em `docs/environment/ENVIRONMENT_INVENTORY.md`
(`bg_prog_artpro+_v240 = 24.03.10017`) e confirmar a string real de versão do exe da
instalação v250, para corrigir referências de versão no repositório.

## Comando reproduzível

```powershell
$paths = @(
  'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe',
  'C:\Esko\bg_prog_artpro+_v250\ArtPro+.app\Contents\Windows\ArtPro+.exe'
)
foreach ($p in $paths) {
  if (Test-Path -LiteralPath $p) {
    $f = Get-Item -LiteralPath $p
    $v = $f.VersionInfo
    "{0}`n  FileVersion    = {1}`n  ProductVersion = {2}`n  SHA256         = {3}" -f `
      $p, $v.FileVersion, $v.ProductVersion, (Get-FileHash -LiteralPath $p -Algorithm SHA256).Hash
  } else { "$p`n  MISSING" }
}
```

## Resultado

### v240 — `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\ArtPro+.exe`

| Campo | Valor |
|---|---|
| **Existe** | Sim |
| **FileVersion** | `24.03.10017` |
| **ProductVersion** | `24.03.10017` |
| FileDescription | `ArtPro+ 24.03` |
| ProductName | `ArtPro+` |
| OriginalFilename | `ArtPro+.exe` |
| CompanyName | `Esko` |
| LegalCopyright | `Copyright (c) 2024 Esko Software BV` |
| FileVersionRaw | `24.3.10017.0` |
| ProductVersionRaw | `24.3.10017.0` |
| Tamanho (bytes) | 31 276 976 |
| Data de modificação | 2024-03-19 17:12:30 |
| **SHA-256** | `9D33166126305F25C50349BB881F7D9ACDC996F3C0C9181D0BE61295D70B0F03` |

### v250 — `C:\Esko\bg_prog_artpro+_v250\ArtPro+.app\Contents\Windows\ArtPro+.exe`

| Campo | Valor |
|---|---|
| **Existe** | Sim |
| **FileVersion** | `25.03.116` |
| **ProductVersion** | `25.03.116` |
| FileDescription | `ArtPro+ 25.03` |
| ProductName | `ArtPro+` |
| OriginalFilename | `ArtPro+.exe` |
| CompanyName | `Esko` |
| LegalCopyright | `Copyright (c) 2025 Esko Software BV` |
| FileVersionRaw | `25.3.116.0` |
| ProductVersionRaw | `25.3.116.0` |
| Tamanho (bytes) | 34 852 904 |
| Data de modificação | 2025-02-04 00:05:00 |
| **SHA-256** | `D27DE85A46BFCD482F837AF58D620773DFAA4B918A751A1BA04BBD0C37EE2E4B` |

## Conclusão

- O mapeamento em `docs/environment/ENVIRONMENT_INVENTORY.md` está **confirmado**:
  `bg_prog_artpro+_v240` → FileVersion/ProductVersion `24.03.10017`.
- A instalação `bg_prog_artpro+_v250` corresponde à versão **`25.03.116`** (não a uma
  string genérica "25.x"). `FileDescription` = `ArtPro+ 25.03`.
- **Ambos os caminhos existem.** Nenhum deles é ausente.
- A string de versão vem do recurso de versão PE (VERSIONINFO) e é consistente entre
  `FileVersion`, `ProductVersion`, `FileDescription` e os campos numéricos (Raw).

## Notas de rastreabilidade

- Fonte dos metadados: recurso VERSIONINFO lido via `Get-Item.VersionInfo` (PowerShell 5.1),
  o mesmo dado que `scripts/inspect_pe.py` lê do diretório `.rsrc`.
- Hashes SHA-256 obtidos com `Get-FileHash -Algorithm SHA256` (idêntico ao usado no
  `manifest.json` do projeto).
- Nenhuma análise de código, importação no Ghidra ou decompilação foi realizada.
