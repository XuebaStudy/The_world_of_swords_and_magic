@echo off
setlocal

set Mode= test
set Order= 4.0 
set Message= Added many new files to support compile 

echo Adding files to Git...
git add .
if %ERRORLEVEL% neq 0 (
    echo Git add failed. Exiting...
    exit /b 1
)

echo Committing changes...
git commit -m "%Mode% %Order%: %Message%"
if %ERRORLEVEL% neq 0 (
    echo Git commit failed. Exiting...
    exit /b 1
)

echo Pushing changes to remote repository...
git push origin main
if %ERRORLEVEL% neq 0 (
    echo Git push failed. Exiting...
    exit /b 1
)

echo All operations completed successfully.
endlocal