mkdir build
xcopy ..\game\res .\res /E /I /Y
emcc ../game/shared.cpp ../game/main.cpp -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s ALLOW_MEMORY_GROWTH=1 --preload-file res -sLEGACY_GL_EMULATION -o build/game.html