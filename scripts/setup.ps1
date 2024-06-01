<#
.SYNOPSIS
Install the dependencies for the project.

.DESCRIPTION 
Qt will be built and installed in the 3rdparty directory. By default, static
libraries are built and installed. If you want to build and install shared
libraries, use the --shared option. This is much faster, as Qt does not need to
be built from, it is only downloaded. Please note that in the release, static
libraries are used, so you should test your changes with static linking in the
end anyway.

.PARAMETER Static
Install static Qt libraries (default).

.PARAMETER Shared
Install shared Qt libraries.

#>
param (
    [switch]$Static,
    [switch]$Shared
)

$this_dir = Split-Path -Parent $MyInvocation.MyCommand.Path
$root_dir = Split-Path -Parent $this_dir

# Check if the token is set
if ($env:QT_INSTALLER_JWT_TOKEN -eq $null) {
    Write-Host "No login to a Qt account found. You have 2 options:" -ForegroundColor Yellow
    Write-Host "- Login to a Qt account by running the login-qt script" -ForegroundColor Yellow
    Write-Host "- Set the environment variable QT_INSTALLER_JWT_TOKEN" -ForegroundColor Yellow
    exit 1
}

Write-Host "Installing Qt"
if ($Static -or (!$Static -and !$Shared)) {
    Write-Host "Installing Qt with static libraries"
    & "$this_dir\build-qt.ps1" -Static -Source "$root_dir/Qt" -Install "$root_dir/3rdparty/Qt"

    
} elseif ($Shared) {
    Write-Host "Installing shared Qt libraries"
    & "$this_dir\build-qt.ps1" -Shared -Source "$root_dir/Qt" -Install "$root_dir/3rdparty/Qt"
}
