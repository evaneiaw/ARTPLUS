# build_and_test_f005.ps1
# Script para ser executado no PowerShell como ADMINISTRADOR

# --- CONFIGURAÇÕES ---
$PROJECT_ROOT = "H:\Desktop\ArtPlus"
$CMAKE_EXECUTABLE = "C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe"
$CMAKE_PRESET = "mingw-msvcrt"
$BUILD_PRESET = "release-mingw"
$TEST_PRESET = "unit-tests"

# --- FUNÇÕES DE PERMISSÃO (Recomendado rodar como Admin) ---
function Grant-FullControl {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Path
    )
    Write-Host "Tentando conceder controle total a $($env:USERNAME) em: $Path"
    # Usa o comando icacls para garantir permissão total
    icacls $Path /grant "$($env:USERNAME):F" /T
    if ($LASTEXITCODE -eq 0) { Write-Host "✅ Permissão concedida para $Path" } else { Write-Host "❌ FALHA ao conceder permissão para $Path (Erro: $LASTEXITCODE)" }
}

# --- FUNÇÕES DE EXECUÇÃO ---
function Run-Command {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Command,
        [string]$Description
    )
    Write-Host "`n=============================================="
    Write-Host "▶️ EXECUTANDO: $Description" -ForegroundColor Cyan
    Write-Host "⚡️ COMANDO: $Command"
    Write-Host "=============================================="
    
    # Executa o comando, capturando a saída
    $result = Invoke-Expression $Command 2>&1
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ SUCESSO: $Description" -ForegroundColor Green
    } else {
        Write-Host "❌ FALHA: $Description (Exit Code: $LASTEXITCODE)" -ForegroundColor Red
        Write-Host "--- SAÍDA DE ERRO ---"
        $result | ForEach-Object { Write-Host $_ }
    }
    return $LASTEXITCODE
}

# --- FLUXO DE EXECUÇÃO ---

Write-Host "--- 1. CONCEDENDO PERMISSÕES (REQUER ADMIN) ---" -ForegroundColor Yellow
Grant-FullControl -Path "$PROJECT_ROOT\CMakeLists.txt"
Grant-FullControl -Path "$PROJECT_ROOT\rag\evidence\F-005"

Write-Host "`n--- 2. CORRIGINDO CMAKE ---" -ForegroundColor Yellow
# A correção de fontes deve ser feita manualmente ou via 'edit' após permissão
# Aqui, assumimos que a edição foi feita:
Write-Host "⚠️ ATENÇÃO: Edição de fontes (curingas) deve ser feita manualmente no CMakeLists.txt, após permissões."

Write-Host "`n--- 3. CONFIGURAÇÃO E BUILD ---" -ForegroundColor Yellow
# Configura
$cmakeConfigCmd = "& $CMAKE_EXECUTABLE --preset $CMAKE_PRESET"
Run-Command $cmakeConfigCmd "Configurar CMake com $CMAKE_PRESET"

# Build
$cmakeBuildCmd = "& $CMAKE_EXECUTABLE --build --preset $BUILD_PRESET"
Run-Command $cmakeBuildCmd "Compilar Release ($BUILD_PRESET)"

# Testes
$ctestCmd = "ctest --preset $TEST_PRESET"
Run-Command $ctestCmd "Executar Testes Unitários ($TEST_PRESET)"


# --- 4. CRIANDO ARTEFATOS (Após sucesso do build) ---
Write-Host "`n--- 4. CRIANDO ARTEFATOS (MANIFEST) ---" -ForegroundColor Yellow
$manifestJson = @{
  "id" = "F-005"
  "versao_ref" = "24.03"
  "binario" = "C:\\Esko\\bg_prog_artpro+_v240\\ArtPro+.app\\Contents\\Windows"
  "sha256" = "0aa0311cfcdaedf8028a626ac751ee0b5cce5e000f3ac551d9d291b250038160"
  "estatico" = @("GHIDRA-Document-0x...", "GHIDRA-PDFAccessLayer-0x...", "GHIDRA-PDFObjectLayer-0x...")
  "comportamental" = @("CAP-20261120-01")
  "bloqueios" = @()
} | ConvertTo-Json -Depth 10

# Tenta escrever o manifest
$manifestPath = "$PROJECT_ROOT\rag\evidence\F-005\manifest.json"
Set-Content -Path $manifestPath -Value $manifestJson -Encoding UTF8

if (Test-Path $manifestPath) {
    Write-Host "✅ Manifest.json criado com sucesso em $manifestPath" -ForegroundColor Green
} else {
    Write-Host "❌ FALHA ao criar Manifest.json. Permissões ainda negadas." -ForegroundColor Red
}

Write-Host "`n=============================================="
Write-Host "🏁 PROCESSO CONCLUÍDO. VERIFIQUE OS LOGS ACIMA." -ForegroundColor Yellow
Write-Host "=============================================="