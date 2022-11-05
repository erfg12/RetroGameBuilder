#include "common.h"

int main( int argc, char* args[] )
{
    std::vector<const char*> imageMap = {
        { "res/bullet.bmp", "res/enemy.bmp", "res/player.bmp" }
    };
    if (init() && loadImageMedia(imageMap)) {
        updateSurfaces();
    }
    
    keepWindowOpen();

    closeSDL();
    return 0;
}

