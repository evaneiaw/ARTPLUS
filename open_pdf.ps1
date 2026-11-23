param([string]$PdfPath)
Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class W32Open {
  [DllImport("user32.dll", SetLastError=true)] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
}
"@
$proc = Get-Process ArtPro+ -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1
if (-not $proc) { Write-Output "NO_ARTPRO"; exit 1 }
if ([W32Open]::IsIconic($proc.MainWindowHandle)) { [W32Open]::ShowWindow($proc.MainWindowHandle, 9) | Out-Null }
[W32Open]::SetForegroundWindow($proc.MainWindowHandle) | Out-Null
Start-Sleep -Milliseconds 700
[System.Windows.Forms.SendKeys]::SendWait("^O")
Start-Sleep -Milliseconds 1500
Write-Output "CTRL_O_SENT"
