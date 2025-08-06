@echo off
echo Building Road Construction Scheduling System...

REM Create directories
if not exist "obj" mkdir obj
if not exist "bin" mkdir bin

REM Compiler settings
set CXX=g++
set CXXFLAGS=-std=c++17 -Wall -Wextra -O2
set INCLUDES=-Iinclude

REM Source files
set SOURCES=src\main.cpp src\Graph.cpp src\Queue.cpp src\RoadScheduler.cpp src\BankersAlgorithm.cpp

REM Compile source files
echo Compiling source files...
%CXX% %CXXFLAGS% %INCLUDES% -c src\main.cpp -o obj\main.o
%CXX% %CXXFLAGS% %INCLUDES% -c src\Graph.cpp -o obj\Graph.o
%CXX% %CXXFLAGS% %INCLUDES% -c src\Queue.cpp -o obj\Queue.o
%CXX% %CXXFLAGS% %INCLUDES% -c src\RoadScheduler.cpp -o obj\RoadScheduler.o
%CXX% %CXXFLAGS% %INCLUDES% -c src\BankersAlgorithm.cpp -o obj\BankersAlgorithm.o

REM Link executable
echo Linking executable...
%CXX% obj\main.o obj\Graph.o obj\Queue.o obj\RoadScheduler.o obj\BankersAlgorithm.o -o bin\RoadConstruction.exe

if %ERRORLEVEL% EQU 0 (
    echo Build successful!
    echo Executable created: bin\RoadConstruction.exe
) else (
    echo Build failed!
)

pause 