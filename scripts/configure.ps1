<#
.SYNOPSIS
Configures a build of the project.

.DESCRIPTION
Configures a build of the project. It is assumed that the depedencies are
installed and are discoverable by cmake. The following is the default behavior:
- The generator is Ninja
- The build type is Release
- The build is stored in a folder named build in the root of the project by default.
- The testst are not build (can be enabled with `-DBUILD_TESTING=ON`)
- The MinGW compiler is used.
- Qt 6.7.1 is used.

.PARAMETER QtDir
The directory where Qt is installed. Default is C:\Qt\6.7.1\mingw_64.

.PARAMETER Clean
If present, the build folder is removed before configuring.

.PARAMETER Source
The path to the source code. Default is root of project.

.PARAMETER Build
The directory to store the build files in. Default is "build" for in root of
the project.

.PARAMETER Arch
The architecture of the build: x86 or amd64. Default is amd64.

.PARAMETER CMakeArgs
All arguments after `--` are passed to cmake.

#>
param(
    [switch]$Clean,
    [string]$Source = $(Join-Path $PSScriptRoot ".."),
    [string]$Build = $(Join-Path  $PSScriptRoot ".." "build"),
    [string]$QtDir = $(Join-Path $PSScriptRoot ".." "3rdparty" "Qt"),
    [string]$Arch="amd64",
    [string[]]$CMakeArgs = @()
)

function Clean() {
    if (Test-Path $Build) {
        Write-Output "Removing build directory"
        Remove-Item $Build -Recurse -Force
    }
}

function  Launch-VsDevShell() {
    if ($env:VSINSTALLDIR) {
        Write-Host "Running Launch-VsDevShell.ps1"
        & "$env:VSINSTALLDIR\Common7\Tools\Launch-VsDevShell.ps1" -Arch $Arch
    } else {
        Write-Host "Not running Launch-VsDevShell because VSINSTALLDIR is not set."
    }
}

function Configure() {
    Write-Output "Configuring build..."
    Write-Output "Source $Source"
    Write-Output "Build $Build"
    Write-Output "QtDir: $QtDir"
    cmake -S "$Source" -B "$Build" -DCMAKE_PREFIX_PATH="$QtDir\lib\cmake" $CMakeArgs 
}

$Root = Join-Path $PSScriptRoot ".."

if ($Clean) {
    Clean
}

Launch-VsDevShell
Configure
