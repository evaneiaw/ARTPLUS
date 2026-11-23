$ErrorActionPreference = 'Continue'
$ui = 'H:\Desktop\ArtPlus\tools\reference_capture\F-002\ui2.ps1'
$dir = 'H:\Desktop\ArtPlus\tools\reference_capture\F-002\shots'
foreach ($x in 1808, 1842, 1876, 1899) {
  & powershell -NoProfile -File $ui -Action click -TitleMatch 'test_vector' -X $x -Y 303 -Wait 1000
  & powershell -NoProfile -File $ui -Action shot -TitleMatch 'test_vector' -Out "$dir\menu-$x.png"
  & powershell -NoProfile -File $ui -Action keys -TitleMatch 'test_vector' -Keys '{ESC}' -Wait 500
}
