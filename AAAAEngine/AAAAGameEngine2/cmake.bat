@echo off
setlocal

cd /d .\AAAAGameEngine2
rd /s /q .\build
mkdir build
cd .\build
cmake ..

endlocal
pause >nul

pause >nul