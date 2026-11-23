param(
  [string]$Action = 'win',
  [string]$Out = '',
  [int]$PidTarget = 0,
  [string]$TitleMatch = 'ArtPro+',
  [int]$X = 0, [int]$Y = 0,
  [int]$X2 = 0, [int]$Y2 = 0,
  [string]$Keys = '',
  [int]$Wait = 600
)

Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
Add-Type @"
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public class W32C {
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);
  [DllImport("user32.dll")] public static extern IntPtr SetActiveWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint d, IntPtr e);
  [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, IntPtr extra);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint msg, IntPtr w, IntPtr l);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern int GetWindowTextLength(IntPtr h);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, System.Text.StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  public static List<IntPtr> Windows() {
    var list = new List<IntPtr>();
    EnumWindows((h, l) => { list.Add(h); return true; }, IntPtr.Zero);
    return list;
  }
  public static void ForceForeground(IntPtr h) {
    uint pid; uint fgThread = GetWindowThreadProcessId(GetForegroundWindow(), out pid);
    uint myThread = GetCurrentThreadId();
    AttachThreadInput(myThread, fgThread, true);
    if (IsIconic(h)) ShowWindow(h, 9);
    BringWindowToTop(h);
    SetForegroundWindow(h);
    SetActiveWindow(h);
    AttachThreadInput(myThread, fgThread, false);
  }
}
"@
[W32C]::SetProcessDPIAware() | Out-Null

function Get-Cands {
  $out = @()
  foreach ($h in [W32C]::Windows()) {
    if (-not [W32C]::IsWindowVisible($h)) { continue }
    $pid2 = 0
    [W32C]::GetWindowThreadProcessId($h, [ref]$pid2) | Out-Null
    if ($PidTarget -gt 0 -and $pid2 -ne $PidTarget) { continue }
    if ($PidTarget -le 0) {
      $pr = Get-Process -Id $pid2 -ErrorAction SilentlyContinue
      if (-not $pr -or $pr.ProcessName -notlike '*ArtPro*') { continue }
    }
    $len = [W32C]::GetWindowTextLength($h)
    $sb = New-Object System.Text.StringBuilder ($len + 2)
    [W32C]::GetWindowText($h, $sb, $sb.Capacity) | Out-Null
    $t = $sb.ToString()
    if ($TitleMatch -and $t -notlike "*$TitleMatch*") { continue }
    $r = New-Object W32C+RECT
    [W32C]::GetWindowRect($h, [ref]$r) | Out-Null
    $w = $r.Right - $r.Left; $hh = $r.Bottom - $r.Top
    if ($w -lt 50 -or $hh -lt 30) { continue }
    $out += [pscustomobject]@{ Handle = $h; Pid = $pid2; Title = $t; X = $r.Left; Y = $r.Top; W = $w; H = $hh }
  }
  return $out
}

function Get-Top {
  $c = @(Get-Cands)
  if ($c.Count -eq 0) { return $null }
  return ($c | Sort-Object { $_.W * $_.H } -Descending | Select-Object -First 1)
}

