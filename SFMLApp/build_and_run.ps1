# Check if the "build" directory exists
if (Test-Path -Path "build") {
    Write-Host "Directory 'build' exists. Removing it..."
    Remove-Item -Path "build" -Recurse -Force
    Write-Host "'build' directory removed."
} else {
    Write-Host "'build' directory does not exist. No action needed."
}

# Get the current working directory (equivalent to pwd in Bash)
$currentDir = Get-Location
Write-Host "Current working directory: $currentDir"

# Change to the project directory from the current working directory
Write-Host "Changing to the 'SFMLApp' directory..."
cd "$currentDir"
Write-Host "Now in the directory: $(Get-Location)"

# Create the "build" directory again
Write-Host "Creating the 'build' directory..."
mkdir build
Write-Host "'build' directory created."

# Change to the "build" directory
Write-Host "Changing to the 'build' directory..."
cd build
Write-Host "Now in the directory: $(Get-Location)"

# Generate build files using CMake with MinGW Makefiles
Write-Host "Generating build files with CMake..."
cmake -G "MinGW Makefiles" ..
Write-Host "Build files generated."

# Build the project
Write-Host "Building the project..."
cmake --build .
Write-Host "Project built."

# Run the application
Write-Host "Running the application..."
.\SFMLApp.exe
Write-Host "Application executed."
