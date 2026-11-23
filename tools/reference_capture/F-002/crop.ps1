param([string]$Src,[string]$Dst,[int]$X,[int]$Y,[int]$W,[int]$H,[int]$Scale=4)
Add-Type -AssemblyName System.Drawing
$src = [System.Drawing.Image]::FromFile($Src)
$crop = New-Object System.Drawing.Bitmap -ArgumentList @([int]$W, [int]$H)
$g = [System.Drawing.Graphics]::FromImage($crop)
$dstRect = New-Object System.Drawing.Rectangle -ArgumentList @(0, 0, [int]$W, [int]$H)
$srcRect = New-Object System.Drawing.Rectangle -ArgumentList @([int]$X, [int]$Y, [int]$W, [int]$H)
$g.DrawImage($src, $dstRect, $srcRect, [System.Drawing.GraphicsUnit]::Pixel)
$g.Dispose()
$big = New-Object System.Drawing.Bitmap -ArgumentList @([int]($W*$Scale), [int]($H*$Scale))
$g2 = [System.Drawing.Graphics]::FromImage($big)
$g2.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
$g2.DrawImage($crop, 0, 0, [int]($W*$Scale), [int]($H*$Scale))
$g2.Dispose()
$big.Save($Dst, [System.Drawing.Imaging.ImageFormat]::Png)
$src.Dispose(); $crop.Dispose(); $big.Dispose()
"ok $Dst"
