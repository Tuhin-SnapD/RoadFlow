# PowerShell build script for Road Construction Scheduling System

Write-Host "Building Road Construction Scheduling System..." -ForegroundColor Green

# Create directories
if (!(Test-Path "obj")) { New-Item -ItemType Directory -Name "obj" }
if (!(Test-Path "bin")) { New-Item -ItemType Directory -Name "bin" }

# Compiler settings
$CXX = "g++"
$CXXFLAGS = "-std=c++17 -Wall -Wextra -O2"
$INCLUDES = "-Iinclude"

# Source files
$SOURCES = @(
    "src\main.cpp",
    "src\Graph.cpp", 
    "src\Queue.cpp",
    "src\RoadScheduler.cpp",
    "src\BankersAlgorithm.cpp"
)

# Compile source files
Write-Host "Compiling source files..." -ForegroundColor Yellow
$success = $true

foreach ($source in $SOURCES) {
    $objFile = "obj\" + [System.IO.Path]::GetFileNameWithoutExtension($source) + ".o"
    $command = "$CXX $CXXFLAGS $INCLUDES -c $source -o $objFile"
    
    Write-Host "Compiling $source..." -ForegroundColor Cyan
    Invoke-Expression $command
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Failed to compile $source" -ForegroundColor Red
        $success = $false
        break
    }
}

if ($success) {
    # Link executable
    Write-Host "Linking executable..." -ForegroundColor Yellow
    $objFiles = Get-ChildItem "obj\*.o" | ForEach-Object { $_.FullName }
    $objFilesString = $objFiles -join " "
    $linkCommand = "$CXX $objFilesString -o bin\RoadConstruction.exe"
    
    Invoke-Expression $linkCommand
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build successful!" -ForegroundColor Green
        Write-Host "Executable created: bin\RoadConstruction.exe" -ForegroundColor Green
    } else {
        Write-Host "Linking failed!" -ForegroundColor Red
    }
} else {
    Write-Host "Build failed due to compilation errors!" -ForegroundColor Red
}

Write-Host "Press any key to continue..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown") 