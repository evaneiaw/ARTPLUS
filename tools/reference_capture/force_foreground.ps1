param(
  [Parameter(Mandatory=$true)][string]$ProcessName
)
# Traz a janela principal de um processo para o primeiro plano sem fechar nada.
# Usa AttachThreadInput porque SetForegroundWindow direto falha por foreground lock.
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Fg {
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
}
"@
$p = Get-Process -Name $ProcessName -ErrorAction SilentlyContinue |
     Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $p) { throw "processo '$ProcessName' sem janela principal" }
$h = $p.MainWindowHandle
$fg = [Fg]::GetForegroundWindow()
$dummy = 0
$fgThread = [Fg]::GetWindowThreadProcessId($fg, [ref]$dummy)
$curThread = [Fg]::GetCurrentThreadId()
[Fg]::AttachThreadInput($curThread, $fgThread, $true) | Out-Null
[Fg]::ShowWindow($h, 3) | Out-Null   # SW_MAXIMIZE
[Fg]::BringWindowToTop($h) | Out-Null
$ok = [Fg]::SetForegroundWindow($h)
[Fg]::AttachThreadInput($curThread, $fgThread, $false) | Out-Null
"{'pid':$($p.Id),'hwnd':$($h.ToInt64()),'title':'$($p.MainWindowTitle)','set_foreground':$($ok.ToString().ToLower())}"
