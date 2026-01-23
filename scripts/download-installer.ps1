<#
.SYNOPSIS
Download the Qt online installer.

.DESCRIPTION 
Download the Qt online installer and run it to download the Qt packages.
#>

$this_dir = Split-Path -Parent $MyInvocation.MyCommand.Path

if (Test-Path "$this_dir/qt-installer.run") {
    Write-Host "Qt installer already downloaded."
    exit 0
}

Write-Host "Downloading Qt installer..."
$url = "https://download.qt.io/official_releases/online_installers/qt-online-installer-windows-x64-online.exe"
Invoke-WebRequest -Uri $url -OutFile "$this_dir/qt-installer.exe"
Write-Host "Qt installer downloaded."
