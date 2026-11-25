param(
  [Parameter(Mandatory=$true)][string]$Out,
  [string]$ProcessName = 'ArtPro+',
  [int]$MenuX = 196, [int]$MenuY = 32,
  [int]$Downs = 18,
  [string]$OutBefore = ""
)
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class FgNav {
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint d, int extra);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
}
"@
[FgNav]::SetProcessDPIAware() | Out-Null

$p = Get-Process -Name $ProcessName -ErrorAction SilentlyContinue |
     Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $p) { throw "processo '$ProcessName' sem janela principal" }
$h = $p.MainWindowHandle

$fg = [FgNav]::GetForegroundWindow()
$dummy = 0
$fgThread = [FgNav]::GetWindowThreadProcessId($fg, [ref]$dummy)
$cur = [FgNav]::GetCurrentThreadId()
[FgNav]::AttachThreadInput($cur, $fgThread, $true) | Out-Null
[FgNav]::ShowWindow($h, 3) | Out-Null
[FgNav]::BringWindowToTop($h) | Out-Null
[FgNav]::SetForegroundWindow($h) | Out-Null
[FgNav]::AttachThreadInput($cur, $fgThread, $false) | Out-Null
Start-Sleep -Milliseconds 400

function Shot([string]$path) {
  $bmp = New-Object System.Drawing.Bitmap(1920, 1080)
  $g = [System.Drawing.Graphics]::FromImage($bmp)
  $g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(1920, 1080)))
  $dir = Split-Path -Parent $path
  if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
  $bmp.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
  $g.Dispose(); $bmp.Dispose()
}

# abre o menu Prepress por clique real
[FgNav]::SetCursorPos($MenuX, $MenuY) | Out-Null
Start-Sleep -Milliseconds 150
[FgNav]::mouse_event(0x0002, 0, 0, 0, 0)
Start-Sleep -Milliseconds 70
[FgNav]::mouse_event(0x0004, 0, 0, 0, 0)
Start-Sleep -Milliseconds 900

# navega por teclado ate o item (evita hotkey global Ctrl+Alt+G do Google Drive)
[System.Windows.Forms.SendKeys]::SendWait("{DOWN $Downs}")
Start-Sleep -Milliseconds 400
if ($OutBefore -ne "") { Shot $OutBefore }
# Step & Repeat e um submenu; RIGHT abre o submenu, ENTER aciona o item "Make Grid"
[System.Windows.Forms.SendKeys]::SendWait("{RIGHT}")
Start-Sleep -Milliseconds 900
Shot ($Out -replace '\.png$','-submenu.png')
[System.Windows.Forms.SendKeys]::SendWait("{ENTER}")
Start-Sleep -Milliseconds 1600
Shot ($Out -replace '\.png$','-t4.png')
Start-Sleep -Milliseconds 2500
Shot $Out
"{'out':'$Out','pid':$($p.Id),'menu':[$MenuX,$MenuY],'downs':$Downs,'before':'$OutBefore'}"
