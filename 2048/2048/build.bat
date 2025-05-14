@echo off
echo Starting build process...
echo Current directory: %CD%

if not exist build (
    echo Creating build directory...
    mkdir build
) else (
    echo Build directory already exists
)

cd build
echo Changed to build directory: %CD%

echo Running CMake...
cmake -DSFML_DIR=../SFML/lib/cmake/SFML .. -G "Visual Studio 17 2022"
if errorlevel 1 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo Building project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
cd ..
pause 