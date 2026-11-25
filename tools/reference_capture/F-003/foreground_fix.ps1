# foreground_fix.ps1
# Remove o foreground lock do Windows sobre uma janela do ArtPro+
# e a coloca em primeiro plano, pronta para interacao via pc-control.
# Uso: powershell -NoProfile -File foreground_fix.ps1 [-TitleMatch "ArtPro+ License Info"]
param([string]$TitleMatch = "ArtPro+ License Info")

Add-Type @"
using System;
using System.Runtime.InteropServices;
using System.Text;
public class FgFix {
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
  [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int nCmdShow);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);

  public static IntPtr FindByTitle(string match) {
    IntPtr result = IntPtr.Zero;
    EnumProc cb = (IntPtr h, IntPtr l) => {
      StringBuilder sb = new StringBuilder(256);
      int len = GetWindowText(h, sb, 256);
      if (len > 0 && sb.ToString().IndexOf(match, StringComparison.OrdinalIgnoreCase) >= 0) {
        result = h;
        return false;
      }
      return true;
    };
    EnumWindows(cb, IntPtr.Zero);
    return result;
  }
}
"@

$h = [FgFix]::FindByTitle($TitleMatch)
if ($h -eq [IntPtr]::Zero) {
  Write-Output "RESULT=WINDOW_NOT_FOUND title=[$TitleMatch]"
  exit 1
}

$curThread = [FgFix]::GetCurrentThreadId()
$fg = [FgFix]::GetForegroundWindow()
$tp = 0
$fgThread = [FgFix]::GetWindowThreadProcessId($fg, [ref]$tp)
$fgPid = $tp

$tp2 = 0
$tgtThread = [FgFix]::GetWindowThreadProcessId($h, [ref]$tp2)
$tgtPid = $tp2

Write-Output ("HWND=0x{0:X8} PID={1} TID={2}" -f $h.ToInt64(), $tgtPid, $tgtThread)
Write-Output ("FG_HWND=0x{0:X8} FG_PID={2} FG_TID={1}" -f $fg.ToInt64(), $fgThread, $fgPid)
Write-Output ("CUR_TID={0}" -f $curThread)

# Anexa entradas de thread para burcar o foreground lock do Windows
[FgFix]::AttachThreadInput($curThread, $fgThread, $true) | Out-Null
[FgFix]::AttachThreadInput($curThread, $tgtThread, $true) | Out-Null

[FgFix]::ShowWindow($h, 5) | Out-Null     # SW_SHOW
[FgFix]::BringWindowToTop($h) | Out-Null
$sf = [FgFix]::SetForegroundWindow($h)

# Desfaz anexacao de entrada de thread
[FgFix]::AttachThreadInput($curThread, $tgtThread, $false) | Out-Null
[FgFix]::AttachThreadInput($curThread, $fgThread, $false) | Out-Null

Start-Sleep -Milliseconds 400
$fg2 = [FgFix]::GetForegroundWindow()
Write-Output ("SETFOREGROUND_RESULT={0}" -f $sf)
Write-Output ("FG_AFTER=0x{0:X8} MATCH={1}" -f $fg2.ToInt64(), ($fg2 -eq $h))

if ($fg2 -eq $h) { Write-Output "RESULT=OK" } else { Write-Output "RESULT=FAIL" }
exit 0
