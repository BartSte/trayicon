param(
    [bool]$Help = $false,
    [bool]$Clean = $false,
    [string]$BuildType = "Release",
    [string]$QtDir = "C:\Qt\6.7.1\mingw_64",
    [string[]]$CMakeArgs = @()
)

function ShowHelp() {
    $msg = @"
Usage: configure.ps1 [-Help] [-Clean] [-BuildType <Release|Debug>]

Configures a build of the project. It is assumed that the depedencies are
installed and are discoverable by cmake. The following is the default behavior:
- The generator is Ninja
- The build type is Release
- The build is stored in a folder named build in the root of the project
- The testst are not build (can be enabled with \`-- -DBUILD_TESTING=ON\`)

Additionally, the following is supported by default:
- A custom build of Qt 6.7 may be located at 3rdparty/Qt

Options:
    --help                  Show this help message
    --clean                 Remove the build folder before configuring
    --build-type <type>     Set the build type to Debug, Release, or
                            RelWithDebInfo (default: Release)
"@
    Write-Output $msg
}

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

if ($Help) {
    ShowHelp
    exit
}

if ($Clean) {
    Clean
}

Configure
