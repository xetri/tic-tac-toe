# Tic Tac Toe

## Description
Tic Tac Toe made in c using SDL2

### Note:
- Surely to run in windows with gcc/clang/tcc compiler with flags mentioned in the [Makefile](.//Makefile) but dont know about other OS
- Setup seperately for other os

### Resources:
- [SDL2](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.2)

### Run

#### Windows

```cmd
mkdir -p out
gcc .\src\main.c -o .\out\main.exe -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
.\out\main.exe
```

