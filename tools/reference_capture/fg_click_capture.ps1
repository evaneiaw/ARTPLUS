param(
  [Parameter(Mandatory=$true)][string]$Out,
  [Parameter(Mandatory=$true)][string]$ProcessName,
  [int]$X = -1, [int]$Y = -1,
  [string]$Keys = "",
  [string]$Text = "",
  [int]$DelayMs = 1200,
  [int]$WaitBeforeMs = 250
)
# Foreground + clique/teclas/texto + captura, tudo em um proceso (evita roubo de foco).
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class FgClick2 {
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint d, int extra);
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint f, int extra);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
}
"@
[FgClick2]::SetProcessDPIAware() | Out-Null

$p = Get-Process -Name $ProcessName -ErrorAction SilentlyContinue |
     Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $p) { throw "processo '$ProcessName' sem janela principal" }
$h = $p.MainWindowHandle

$fg = [FgClick2]::GetForegroundWindow()
$dummy = 0
$fgThread = [FgClick2]::GetWindowThreadProcessId($fg, [ref]$dummy)
$cur = [FgClick2]::GetCurrentThreadId()
[FgClick2]::AttachThreadInput($cur, $fgThread, $true) | Out-Null
if ($X -lt 0) { [FgClick2]::ShowWindow($h, 3) | Out-Null }
[FgClick2]::BringWindowToTop($h) | Out-Null
$ok = [FgClick2]::SetForegroundWindow($h)
[FgClick2]::AttachThreadInput($cur, $fgThread, $false) | Out-Null
Start-Sleep -Milliseconds $WaitBeforeMs

$vkmap = @{
  'esc'=27; 'escape'=27; 'enter'=13; 'return'=13; 'tab'=9; 'back'=8; 'delete'=46;
  'ctrl'=17; 'shift'=16; 'alt'=18; 'f4'=115; 'space'=32; 'o'=79; 'a'=65; 's'=83;
}
function Get-Vk([string]$name) {
  $k = $name.Trim().ToLower()
  if ($vkmap.ContainsKey($k)) { return [byte]$vkmap[$k] }
  if ($k.Length -eq 1) { return [byte]([char]::ToUpper($k[0])) }
  throw "tecla desconhecida: $name"
}

if ($X -ge 0 -and $Y -ge 0) {
  [FgClick2]::SetCursorPos($X, $Y) | Out-Null
  Start-Sleep -Milliseconds 120
  [FgClick2]::mouse_event(0x0002, 0, 0, 0, 0)
  Start-Sleep -Milliseconds 60
  [FgClick2]::mouse_event(0x0004, 0, 0, 0, 0)
  Start-Sleep -Milliseconds 350
}
if ($Keys -ne "") {
  $parts = $Keys -split '\+'
  $vks = @()
  foreach ($part in $parts) { $vks += Get-Vk $part }
  # teclas modificadoras primeiro; solta em ordem inversa
  foreach ($vk in $vks) { [FgClick2]::keybd_event($vk, 0, 0, 0); Start-Sleep -Milliseconds 50 }
  for ($i = $vks.Count - 1; $i -ge 0; $i--) { [FgClick2]::keybd_event($vks[$i], 0, 2, 0); Start-Sleep -Milliseconds 50 }
  Start-Sleep -Milliseconds 400
}
if ($Text -ne "") {
  [System.Windows.Forms.SendKeys]::SendWait($Text)
  Start-Sleep -Milliseconds 500
}
if ($DelayMs -gt 0) { Start-Sleep -Milliseconds $DelayMs }

$bmp = New-Object System.Drawing.Bitmap(1920, 1080)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen(0, 0, 0, 0, (New-Object System.Drawing.Size(1920, 1080)))
$dir = Split-Path -Parent $Out
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose(); $bmp.Dispose()
"{'out':'$Out','pid':$($p.Id),'set_foreground':$($ok.ToString().ToLower()),'click':[$X,$Y],'keys':'$Keys','text_len':$($Text.Length)}"
