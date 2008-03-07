@echo off
IF EXIST win32\StupidServ-Setup*.exe del win32\StupidServ-Setup*.exe
"C:\Program Files\Pantaray\QSetup\Composer.exe" win32\StupidServ.qsp /Compile /Exit
move win32\StupidServ-Setup.exe win32\StupidServ-Setup-3-0-1-%1.exe
