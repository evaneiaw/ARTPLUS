$evidenceDir = 'H:\Desktop\ArtPlus\rag\evidence\F-006\ghidra'
$csvPaths = @{
  'Document' = 'H:\Desktop\ArtPlus\rag\ghidra\exports\Document.dll'
  'NDLModel' = 'H:\Desktop\ArtPlus\rag\ghidra\exports\NDLModel.dll'
}

foreach ($mod in @('Document','NDLModel')) {
  $csvDir = $csvPaths[$mod]
  $callgraph = Import-Csv "$csvDir\callgraph_simplified.csv"

  Get-ChildItem -Path $evidenceDir -Filter "${mod}__*.md" | ForEach-Object {
    $file = $_
    if ($file.Name -match '__([0-9a-fA-F]{8,})\.md$') {
      $addr = $matches[1].ToLower()

      $callers = $callgraph | Where-Object { $_.CalleeAddress -eq $addr }
      $callerLines = @()
      foreach ($c in $callers) {
        $callerLines += "- caller $($c.CallerAddress) ($($c.CallerName))"
      }

      $content = Get-Content -Path $file.FullName -Raw
      if ($content.Contains('## Xrefs de entrada')) { return }

      $xrefSection = "`n`n## Xrefs de entrada (callers)`n`n"
      if ($callerLines.Count -eq 0) {
        $xrefSection += "_Nenhum caller direto detectado no callgraph (chamada provavelmente via vtable/service locator ou ponteiro de funcao)._`n"
      } else {
        $xrefSection += ($callerLines -join "`n") + "`n"
      }
      $xrefSection += "`n## Xrefs de saida (callees)`n`n"
      $xrefSection += "_Ver pseudocodigo acima - chamadas a FUN_* e simbolos nomeados (ex: SwitchToWorkingFile, GODocument::Save, WriteOptions::IsSaveAs) representam os callees._`n"

      $newContent = $content + $xrefSection
      Set-Content -Path $file.FullName -Value $newContent -NoNewline
    }
  }
}
Write-Host "Enriquecimento concluido."