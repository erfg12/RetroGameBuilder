#ifndef RETRO_COMMON
#define RETRO_COMMON

#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <map>
#include <vector>

#if defined(__PS2__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_endian.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <iopheap.h>
#include <sbv_patches.h>
//#include <romfs_io.h>
#include <libcdvd.h>
#elif (defined(__linux__) && !defined(ANDROID)) || defined (__WIIU__) || defined (__PSVITA__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_events.h>
#elif defined(__APPLE__) && !defined(IOSBUILD)
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2/SDL_events.h>
#elif defined(__APPLE__) && defined(IOSBUILD)
#include "SDL.h"
#include "SDL_main.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#else
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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

#if defined (__WIIU__)
#include <unistd.h>
#include <whb/proc.h>
#include <wut.h>
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

#if __3DS__
#include "3ds.h"
#endif

#if defined(__SWITCH__) || defined(__WIIU__)
#define JOY_START 10
#define JOY_LEFT  12
#define JOY_UP    13
#define JOY_RIGHT 14
#define JOY_DOWN  15
#elif defined(__PSVITA__) || defined(PSP)
#define JOY_START 11
#define JOY_LEFT  7
#define JOY_UP	  8
#define JOY_RIGHT 9
#define JOY_DOWN  6
#elif defined(__3DS__) || defined(__PS2__)
#define JOY_START 0
#define JOY_LEFT  99 // these are processed through joystick Hat
#define JOY_UP	  99
#define JOY_RIGHT 99
#define JOY_DOWN  99
#endif

#if defined(__WIN9X__)
#define JOY_START 0
#define JOY_LEFT  0
#define JOY_UP	  0
#define JOY_RIGHT 0
#define JOY_DOWN  0
#elif defined(__WII__)
#define JOY_START 5
#define JOY_LEFT  99 // joystick Hat
#define JOY_UP	  99
#define JOY_RIGHT 99
#define JOY_DOWN  99
#elif (defined(__WIN32__) && !defined(__WIN9X__) && !defined(XBOX)) || defined(__APPLE__) || defined(__linux__) || defined(__EMSCRIPTEN__)
#define JOY_START SDL_CONTROLLER_BUTTON_START
#define JOY_LEFT  SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define JOY_UP	  SDL_CONTROLLER_BUTTON_DPAD_UP
#define JOY_RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT
#define JOY_DOWN  SDL_CONTROLLER_BUTTON_DPAD_DOWN
#elif defined(XBOX)
#define JOY_START 7
#define JOY_LEFT  SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define JOY_UP	  SDL_CONTROLLER_BUTTON_DPAD_UP
#define JOY_RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT
#define JOY_DOWN  SDL_CONTROLLER_BUTTON_DPAD_DOWN
#elif defined(__XBOXONE__)
#define JOY_START 7
#define JOY_LEFT  13
#define JOY_UP	  10
#define JOY_RIGHT 11
#define JOY_DOWN  12
#endif

#define TICK_INTERVAL    20

#endif
