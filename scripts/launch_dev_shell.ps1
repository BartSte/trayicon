<#
.SYNOPSIS
Launches the Visual Studio Developer Command Prompt.

.DESCRIPTION
Launches the Visual Studio Developer Command Prompt. If the environment
variable VSINSTALLDIR is not set, the script will not do anything.

.PARAMETER Arch
The architecture of the build: x86 or amd64. Default is amd64.

#>
param(
    [string]$Arch="amd64"
)
if ($env:VSINSTALLDIR) {
    Write-Host "Running Launch-VsDevShell.ps1"
    & "$Env:VSINSTALLDIR\Common7\Tools\Launch-VsDevShell.ps1" -Arch $Arch
} else {
    Write-Host "Not running Launch-VsDevShell because VSINSTALLDIR is not set."
}
