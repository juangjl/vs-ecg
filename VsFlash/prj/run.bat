set APP_ROOT=%CD%\lib
ECHO %Path%|findstr /i /c:"%APP_ROOT:"=%">nul || set Path=%Path%;%APP_ROOT%;
BIN\VsFlash.exe
