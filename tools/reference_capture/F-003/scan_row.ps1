param([string]$Path, [int]$Y = 600, [int]$X0 = 1100, [int]$X1 = 1180)
Add-Type -AssemblyName System.Drawing
$b = [System.Drawing.Bitmap]::FromFile($Path)
for ($x = $X0; $x -le $X1; $x++) {
  $c = $b.GetPixel($x, $Y)
  if (-not ($c.R -eq 255 -and $c.G -eq 255 -and $c.B -eq 255)) {
    Write-Output ($x.ToString() + " -> " + $c.R + "," + $c.G + "," + $c.B)
  }
}
$b.Dispose()
