This project is aimed at compiling a game across multiple game consoles and computers. The game's code is stored in the `/game` directory.

### How To Build:

#### MacOS (+ iOS,iPadOS,tvOS)
Download SDL2, open the DMG, place the framework file in `/library/frameworks` directory. Open `game.xcodeproj` with XCode, press build.

#### Windows
Download SDL2 vc zip, unzip inner contents to the `vs\sdl2-vc` directory. Open `game.sln` file with Visual Studio, press build.

#### Linux (Ubuntu)
In Terminal type `sudo apt install build-essential libsdl2-dev`. Now type `make`.

#### Web
Clone `https://github.com/emscripten-core/emsdk.git`. Navigate to emsdk dir. On Linux/MacOS: `./emsdk install latest`, `./emsdk activate latest`, `source ./emsdk_env.sh`. Don't close Terminal. Navigate back to project dir and run `web.sh`. On Windows: `emsdk install latest`, `emsdk activate latest`, `emsdk_env.bat`. Don't close command window. Navigate back to project dir and run `web.bat`

#### PSVita
NOTE: I recommend doing this on a Linux distro like Ubuntu. First install [VitaSDK](https://vitasdk.org/). Then `chmod a+x psvita.sh`, and run `./psvita.sh`. In `/psvita/build` you will have your .vpk file.

#### Switch
Install DevKitPro. Open `DevKitPro > MSys2`. CD to the switch directory, type `make`.

