<#
.SYNOPSIS
Configures a build of the project.

.DESCRIPTION
Configures a build of the project. It is assumed that the depedencies are
installed and are discoverable by cmake. The following is the default behavior:
- The generator is Ninja
- The build type is Release
- The build is stored in a folder named build in the root of the project
- The testst are not build (can be enabled with `-DBUILD_TESTING=ON`)
- The MinGW compiler is used.
- Qt 6.7.1 is used.

.PARAMETER BuildType
The build type to use. Can be Release, Debug, or RelWithDebInfo. Default is Release.

.PARAMETER QtDir
The directory where Qt is installed. Default is C:\Qt\6.7.1\mingw_64.

.PARAMETER Clean
If present, the build folder is removed before configuring.

.PARAMETER CMakeArgs
All arguments after `--` are passed to cmake.
#>
param(
    [string]$BuildType = "Release",
    [string]$QtDir = "C:\Qt\6.7.1\mingw_64",
    [switch]$Clean,
    [string[]]$CMakeArgs = @()
)

function Clean() {
    if (Test-Path $Root\build) {
        Remove-Item $Root\build -Recurse -Force
    }
}

function Configure() {
    Write-Output "Configuring build..."
    Write-Output "Root: $Root"
    Write-Output "QtDir: $QtDir"
    cmake -G "Ninja" -S "$Root" -B "$Root\build" -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE="$BuildType" -DCMAKE_PREFIX_PATH="$QtDir\lib\cmake" $CMakeArgs 
}

$Root = Join-Path $PSScriptRoot ".."

if ($Clean) {
    Clean
}

Configure

