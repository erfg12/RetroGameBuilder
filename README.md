This project is aimed at compiling a game across multiple game consoles and computers. The game's code is stored in the `/game` directory.

### How To Build:

#### MacOS (+ iOS,iPadOS,tvOS)
Download SDL2 dmg, open the DMG, place the framework file in `/library/frameworks` directory. Open `macos/game.xcodeproj` with XCode, press build.

#### Windows
Download SDL2 vc zip, unzip inner contents to the `windows\sdl2-vc` directory. Open `windows\game.sln` file with Visual Studio, press build.

#### Linux (Ubuntu)
In Terminal, type `sudo apt install build-essential libsdl2-dev`, then CD to the `/linux` directory. Now type `make`.

#### Web
Clone `https://github.com/emscripten-core/emsdk.git`. Navigate to emsdk dir. On Linux/MacOS: `./emsdk install latest`, `./emsdk activate latest`, `source ./emsdk_env.sh`. Don't close Terminal. Navigate back to project `/web` dir, type `chmod a+x build.sh` and run `build.sh`. On Windows: `emsdk install latest`, `emsdk activate latest`, `emsdk_env.bat`. Don't close command window. Navigate back to project dir and run `web\build.bat`

#### PSVita
NOTE: I recommend doing this on a Linux distro like Ubuntu. First install [VitaSDK](https://vitasdk.org/). Then CD to the `/psvita` directory, then `chmod a+x ./psvita.sh`, and run `./build.sh`. In `/build` you will have your .vpk file.

#### Switch
Install DevKitPro. Open `DevKitPro > MSys2`. Type `pacman -S switch-portlibs` and install ALL. CD to the `/switch` directory, type `make`.

#### 3DS
Install DevKitPro. Open `DevKitPro > MSys2`. Type `pacman -S 3ds-portlibs` and install ALL. CD to the `/3ds` directory, type `make`.

