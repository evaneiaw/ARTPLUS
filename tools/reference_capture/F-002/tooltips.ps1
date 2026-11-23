$ErrorActionPreference = 'Continue'
$ui = 'H:\Desktop\ArtPlus\tools\reference_capture\F-002\ui2.ps1'
$dir = 'H:\Desktop\ArtPlus\tools\reference_capture\F-002\shots'
$y = 292
foreach ($x in 1664, 1687, 1710, 1795, 1829, 1863, 1886) {
  $rx = $x - 70
  $ry = $y - 20
  & powershell -NoProfile -File $ui -Action move -TitleMatch 'test_vector' -X $x -Y $y -Wait 1400
  & powershell -NoProfile -File $ui -Action region -X $rx -Y $ry -X2 420 -Y2 95 -Out "$dir\tt-$x.png"
}
