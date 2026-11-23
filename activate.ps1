Add-Type @"
using System;
using System.Runtime.InteropServices;
public class W32Sw {
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern void SwitchToThisWindow(IntPtr h, bool alt);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
}
"@
$p = Get-Process ArtPro+ | Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1
$h = $p.MainWindowHandle
if ([W32Sw]::IsIconic($h)) { [W32Sw]::ShowWindow($h, 9) | Out-Null }
[W32Sw]::SwitchToThisWindow($h, $true)
Start-Sleep -Milliseconds 700
"FG=" + [W32Sw]::GetForegroundWindow() + " h=" + $h + " match=" + ([W32Sw]::GetForegroundWindow() -eq $h)
