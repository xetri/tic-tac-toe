@echo off

if not exist .\bin mkdir .\bin
call gcc .\src\main.c -o .\bin\main.exe -Wall -Llib -lmingw32 -lSDL2main -lSDL2
