#include "common.h"

int main( int argc, char* args[] )
{
    std::vector<const char*> my_map = {
        { "res/hello_world.bmp" }
    };
    if (init() && loadMedia(my_map))
        updateSurfaces();
    
    keepWindowOpen();

    closeSDL();
    return 0;
}

