@echo off

if not exist .\out mkdir .\out
call gcc .\src\main.c -o .\out\main.exe -Wall -Llib\x64 -lmingw32 -lSDL2main -lSDL2
REM call .\out\main.exe
