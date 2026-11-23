Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WinEnum {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
}
"@
$p = (Get-Process ArtPro+ | Where-Object { $_.MainWindowHandle -ne 0 } | Select-Object -First 1)
$targetPid = $p.Id
$list = New-Object System.Collections.ArrayList
$script:tp = $targetPid
$cb = [WinEnum+EnumProc]{ param($h,$l)
  $wpid=0; [WinEnum]::GetWindowThreadProcessId($h,[ref]$wpid) | Out-Null
  if ($wpid -eq $script:tp) {
    $sb = New-Object System.Text.StringBuilder 256
    [WinEnum]::GetWindowText($h,$sb,256) | Out-Null
    $cn = New-Object System.Text.StringBuilder 256
    [WinEnum]::GetClassName($h,$cn,256) | Out-Null
    [void]$list.Add(("HWND={0} vis={1} class={2} title=[{3}]" -f $h,[WinEnum]::IsWindowVisible($h),$cn.ToString(),$sb.ToString()))
  }
  return $true
}
[WinEnum]::EnumWindows($cb,[IntPtr]::Zero) | Out-Null
"PID=$targetPid"
$list
"FG=" + [WinEnum]::GetForegroundWindow()
