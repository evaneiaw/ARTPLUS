# Ambiente ArtPlus — Configuração Canônica (v24.03.10017)

Este documento contém a única fonte de verdade para todos os caminhos e versões de ferramentas e artefatos de referência do projeto ArtPlus. **Todos os agentes devem consultar este documento ou scripts de descoberta automática em vez de manter caminhos codificados.**

## 1. Configuração do Sistema
- **Raiz do Repositório:** `H:\Desktop\ArtPlus`
- **Branch Canônica:** `master`
- **Versão Referência ArtPro+:** `v24.03.10017`
- **Caminho ArtPro+ Ref:** `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows`
- **Versão Histórica ArtPro+:** `v25.03.116` (`C:\Esko\bg_prog_artpro+_v250`)

## 2. Ferramentas de Engenharia Reversa
- **Ghidra:** `H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC` (Requer JDK 25: `C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot`)
- **REA CLI:** `C:\Users\Evanei\.local\share\opencode\rea-side` (Usa Node 26.13.1: `C:\Users\Evanei\.local\share\opencode\node-v26.13.1\node.exe`)
- **PC-Control:** MCP `desktop-control-mcp` 0.1.0 (requer `mcp<2` instalado).

## 3. Toolchain de Build
- **CMake:** Kitware absoluto: `C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe`
- **Compilador:** MinGW POSIX **MSVCRT** (`...\BrechtSanders.WinLibs.POSIX.MSVCRT_...\mingw64\bin\g++.exe`)
- **Preset:** `mingw-msvcrt` → `release-mingw`

## 4. Diretórios de Trabalho e Artefatos
- **Build Compartilhado:** `build/` (Uso restrito a `ARTPLUS_GATE_BUILD_DIR=build_<escopo>`)
- **Scripts de Gate:** `scripts/` (Inclui `gate.py`, `check_version.py`, `preflight.py`)
- **Logs de Build:** `docs/testing/gates/logs/`
- **Raiz do Projeto:** `H:\Desktop\ArtPlus`
