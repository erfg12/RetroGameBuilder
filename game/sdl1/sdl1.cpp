#include "../common.h"
#include "sdl1.h"

//SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
std::vector< SDL_Surface* > LoadedImages;

bool init()
{
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //SDL_WM_SetCaption("SDL Title", NULL);
        gScreenSurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    }
    return success;
}

bool loadMedia(std::vector<const char*> images)
{
    bool success = true;
    for (const char* x : images) {
        SDL_Surface* SDLImg = SDL_LoadBMP(x);
        LoadedImages.push_back(SDLImg);
        if (SDLImg == NULL)
        {
            printf("Unable to load image %s! SDL Error: %s\n", x, SDL_GetError());
            success = false;
        }
    }
    return success;
}

void closeSDL()
{
    for (SDL_Surface* x : LoadedImages) {
        SDL_FreeSurface( x );
    }
    //gWindow = NULL;
    SDL_Quit();
}

void updateSurfaces() {
    for (SDL_Surface* x : LoadedImages) {
        SDL_BlitSurface( x, NULL, gScreenSurface, NULL );
    }
    //SDL_UpdateWindowSurface( gWindow );
}

void keepWindowOpen() {
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }
}