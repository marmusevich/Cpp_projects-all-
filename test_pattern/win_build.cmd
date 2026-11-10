@echo off
setlocal enabledelayedexpansion


set BuildDir=_ms_build

mkdir %BuildDir%
rem cmake -G "Visual Studio 17" -B %BuildDir%
cmake -B %BuildDir%
cmake --build %BuildDir%

pause