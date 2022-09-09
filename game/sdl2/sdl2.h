#ifndef RETRO_SDL2
#define RETRO_SDL2

#if defined(__APPLE__) || (defined(__linux__) && !defined(ANDROID)) || defined (__WIIU__)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

#endif