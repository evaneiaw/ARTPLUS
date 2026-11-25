param(
  [Parameter(Mandatory=$true)][string]$Out,
  [int]$X=0, [int]$Y=0, [int]$W=1920, [int]$H=1080
)
# Captura de tela sem ativar/alterar nenhuma janela (sem SetForegroundWindow).
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Dpi1 {
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
}
"@
[Dpi1]::SetProcessDPIAware() | Out-Null

$bmp = New-Object System.Drawing.Bitmap($W, $H)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($X, $Y, 0, 0, (New-Object System.Drawing.Size($W, $H)))
$dir = Split-Path -Parent $Out
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"{'out':'$Out','rect':[$X,$Y,$W,$H]}"
