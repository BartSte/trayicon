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

.PARAMETER CMakeArgs
All arguments after `--` are passed to cmake.

#>
param(
    [string]$QtDir = "C:\Qt\6.7.1\msvc2019_64",
    [switch]$Clean,
    [string]$Source = $(Join-Path $PSScriptRoot ".."),
    [string]$Build = $(Join-Path  $PSScriptRoot ".." "build"),
    [string[]]$CMakeArgs = @()
)

function Clean() {
    if (Test-Path $Build) {
        Write-Output "Removing build directory"
        Remove-Item $Build -Recurse -Force
    }
}

function Configure() {
    Write-Output "Configuring build..."
    Write-Output "Source $Source"
    Write-Output "Build $Build"
    Write-Output "QtDir: $QtDir"
    cmake -S "$Source" -B "$Build" -DCMAKE_PREFIX_PATH="$QtDir\lib\cmake;$Root\3rdparty\Qt\lib\cmake" $CMakeArgs 
}

if ($Clean) {
    Clean
}

$Root = Join-Path $PSScriptRoot ".."
Configure
