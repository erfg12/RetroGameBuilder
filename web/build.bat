mkdir build
emcc ../game/sdl2/sdl2.cpp ../game/main.cpp -o build/game.js -s USE_SDL=2