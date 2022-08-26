#include "common.h"

int main( int argc, char* args[] )
{
    if (init() && loadMedia()) 
        updateSurfaces();
    
    keepWindowOpen();

    closeSDL();
    return 0;
}

