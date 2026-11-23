$env:JAVA_HOME = 'C:\Program Files\Eclipse Adoptium\jdk-25.0.5.8-hotspot'
$headless = 'H:\Desktop\ArtPlus\tools\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat'
$projects = 'H:\Desktop\ArtPlus\tools\ghidra_projects'
$work = 'H:\Desktop\ArtPlus\tools\ghidra_analysis'
$empty = Join-Path $env:TEMP 'ghidra-empty-stdin.txt'
New-Item -ItemType File -Force $empty | Out-Null
$argsList = @($headless, $projects, 'ArtProPlus_PDFDocument', '-process', 'Document.dll', '-noanalysis',
  '-scriptPath', "$work\ghidra_scripts",
  '-postScript', 'DecompileAddr.java', '0x1800FAE70', '0x1800FAEE0')
$p = Start-Process -FilePath 'cmd.exe' -ArgumentList (@('/c') + $argsList) -RedirectStandardInput $empty -RedirectStandardOutput "$work\Document.getpagebox.log" -RedirectStandardError "$work\Document.getpagebox.log.err" -WindowStyle Hidden -PassThru
Wait-Process -Id $p.Id -Timeout 600 -ErrorAction SilentlyContinue
Get-Content "$work\Document.getpagebox.log" | Select-String -Pattern 'WROTE|NO FUNCTION|FAILED|SCRIPT ERROR|error:' | Select-Object -Last 10 | ForEach-Object { $_.Line }
Get-ChildItem 'H:\Desktop\ArtPlus\rag\ghidra\exports\Document.dll\decompiled_addr' -ErrorAction SilentlyContinue | Select-Object Name, Length
