param(
  [Parameter(Mandatory=$true)][string]$Out,
  [string]$ProcessName = 'ArtPro+'
)
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Rec {
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
  [DllImport("user32.dll")] public static extern bool RedrawWindow(IntPtr h, IntPtr r, IntPtr rgn, uint flags);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
}
"@
[Rec]::SetProcessDPIAware() | Out-Null
$p = Get-Process -Name $ProcessName -ErrorAction SilentlyContinue |
     Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $p) { throw "processo '$ProcessName' sem janela principal" }
$h = $p.MainWindowHandle

# 1) sai do modo interativo pendente
[System.Windows.Forms.SendKeys]::SendWait("{ESC}")
Start-Sleep -Milliseconds 700
[System.Windows.Forms.SendKeys]::SendWait("{ESC}")
Start-Sleep -Milliseconds 500

# 2) minimiza/restaura para forcar repaint completo (nao fecha o app)
[Rec]::ShowWindow($h, 6) | Out-Null
Start-Sleep -Milliseconds 900
[Rec]::ShowWindow($h, 9) | Out-Null
Start-Sleep -Milliseconds 900

$fg = [Rec]::GetForegroundWindow()
$dummy = 0
$fgThread = [Rec]::GetWindowThreadProcessId($fg, [ref]$dummy)
$cur = [Rec]::GetCurrentThreadId()
[Rec]::AttachThreadInput($cur, $fgThread, $true) | Out-Null
[Rec]::BringWindowToTop($h) | Out-Null
[Rec]::SetForegroundWindow($h) | Out-Null
[Rec]::AttachThreadInput($cur, $fgThread, $false) | Out-Null
[Rec]::RedrawWindow($h, [IntPtr]::Zero, [IntPtr]::Zero, 0x0485) | Out-Null
Start-Sleep -Milliseconds 1500

$bmp = New-Object System.Drawing.Bitmap(1920, 1080)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(1920, 1080)))
$dir = Split-Path -Parent $Out
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"{'out':'$Out','pid':$($p.Id),'title':'$($p.MainWindowTitle)','responding':$($p.Responding.ToString().ToLower())}"
