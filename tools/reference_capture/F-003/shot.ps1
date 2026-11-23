param(
  [Parameter(Mandatory=$true)][string]$Out,
  [int]$Left = 0, [int]$Top = 0, [int]$Width = 1920, [int]$Height = 1080
)
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$bmp = New-Object System.Drawing.Bitmap $Width, $Height
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($Left, $Top, 0, 0, (New-Object System.Drawing.Size $Width, $Height))
$g.Dispose()
$dir = Split-Path -Parent $Out
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$bmp.Dispose()
Write-Output ("saved: " + $Out + " " + (Get-Item $Out).Length + " bytes")
