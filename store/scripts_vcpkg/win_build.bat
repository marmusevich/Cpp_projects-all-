@echo off
cls
:: uncoment and use to set path to the vcpkg or set manually
::setx VCPKG_ROOT "path to vcpkg" >nul
::setx PATH "%PATH%;%VCPKG_ROOT%" >nul

echo VCPKG_ROOT is '%VCPKG_ROOT%'

:: set path in case script runs outside contained dir
cd %~dp0\..

vcpkg install

set BUILD_DIR=%~dp0..\Build

:: for debug cmake file
::rd /s /q %BUILD_DIR%

mkdir %BUILD_DIR%
cmake -G "Visual Studio 17" -B %BUILD_DIR% 
cmake --build %BUILD_DIR%

pause
