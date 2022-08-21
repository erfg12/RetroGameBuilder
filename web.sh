mkdir build
emcc -c game/main.c -o game/main.o -s USE_SDL=2
emcc game/main.o -o build/main.html -s USE_SDL=2