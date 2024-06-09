# Define the path to the executable
$appPath = "C:\path\to\app.exe"

# Create a new job object
$jobObject = New-Object System.Diagnostics.Process

# Start the process and assign it to the job object
$process = Start-Process -FilePath $appPath -PassThru

# Attach the process to the job object

$jobObject.StartInfo.FileName = $process.StartInfo.FileName
$jobObject.StartInfo.Arguments = $process.StartInfo.Arguments
$jobObject.StartInfo.UseShellExecute = $false
$jobObject.StartInfo.RedirectStandardOutput = $true

$jobObject.StartInfo.RedirectStandardError = $true


# Assign the process to the job object
$jobObject.Start()
$jobObject.WaitForExit()

# When the PowerShell script is terminated, the job object will clean up the process
