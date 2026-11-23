$env:JAVA_HOME="C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot"
$headless="H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat"
$projects="H:\Desktop\ArtPlus\tools\ghidra_projects"
$binario="C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll"
$log="H:\Desktop\ArtPlus\tools\ghidra_analysis\DocumentMarks.final_import.log"
$errlog="H:\Desktop\ArtPlus\tools\ghidra_analysis\DocumentMarks.final_import.log.err"
$scriptPath="H:\Desktop\ArtPlus\tools\ghidra_analysis\ghidra_scripts"
$empty = Join-Path $env:TEMP "ghidra-empty-stdin.txt"

Set-Content -Path $empty -Value ""

cmd /c "`"$headless`" `"$projects`" DocMarks -import `"$binario`" -overwrite -scriptPath `"$scriptPath`" -postScript ExportFunctions.java ExportMarksFocus.java" | Set-Content -Path $log

Write-Host "Import completed, check $log"
