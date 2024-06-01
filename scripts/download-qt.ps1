<#
.SYNOPSIS
Download the Qt packages using the Qt installer.

.DESCRIPTION 
For this script to work, you need to set the QT_INSTALLER_JWT_TOKEN environment
variable to your jwt token. Check the website of Qt for more information

.PARAMETER Root
The root directory where the Qt packages will be downloaded/installed.

.PARAMETER Package
The names of the Qt packages to download.
#>
param (
    [string]$Root,
    [string]$Package
)

$this_dir = Split-Path -Parent $MyInvocation.MyCommand.Path
& "$this_dir\download-installer.ps1"
Write-Host "Running Qt installer..."
& "$this_dir\qt-installer.exe" --root "$Root" --accept-licenses --accept-obligations --default-answer --confirm-command install $Package
