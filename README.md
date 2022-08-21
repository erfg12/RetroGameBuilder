This project is aimed at compiling a game across multiple game consoles and computers.

### MacOS (+ iOS,iPadOS,tvOS)
Download SDL2, open the DMG, place the framework file in `/library/frameworks` directory. Open `game.xcodeproj` with XCode, press build.

### Windows
Download SDL2 vc zip, unzip inner contents to the `vs\sdl2-vc` directory. Open `game.sln` file with Visual Studio, press build.

### Linux (Ubuntu)
In Terminal type `sudo apt install build-essential libsdl2-dev`. Now type `make`.