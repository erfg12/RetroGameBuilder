#if defined (__3DS__)
    #include "sdl1/sdl1.h" // this game's SDL1 methods
#else
    #include "sdl2/sdl2.h" // this game's SDL2 methods
#endif

int main( int argc, char* args[] )
{
    if (init() && loadMedia()) 
        updateSurfaces();
    
    keepWindowOpen();

    closeSDL();
    return 0;
}

