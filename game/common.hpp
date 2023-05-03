#ifndef RETRO_COMMON
#define RETRO_COMMON

#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <map>
#include <vector>

#if defined(__PS2__)
#include "SDL/SDL.h"
#include "SDL/SDL_endian.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <tamtypes.h>
#include <sifrpc.h>
#include <kernel.h>
#include <loadfile.h>
#include <errno.h>
#include <iopheap.h>
#include <debug.h>
#include <iopcontrol.h>
#include <sbv_patches.h>
#include <libmc.h>
#include <libcdvd.h>
#include <debug.h>
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

#endif
