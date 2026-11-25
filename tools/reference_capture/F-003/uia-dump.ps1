param([string]$TitleMatch = "", [int]$Depth = 6)
Add-Type -AssemblyName UIAutomationClient, UIAutomationTypes
$t = [System.Windows.Automation.TreeScope]
$c = [System.Windows.Automation.Condition]
function Walk($el, $d) {
  if ($d -gt $Depth) { return }
  try {
    $name = $el.CurrentName
    $cls = $el.CurrentClassName
    $aid = $el.CurrentAutomationId
    $ct = $el.CurrentControlType.ToString()
    Write-Output ("  " * $d + "[$ct] Name='$name' Class='$cls' Aid='$aid'")
  } catch {}
  try { $children = $el.FindAll($t::Children, $c::TrueCondition) } catch { return }
  foreach ($ch in $children) { Walk $ch ($d + 1) }
}
foreach ($w in [System.Windows.Automation.AutomationElement]::RootElement.FindAll($t::Children, $c::TrueCondition)) {
  try { $title = $w.CurrentName } catch { continue }
  if ($TitleMatch -and $title.IndexOf($TitleMatch, [System.StringComparison]::OrdinalIgnoreCase) -lt 0) { continue }
  Write-Output ("WINDOW Name='$title' Class='$($w.CurrentClassName)' PID=$($w.CurrentProcessId)")
  Walk $w 1
}
