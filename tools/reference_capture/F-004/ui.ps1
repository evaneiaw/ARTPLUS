param(
  [string]$Action = 'shot',
  [string]$Out = '',
  [string]$TitleMatch = 'ArtPro+',
  [int]$X = 0, [int]$Y = 0,
  [string]$Keys = '',
  [int]$Wait = 500
)

Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
Add-Type @"
using System;
using System.Runtime.InteropServices;
public class W32B {
  [DllImport("user32.dll", SetLastError=true)] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
  [DllImport("user32.dll")] public static extern void mouse_event(uint f, uint dx, uint dy, uint d, IntPtr e);
}
"@
[W32B]::SetProcessDPIAware() | Out-Null

function Get-Win {
  param([string]$m)
  return Get-Process | Where-Object { $_.MainWindowTitle -like "*$m*" -and $_.MainWindowHandle -ne 0 } | Select-Object -First 1
}

function Focus-Win($p) {
  if (-not $p) { return }
  if ([W32B]::IsIconic($p.MainWindowHandle)) { [W32B]::ShowWindow($p.MainWindowHandle, 9) | Out-Null }
  [W32B]::SetForegroundWindow($p.MainWindowHandle) | Out-Null
  Start-Sleep -Milliseconds 300
}

switch ($Action) {
  'shot' {
    $p = Get-Win $TitleMatch
    if (-not $p) { Write-Output "NO_WINDOW:$TitleMatch"; exit 2 }
    Focus-Win $p
    $r = New-Object W32B+RECT
    [W32B]::GetWindowRect($p.MainWindowHandle, [ref]$r) | Out-Null
    $bx=$r.Left; $by=$r.Top; $bw=$r.Right-$r.Left; $bh=$r.Bottom-$r.Top
    $bmp = New-Object System.Drawing.Bitmap($bw, $bh)
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.CopyFromScreen($bx, $by, 0, 0, (New-Object System.Drawing.Size($bw, $bh)))
    $dir = Split-Path -Parent $Out
    if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    $bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
    $g.Dispose(); $bmp.Dispose()
    "{`"action`":`"shot`",`"window`":`"$($p.MainWindowTitle)`",`"rect`":[$bx,$by,$bw,$bh],`"out`":`"$Out`"}"
  }
  'click' {
    $p = Get-Win $TitleMatch
    if (-not $p) { Write-Output "NO_WINDOW:$TitleMatch"; exit 2 }
    Focus-Win $p
    [W32B]::SetCursorPos($X, $Y) | Out-Null
    Start-Sleep -Milliseconds 120
    [W32B]::mouse_event(0x0002, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds 60
    [W32B]::mouse_event(0x0004, 0, 0, 0, [IntPtr]::Zero)
    Start-Sleep -Milliseconds $Wait
    "{`"action`":`"click`",`"at`":[$X,$Y],`"window`":`"$($p.MainWindowTitle)`"}"
  }
  'keys' {
    $p = Get-Win $TitleMatch
    if (-not $p) { Write-Output "NO_WINDOW:$TitleMatch"; exit 2 }
    Focus-Win $p
    Add-Type -AssemblyName System.Windows.Forms
    [System.Windows.Forms.SendKeys]::SendWait($Keys)
    Start-Sleep -Milliseconds $Wait
    "{`"action`":`"keys`",`"keys`":`"$Keys`"}"
  }
  'openfile' {
    $p = Get-Win 'Open File'
    if (-not $p) { $p = Get-Win 'Abrir' }
    if (-not $p) { Write-Output 'NO_WINDOW:Open File'; exit 2 }
    $el = [System.Windows.Automation.AutomationElement]::FromHandle($p.MainWindowHandle)
    $cond = [System.Windows.Automation.Condition]::TrueCondition
    $all = $el.FindAll([System.Windows.Automation.TreeScope]::Descendants, $cond)
    $doneVal = $false; $doneBtn = $false
    foreach ($e in $all) {
      $ct = $e.Current.ControlType.ProgrammaticName
      if (-not $doneVal -and ($ct -eq 'ControlType.Edit')) {
        try {
          $vp = $e.GetCurrentPattern([System.Windows.Automation.ValuePattern]::Pattern)
          $vp.SetValue($Keys)
          $doneVal = $true
          "SET_NAME|$($e.Current.Name)|$Keys"
        } catch { "ERR_SETVAL:$($_.Exception.Message)" }
      }
      if (-not $doneBtn -and ($ct -eq 'ControlType.Button') -and ($e.Current.Name -eq 'Abrir' -or $e.Current.Name -eq 'Open')) {
        try {
          $ip = $e.GetCurrentPattern([System.Windows.Automation.InvokePattern]::Pattern)
          $ip.Invoke()
          $doneBtn = $true
          "INVOKED|$($e.Current.Name)"
        } catch { "ERR_INVOKE:$($_.Exception.Message)" }
      }
    }
    "DONE val=$doneVal btn=$doneBtn"
  }
  'uia' {
    $p = Get-Win $TitleMatch
    if (-not $p) { Write-Output "NO_WINDOW:$TitleMatch"; exit 2 }
    $el = [System.Windows.Automation.AutomationElement]::FromHandle($p.MainWindowHandle)
    $walker = [System.Windows.Automation.TreeWalker]::ControlViewWalker
    $cond = [System.Windows.Automation.Condition]::TrueCondition
    $all = $el.FindAll([System.Windows.Automation.TreeScope]::Descendants, $cond)
    $n = 0
    foreach ($e in $all) {
      $n++
      if ($n -gt 400) { break }
      $r = $e.Current.BoundingRectangle
      $nm = $e.Current.Name -replace "`r|`n", ' '
      if ($nm.Length -gt 90) { $nm = $nm.Substring(0,90) }
      "{0}|{1}|{2}|{3},{4},{5},{6}" -f $e.Current.ControlType.ProgrammaticName, $e.Current.AutomationId, $nm, [int]$r.X, [int]$r.Y, [int]$r.Width, [int]$r.Height
    }
  }
}
