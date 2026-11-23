param([Parameter(Mandatory=$true)][string]$TitleMatch = 'ArtPro+')

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class Act {
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, IntPtr pid);
  [DllImport("user32.dll")] public static extern IntPtr AttachThreadInput(uint a, uint b, bool f);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
  [DllImport("user32.dll")] public static extern IntPtr SetFocus(IntPtr h);
}
"@

$target = Get-Process | Where-Object { $_.MainWindowTitle -like "*$TitleMatch*" -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $target) { "NO_WINDOW"; exit 2 }

# minimize every other visible top-level window from other processes
foreach ($p in (Get-Process | Where-Object { $_.MainWindowHandle -ne 0 -and $_.Id -ne $target.Id })) {
  try { [Act]::ShowWindow($p.MainWindowHandle, 6) | Out-Null } catch {}
}
Start-Sleep -Milliseconds 300

$h = $target.MainWindowHandle
if ([Act]::IsIconic($h)) { [Act]::ShowWindow($h, 9) | Out-Null }
$fg = [Act]::GetForegroundWindow()
$fgThread = [Act]::GetWindowThreadProcessId($fg, [IntPtr]::Zero)
$curThread = [Act]::GetCurrentThreadId()
[Act]::AttachThreadInput($fgThread, $curThread, $true) | Out-Null
[Act]::BringWindowToTop($h) | Out-Null
[Act]::SetForegroundWindow($h) | Out-Null
[Act]::SetFocus($h) | Out-Null
[Act]::AttachThreadInput($fgThread, $curThread, $false) | Out-Null
Start-Sleep -Milliseconds 400
"fg=$([Act]::GetForegroundWindow()) target=$h title=$($target.MainWindowTitle)"
