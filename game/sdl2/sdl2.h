#ifndef RETRO_SDL2
#define RETRO_SDL2

#if defined(__APPLE__) || defined(__linux__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#if __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdio.h>
#include <stdbool.h>

bool init();
bool loadMedia();
void closeSDL();
void keepWindowOpen();
void updateSurfaces();

#endif