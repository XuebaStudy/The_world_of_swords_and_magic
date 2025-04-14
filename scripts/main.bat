@echo off
setlocal

set BUILD_DIR=build

if exist %BUILD_DIR% (
    echo Cleaning existing build directory...
    rmdir /s /q %BUILD_DIR%
)

mkdir %BUILD_DIR%

cd /d %BUILD_DIR%

cmake -G "MinGW Makefiles" .. > NUL
..\mingw64\bin\make > NUL

if exist ..\Project\bin\main.exe (
    echo Deleting old main.exe file...
    del ..\Project\bin\main.exe
)

copy main.exe ..\Project\bin\main.exe > NUL

cd ..\Project\bin
main.exe

