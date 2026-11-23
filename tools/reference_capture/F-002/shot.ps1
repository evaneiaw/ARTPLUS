param(
  [Parameter(Mandatory=$true)][string]$Out,
  [string]$TitleMatch = 'ArtPro+',
  [switch]$Region,
  [int]$X=0, [int]$Y=0, [int]$W=0, [int]$H=0
)

Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class W32F002 {
  [DllImport("user32.dll", SetLastError=true)] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
}
"@
[W32F002]::SetProcessDPIAware() | Out-Null

$proc = Get-Process | Where-Object { $_.MainWindowTitle -like "*$TitleMatch*" -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $proc) { Write-Output "NO_WINDOW:$TitleMatch"; exit 2 }
if ([W32F002]::IsIconic($proc.MainWindowHandle)) { [W32F002]::ShowWindow($proc.MainWindowHandle, 9) | Out-Null }
[W32F002]::SetForegroundWindow($proc.MainWindowHandle) | Out-Null
Start-Sleep -Milliseconds 350

$r = New-Object W32F002+RECT
[W32F002]::GetWindowRect($proc.MainWindowHandle, [ref]$r) | Out-Null

$bx = $r.Left; $by = $r.Top; $bw = $r.Right - $r.Left; $bh = $r.Bottom - $r.Top
if ($Region -and $W -gt 0) { $bx=$X; $by=$Y; $bw=$W; $bh=$H }

$bmp = New-Object System.Drawing.Bitmap($bw, $bh)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($bx, $by, 0, 0, (New-Object System.Drawing.Size($bw, $bh)))
$dir = Split-Path -Parent $Out
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"{'window':'$($proc.MainWindowTitle)','rect':[$bx,$by,$bw,$bh],'out':'$Out','bytes':$((Get-Item $Out).Length)}"
