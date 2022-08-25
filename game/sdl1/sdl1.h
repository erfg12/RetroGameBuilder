#ifndef RETRO_SDL1
#define RETRO_SDL1

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

bool init();
bool loadMedia();
void closeSDL();
void keepWindowOpen();
void updateSurfaces();

#endif