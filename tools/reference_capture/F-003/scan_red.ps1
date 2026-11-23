param([string]$Path, [int]$Max = 60)
Add-Type -AssemblyName System.Drawing
$b = [System.Drawing.Bitmap]::FromFile($Path)
Write-Output ("size: " + $b.Width + "x" + $b.Height)
$count = 0
$minx = 99999; $maxx = -1; $miny = 99999; $maxy = -1
for ($y = 0; $y -lt $b.Height; $y++) {
  for ($x = 0; $x -lt $b.Width; $x++) {
    $c = $b.GetPixel($x, $y)
    if ($c.R -eq 255 -and $c.G -eq 79 -and $c.B -eq 79) {
      $count++
      if ($x -lt $minx) { $minx = $x }
      if ($x -gt $maxx) { $maxx = $x }
      if ($y -lt $miny) { $miny = $y }
      if ($y -gt $maxy) { $maxy = $y }
      if ($count -le $Max) { Write-Output ("hit " + $x + "," + $y) }
    }
  }
}
Write-Output ("count: " + $count)
Write-Output ("bbox: " + $minx + "," + $miny + " -> " + $maxx + "," + $maxy)
$b.Dispose()
