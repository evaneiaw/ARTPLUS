$env:JAVA_HOME="C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot"
$headless="H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat"
$projects="H:\Desktop\ArtPlus\tools\ghidra_projects"
$binario="C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll"
$log="H:\Desktop\ArtPlus\tools\ghidra_analysis\DocumentMarks.import.log"
$errlog="H:\Desktop\ArtPlus\tools\ghidra_analysis\DocumentMarks.import.log.err"
$empty = Join-Path $env:TEMP "ghidra-empty-stdin.txt"

Set-Content -Path $empty -Value ""

cmd /c "`"$headless`" `"$projects`" ArtProPlus -import `"$binario`" -overwrite" | Set-Content -Path $log

# Check if project was created
if (Test-Path "$projects\ArtProPlus") {
    Write-Host "Import completed successfully"
} else {
    Write-Host "Import may have failed"
}
