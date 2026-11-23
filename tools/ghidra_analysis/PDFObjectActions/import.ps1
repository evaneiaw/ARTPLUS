$ErrorActionPreference = 'Stop'
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$env:JAVA_HOME = 'C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot'
$headless = 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat'
$projects = 'H:\Desktop\ArtPlus\tools\ghidra_projects'
$projName = 'ArtProPlus'
$target = 'C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\PDFObjectActions.dll'
$log = 'H:\Desktop\ArtPlus\tools\ghidra_analysis\PDFObjectActions\import.log'
$errLog = 'H:\Desktop\ArtPlus\tools\ghidra_analysis\PDFObjectActions\import.log.err'
$empty = Join-Path $env:TEMP 'ghidra-empty-stdin.txt'
New-Item -ItemType File -Force $empty | Out-Null
$argList = @($projects, $projName, '-import', $target, '-overwrite')
$p = Start-Process $headless -ArgumentList $argList -RedirectStandardInput $empty -RedirectStandardOutput $log -RedirectStandardError $errLog -WindowStyle Hidden -PassThru
Write-Output ('PID=' + $p.Id)
$p.Id | Out-File 'H:\Desktop\ArtPlus\tools\ghidra_analysis\PDFObjectActions\import.pid' -Encoding ascii

