## About

This project's goal is compiling a game across multiple consoles and computers. The game's code is stored in the `/game` directory.

## How To Build:

### MacOS (+ iOS,iPadOS,tvOS)
- - -
Download [SDL2 dmg](https://github.com/libsdl-org/SDL/releases/latest), open the DMG, place the framework file in `/library/frameworks` directory. Open `macos/game.xcodeproj` with XCode, press build.

### Windows
- - -
Download [SDL2 vc zip](https://github.com/libsdl-org/SDL/releases/latest), unzip inner contents to the `windows\sdl2-vc` directory. Open `windows\game.sln` file with Visual Studio, press build.

### Linux (Ubuntu)
- - -
In Terminal, type `sudo apt install build-essential libsdl2-dev`, then CD to the `/linux` directory. Now type `make`.

### Web
- - -
Clone `https://github.com/emscripten-core/emsdk.git`. Navigate to emsdk dir. On Linux/MacOS: `./emsdk install latest`, `./emsdk activate latest`, `source ./emsdk_env.sh`. Don't close Terminal. Navigate back to project `/web` dir, type `chmod a+x build.sh` and run `build.sh`. On Windows: `emsdk install latest`, `emsdk activate latest`, `emsdk_env.bat`. Don't close command window. Navigate back to project dir and run `web\build.bat`

### PSVita
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). First install [VitaSDK](https://vitasdk.org/). Then CD to the `/psvita` directory, then `chmod a+x ./psvita.sh`, and run `./build.sh`. In `/build` you will have your .vpk file.

### Switch
- - -
Install DevKitPro. Open `DevKitPro > MSys2`. Type `pacman -S switch-portlibs` and install ALL. CD to the `/switch` directory, type `make`.

### 3DS
- - -
Install DevKitPro. Open `DevKitPro > MSys2`. Type `pacman -S 3ds-portlibs` and install ALL. CD to the `/3ds` directory, type `make`.

### DreamCast
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). Setup [KOS](https://gist.github.com/erfg12/a55328f50abaea15bd06d6584ed435af#file-kos-setup-easy-md) first, then [OpenGL](https://gist.github.com/erfg12/64285ce6e466fccbe8316f2e7594861a#file-kos-sdl-with-opengl-md). CD to `/dreamcast`, type `make`.