switch ($Action) {
  'win' {
    Get-Cands | ForEach-Object { "HWND={0} PID={1} RECT={2},{3} {4}x{5} TITLE={6}" -f $_.Handle, $_.Pid, $_.X, $_.Y, $_.W, $_.H, $_.Title }
  }
  'shot' {
    $t = Get-Top
    if (-not $t) { Write-Output 'NO_WINDOW'; exit 2 }
    [W32C]::ForceForeground($t.Handle)
    Start-Sleep -Milliseconds 500
    $bmp = New-Object System.Drawing.Bitmap($t.W, $t.H)
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($t.X, $t.Y, 0, 0, (New-Object System.Drawing.Size($t.W, $t.H)))
    $dir = Split-Path -Parent $Out
    if ($dir -and -not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    $bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
    $g.Dispose(); $bmp.Dispose()
    "{`"action`":`"shot`",`"hwnd`":`"$($t.Handle)`",`"title`":`"$($t.Title)`",`"rect`":[$($t.X),$($t.Y),$($t.W),$($t.H)],`"out`":`"$Out`"}"
  }
  'click' {
    $t = Get-Top
    if (-not $t) { Write-Output 'NO_WINDOW'; exit 2 }
    [W32C]::ForceForeground($t.Handle)
    Start-Sleep -Milliseconds 300
    [W32C]::SetCursorPos($X, $Y) | Out-Null
    Start-Sleep -Milliseconds 150
    [W32C]::mouse_event(0x0002, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds 60
    [W32C]::mouse_event(0x0004, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds $Wait
    "{`"action`":`"click`",`"at`":[$X,$Y],`"title`":`"$($t.Title)`"}"
  }
  'move' {
    $t = Get-Top
    if (-not $t) { Write-Output 'NO_WINDOW'; exit 2 }
    [W32C]::ForceForeground($t.Handle)
    Start-Sleep -Milliseconds 200
    [W32C]::SetCursorPos($X, $Y) | Out-Null
    Start-Sleep -Milliseconds $Wait
    "{`"action`":`"move`",`"at`":[$X,$Y],`"title`":`"$($t.Title)`"}"
  }
  'region' {
    $bmp = New-Object System.Drawing.Bitmap($X2, $Y2)
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($X, $Y, 0, 0, (New-Object System.Drawing.Size($X2, $Y2)))
    $dir = Split-Path -Parent $Out
    if ($dir -and -not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    $bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
    $g.Dispose(); $bmp.Dispose()
    "{`"action`":`"region`",`"rect`":[$X,$Y,$X2,$Y2],`"out`":`"$Out`"}"
  }
  'dblclick' {
    $t = Get-Top
    if (-not $t) { Write-Output 'NO_WINDOW'; exit 2 }
    [W32C]::ForceForeground($t.Handle)
    Start-Sleep -Milliseconds 300
    [W32C]::SetCursorPos($X, $Y) | Out-Null
    Start-Sleep -Milliseconds 150
    1..2 | ForEach-Object {
      [W32C]::mouse_event(0x0002, 0, 0, 0, [IntPtr]::Zero)
      Start-Sleep -Milliseconds 40
      [W32C]::mouse_event(0x0004, 0, 0, 0, [IntPtr]::Zero)
      Start-Sleep -Milliseconds 60
    }
    Start-Sleep -Milliseconds $Wait
    "{`"action`":`"dblclick`",`"at`":[$X,$Y],`"title`":`"$($t.Title)`"}"
  }
  'rclick' {
    $t = Get-Top
    if (-not $t) { Write-Output 'NO_WINDOW'; exit 2 }
    [W32C]::ForceForeground($t.Handle)
    Start-Sleep -Milliseconds 300
    [W32C]::SetCursorPos($X, $Y) | Out-Null
    Start-Sleep -Milliseconds 150
    [W32C]::mouse_event(0x0008, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds 60
    [W32C]::mouse_event(0x0010, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds $Wait
    "{`"action`":`"rclick`",`"at`":[$X,$Y],`"title`":`"$($t.Title)`"}"
  }
  'keys' {
    $t = Get-Top
    if (-not $t) { Write-Output 'NO_WINDOW'; exit 2 }
    [W32C]::ForceForeground($t.Handle)
    Start-Sleep -Milliseconds 250
    Add-Type -AssemblyName System.Windows.Forms
    [System.Windows.Forms.SendKeys]::SendWait($Keys)
    Start-Sleep -Milliseconds $Wait
    "{`"action`":`"keys`",`"keys`":`"$Keys`"}"
  }
  'uia' {
    $t = Get-Top
    if (-not $t) { Write-Output 'NO_WINDOW'; exit 2 }
    $el = [System.Windows.Automation.AutomationElement]::FromHandle($t.Handle)
    $cond = [System.Windows.Automation.Condition]::TrueCondition
    $all = $el.FindAll([System.Windows.Automation.TreeScope]::Descendants, $cond)
    $n = 0
    foreach ($e in $all) {
      $n++
      if ($n -gt 600) { break }
      $r = $e.Current.BoundingRectangle
      $nm = $e.Current.Name -replace "`r|`n", ' '
      if ($nm.Length -gt 120) { $nm = $nm.Substring(0,120) }
      "{0}|{1}|{2}|{3},{4},{5},{6}" -f $e.Current.ControlType.ProgrammaticName, $e.Current.AutomationId, $nm, [int]$r.X, [int]$r.Y, [int]$r.Width, [int]$r.Height
    }
  }
  'uiaall' {
    $pid2 = $PidTarget
    $roots = @(Get-Cands)
    foreach ($rt in $roots) {
      "=== WINDOW $($rt.Title) [$($rt.Handle)] ==="
      $el = [System.Windows.Automation.AutomationElement]::FromHandle($rt.Handle)
      $cond = [System.Windows.Automation.Condition]::TrueCondition
      $all = $el.FindAll([System.Windows.Automation.TreeScope]::Descendants, $cond)
      $n = 0
      foreach ($e in $all) {
        $n++
        if ($n -gt 800) { break }
        $r = $e.Current.BoundingRectangle
        $nm = $e.Current.Name -replace "`r|`n", ' '
        if ($nm.Length -gt 140) { $nm = $nm.Substring(0,140) }
        "{0}|{1}|{2}|{3},{4},{5},{6}" -f $e.Current.ControlType.ProgrammaticName, $e.Current.AutomationId, $nm, [int]$r.X, [int]$r.Y, [int]$r.Width, [int]$r.Height
      }
    }
  }
}
