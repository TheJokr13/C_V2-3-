@echo off
gcc\bin\gcc.exe main.c -o main -I ./SDL2/include -L ./SDL2/lib -lSDL2 SDL2_ttf.lib -lSDL2_mixer -lSDL2_IMAGE
main.exe