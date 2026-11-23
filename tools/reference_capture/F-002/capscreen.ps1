param(
  [Parameter(Mandatory=$true)][string]$Out,
  [int]$X=0, [int]$Y=0, [int]$W=0, [int]$H=0
)

Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class CapF002 {
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
}
"@

$dir = Split-Path -Parent $Out
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }

# Se região não informada, captura o monitor principal (tela toda)
if ($W -le 0) { $W = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Width }
if ($H -le 0) { $H = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Height }

$bmp = New-Object System.Drawing.Bitmap($W, $H)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($X, $Y, 0, 0, (New-Object System.Drawing.Size($W, $H)))
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"{'out':'$Out','bytes':$((Get-Item $Out).Length),'size':[$W,$H]}"
