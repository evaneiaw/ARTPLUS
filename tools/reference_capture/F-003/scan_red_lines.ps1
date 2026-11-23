param([string]$Path, [int]$MaxRow = 5)
Add-Type -AssemblyName System.Drawing
$b = [System.Drawing.Bitmap]::FromFile($Path)
$rows = @{}
$cols = @{}
for ($y = 0; $y -lt $b.Height; $y++) {
  for ($x = 0; $x -lt $b.Width; $x++) {
    $c = $b.GetPixel($x, $y)
    if ($c.R -eq 255 -and $c.G -eq 79 -and $c.B -eq 79) {
      if ($x -lt 1650) {
        if ($rows.ContainsKey($y)) { $rows[$y]++ } else { $rows[$y] = 1 }
        if ($cols.ContainsKey($x)) { $cols[$x]++ } else { $cols[$x] = 1 }
      }
    }
  }
}
Write-Output "rows with >=20 red px (y:count):"
$rows.GetEnumerator() | Where-Object { $_.Value -ge 20 } | Sort-Object Name | ForEach-Object { Write-Output ("  " + $_.Name + ":" + $_.Value) }
Write-Output "cols with >=20 red px (x:count):"
$cols.GetEnumerator() | Where-Object { $_.Value -ge 20 } | Sort-Object Name | ForEach-Object { Write-Output ("  " + $_.Name + ":" + $_.Value) }
$b.Dispose()
