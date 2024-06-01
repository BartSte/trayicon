<#
.SYNOPSIS
Build and install Qt.

.DESCRIPTION 
Build Qt with static or shared linking.

.PARAMETER Source
The source directory of Qt.

.PARAMETER Install
The installation directory of Qt.

.PARAMETER Static
Install static Qt libraries (default).

.PARAMETER Shared
Install shared Qt libraries.

.PARAMETER Version
The version of Qt to install.
#>
param (
    [string]$Source=$(Join-Path $PSScriptRoot ".." "Qt"),
    [string]$Install=$(Join-Path $PSScriptRoot ".." "3rdparty" "Qt"),
    [switch]$Static,
    [switch]$Shared,
    [string]$Version="6.7.1"
)

function Build-Qt-Static() {
    Write-Host "Downloading Qt source code"

    # is the source directory is not empty, do not download the source code again
    if (!(Test-Path "$Source")) {
        New-Item -ItemType Directory -Path "$Source" 
        & "$PSScriptRoot\download-qt.ps1" -Root "$Source" -Package "qt.qt6.$version_no_period.src"
    } else {
        Write-Host "The source directory is not empty, skipping download"
    }
        
    Write-Host "Building Qt with static linking"
    $src = Join-Path $Source $Version "Src"

    Write-Host "Deleting old build directory at $src\build if it exists"
    Remove-Item -Recurse -Force "$src\build" -ErrorAction SilentlyContinue

    & "C:\Program Files (x86)\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64
    & "$src\configure.bat" -static -release -prefix $Install -submodules qtbase -- -S "$src" -B "$src\build" -Wdev
    cmake --build "$src\build" --config Release
    cmake --install "$src\build"
}

function Build-Qt-Shared() {
    Write-Host "Downloading Qt shared libraries"
    Remove-Item -Recurse -Force "$Source"
    Remove-Item -Recurse -Force "$Install"
    New-Item -ItemType Directory -Path "$Install" | Out-Null
    New-Item -ItemType Directory -Path "$Source" | Out-Null

    & "$this_dir\download-qt.ps1" -Root "$Source" -Package "qt.qt6.$version_no_period.msvc2019_64"
    Copy-Item -Recurse -Force "$Source\qt-qt6-$version_no_period.msvc2019_64" "$Install"
}
    
$version_no_period = $Version.Replace(".", "")

if ($Static -or (!$Static -and !$Shared)) {
    Build-Qt-Static
} elseif ($Shared) {
    Build-Qt-Shared
}
