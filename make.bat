
@echo off
SET ORICUTRON="..\..\..\oricutron\"

SET ORIGIN_PATH=%CD%
rem SET PATH=%PATH%;%cc65%


del build\*.* /q
rem %OSDK%\bin\xa.exe -v -R -cc src\mymDbug.s -o src\mymplayer.o -DTARGET_FILEFORMAT_O65 -DTARGET_ORIX

%OSDK%\bin\xa.exe -R -cc src\rs232.asm -o build\rs232.o
co65  build\rs232.o -o build\rs232.s
cl65 -ttelestrat src\orixdbg.c build\rs232.s -o build\usr\bin\orixdbg


IF "%1"=="NORUN" GOTO End
copy build\usr\bin\orixdbg %ORICUTRON%\usbdrive\bin\a

cd %ORICUTRON%
OricutronV11 -mt 

cd %ORIGIN_PATH%
:End