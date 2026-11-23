# fix_permissions_and_cmake_sources.ps1
# Script para ser executado no PowerShell como ADMINISTRADOR

# --- CONFIGURAÇÕES ---
$PROJECT_ROOT = "H:\Desktop\ArtPlus"

Write-Host "=== SCRIPT DE CORREÇÃO DE PERMISSÕES E CMAKE ===" -ForegroundColor Cyan

# --- FUNÇÕES ---
function Grant-FullControl {
    param([Parameter(Mandatory=$true)]$Path)
    Write-Host "`n[1] Concedendo controle total em: $Path"
    icacls $Path /grant "$($env:USERNAME):F" /T 2>&1
    if ($LASTEXITCODE -eq 0) { Write-Host "   ✅ Concedido" } else { Write-Host "   ❌ Falha (Código: $LASTEXITCODE)" }
}

function Edit-CMakeLists {
    Write-Host "`n[2] Editando CMakeLists.txt (após permissões)..."
    
    # Lógica: ler, substituir, escrever
    # Como o tool 'edit' do OpenCode ainda não funcionou, usamos PowerShell
    
    # Primeiro, vamos garantir que o arquivo tem conteúdo legível
    $content = Get-Content "$PROJECT_ROOT\CMakeLists.txt" -Raw
    
    # Verificar se já têm as variáveis de fontes
    if ($content -match "set\(DOCUMENT_SOURCES") {
        Write-Host "   📝 Já contém set(DOCUMENT_SOURCES) - substituindo para curingas..."
        
        # Substituir a lista explícita por curinga
        $oldDoc = "set(DOCUMENT_SOURCES
    src/document/document_model.cpp
    src/document/document_model.h
    src/document/document_serializer.cpp
    src/document/document_serializer.h
    src/document/undo.cpp
    src/document/undo.h
)"
        $newDoc = "set(DOCUMENT_SOURCES src/document/*.cpp)"
        
        $content = $content -replace [regex]::Escape($oldDoc), $newDoc
        
        $oldPdf = "set(PDF_SOURCES
    src/pdf/pdf_types.cpp
    src/pdf/pdf_types.h
    src/pdf/pdf_lexer.cpp
    src/pdf/pdf_lexer.h
    src/pdf/pdf_parser.h
    src/pdf/pdf_document.cpp
    src/pdf/pdf_document.h
    src/pdf/pdf_content.cpp
    src/pdf/pdf_content.h
    src/pdf/pdf_importer.cpp
    src/pdf/pdf_importer.h
    src/pdf/pdf_exporter.cpp
    src/pdf/pdf_exporter.h
)"
        $newPdf = "set(PDF_SOURCES src/pdf/*.cpp)"
        
        $content = $content -replace [regex]::Escape($oldPdf), $newPdf
        
        # Escrever de volta
        $content | Out-File -Encoding UTF8 -NoNewFile "$PROJECT_ROOT\CMakeLists.txt"
        Write-Host "   ✅ CMakeLists.txt atualizado com curingas"
    } else {
        Write-Host "   ⚠️ Não encontrou set(DOCUMENT_SOURCES)... verificando estrutura atual"
        # Mostrar primeiro trecho para debug
        $lines = Get-Content "$PROJECT_ROOT\CMakeLists.txt" -TotalCount 50
        $lines | ForEach-Object { Write-Host "$_" }
    }
}

# --- EXECUÇÃO ---
# 1. Conceder permissões
Grant-FullControl -Path "$PROJECT_ROOT\CMakeLists.txt"
Grant-FullControl -Path "$PROJECT_ROOT\rag\evidence\F-005"
Grant-FullControl -Path "$PROJECT_ROOT\rag\evidence"

# 2. Espera um momento para as ACLs serem propagadas
Write-Host "`n[⏳] Aguardando propagação de ACLs (3 segundos)..."
Start-Sleep -Seconds 3

# 3. Editar CMakeLists (agora que permissões foram concedidas)
Edit-CMakeLists

# 4. Testar escrita
Write-Host "`n[3] Testando escrita de manifest.json..."
$manifestPath = "$PROJECT_ROOT\rag\evidence\F-005\manifest.json"
$testContent = @{id="TEST"; versao="1"} | ConvertTo-Json
Set-Content -Path $manifestPath -Value $testContent -Encoding UTF8

if (Test-Path $manifestPath) {
    Write-Host "   ✅ Escrita funcionou em rag/evidence/F-005/"
    # Limpar arquivo de teste
    Remove-Item $manifestPath -Force
} else {
    Write-Host "   ❌ Ainda bloqueado. Pode precisar reiniciar o OpenCode."
}