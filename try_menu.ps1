param()
Add-Type -AssemblyName Microsoft.VisualBasic
Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class W32M {
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
}
"@
$proc = Get-Process ArtPro+ | Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1
$h = $proc.MainWindowHandle
if ([W32M]::IsIconic($h)) { [W32M]::ShowWindow($h, 9) | Out-Null }
try { [Microsoft.VisualBasic.Interaction]::AppActivate($proc.Id) | Out-Null } catch { "AppActivateERR:$_" }
Start-Sleep -Milliseconds 600
[W32M]::BringWindowToTop($h) | Out-Null
[W32M]::SetForegroundWindow($h) | Out-Null
Start-Sleep -Milliseconds 500
$fg = [W32M]::GetForegroundWindow()
"FG_MATCH=" + ($fg -eq $h) + " fg=" + $fg + " h=" + $h
[System.Windows.Forms.SendKeys]::SendWait("%f")
Start-Sleep -Milliseconds 900
"ALT_F_SENT"
