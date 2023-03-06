mkdir build
cp -R ../game/res ./
emcc ../game/shared.cpp ../game/main.cpp -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s ALLOW_MEMORY_GROWTH=1 --preload-file res -o build/game.html