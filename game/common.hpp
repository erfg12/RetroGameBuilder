#ifndef RETRO_COMMON
#define RETRO_COMMON

#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <map>
#include <vector>

#if defined(__PS2__)
#include "SDL/SDL.h"
#elif defined(__APPLE__) || (defined(__linux__) && !defined(ANDROID)) || defined (__WIIU__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

#if __DREAMCAST__
#include "dreamcast.h"
#endif

#endif