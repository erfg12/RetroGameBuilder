#include "../common.h"
#include "sdl1.h"

//SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

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

bool loadMedia()
{
    bool success = true;
    gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}

void closeSDL()
{
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;
    //gWindow = NULL;
    SDL_Quit();
}

void updateSurfaces() {
    SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
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