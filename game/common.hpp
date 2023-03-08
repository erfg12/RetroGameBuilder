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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
//#include "../xbox/nxdk/lib/sdl/SDL2_mixer/include/SDL_mixer.h" // xbox
#endif

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

#if __DREAMCAST__
#include "dreamcast.hpp"
#endif

#endif