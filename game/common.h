#ifndef RETRO_COMMON
#define RETRO_COMMON

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const char WINDOW_TITLE[] = "SDL Title";

bool init();
bool loadMedia();
void closeSDL();
void keepWindowOpen();
void updateSurfaces();

#if defined (__3DS__) || defined (__WII__) || defined (__PS2__)
    #include "sdl1/sdl1.h" // this game's SDL1 methods
#else
    #include "sdl2/sdl2.h" // this game's SDL2 methods
#endif
#if defined (__DREAMCAST__)
    #include "sdl1/dreamcast.h"
#endif

#include <stdio.h>
#include <stdbool.h>

#endif