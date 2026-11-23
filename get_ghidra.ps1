$releases = Invoke-RestMethod -Uri 'https://api.github.com/repos/NationalSecurityAgency/ghidra/releases' -Headers @{Accept='application/vnd.github.v3+json'}
foreach ($r in $releases) {
    if ($r.tag_name -like 'Ghidra_12.1*') {
        Write-Host "Tag: $($r.tag_name)"
        $r.assets | Select-Object name, browser_download_url, size | Format-Table
    }
}