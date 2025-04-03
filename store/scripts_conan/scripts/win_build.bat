@echo off
cls

:: set path in case script runs outside contained dir
cd %~dp0\..

set BUILD_DIR=%~dp0..\build_win
set CONAN_CMAKE="%BUILD_DIR%\conan\cmake"
set BUILD_TYPE=Debug
::set BUILD_TYPE=Release



:: for debug cmake file
::rd /s /q %BUILD_DIR%

mkdir %BUILD_DIR%
conan install . --output-folder=%CONAN_CMAKE% --build=missing --settings=build_type=%BUILD_TYPE% -s compiler.cppstd=17

echo "BUILD_DIR = %BUILD_DIR%" 
echo "CONAN_CMAKE = %CONAN_CMAKE%" 
echo "BUILD_TYPE = %BUILD_TYPE%" 


cmake -G "Visual Studio 17" -B %BUILD_DIR% -DCMAKE_TOOLCHAIN_FILE=%CONAN_CMAKE%\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
cmake --build %BUILD_DIR%

pause

