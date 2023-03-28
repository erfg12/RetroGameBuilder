#ifndef RETRO_COMMON
#define RETRO_COMMON

#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <map>
#include <vector>

#if defined(__PS2__)
#include "SDL/SDL.h"
#elif defined(__APPLE__) || (defined(__linux__) && !defined(ANDROID)) || defined (__WIIU__) || defined (__PSVITA__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
//#include <SDL_mixer.h>
#include "audio.hpp"
#endif
#if defined(__SWITCH__)
#include <unistd.h>
#include <switch.h>
#endif
#if defined(XBOX)
#include <hal/debug.h>
#include <hal/xbox.h>
#include <hal/video.h>
#include <windows.h>
#endif

#if __PSVITA__
#include <vitasdk.h>
#include <kubridge.h>
#include <vitashark.h>
#include <zlib.h>
#include <psp2/kernel/processmgr.h>
#endif

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

#if __DREAMCAST__
#include "dreamcast.hpp"
#endif

#endif