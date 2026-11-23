$f = "H:\Desktop\ArtPlus\CMakeLists.txt"
$t = [IO.File]::ReadAllText($f)
$old = "add_executable(bearer_bar_test`r`n    tests/unit/test_bearer_bar.cpp`r`n)"
$new = "add_executable(bearer_bar_test`r`n    tests/unit/test_bearer_bar.cpp`r`n    `$" + "DOCUMENT_SOURCES" + "`r`n    `$" + "PREPRESS_SOURCES" + "`r`n)"
if ($t.Contains($new)) { Write-Host "ALREADY"; exit 0 }
if (-not $t.Contains($old)) { Write-Host "ANCHOR NOT FOUND"; exit 1 }
$t2 = $t.Replace($old, $new)
[IO.File]::WriteAllText($f, $t2)
Write-Host "DONE"