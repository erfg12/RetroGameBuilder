## About

This project's goal is compiling a game across multiple consoles and computers. The game's code is stored in the `/game` directory.

Currently most systems don't compile. Check the TO-DO section below to see what systems currently build.

## TO-DO
- [x] 3DS
- [ ] Android
- [ ] DreamCast
- [x] Linux
- [ ] MacOS (+ iOS)
- [ ] Mac OS X
- [ ] PlayStation 2
- [x] PSVita
- [x] Switch
- [x] Windows 9x
- [x] Windows
- [x] Web
- [ ] Wii
- [ ] Wii U
- [ ] OG Xbox

## How To Build:

### 3DS
- - -
Install [DevKitPro](https://devkitpro.org/wiki/Getting_Started). Open `DevKitPro > MSys2`. Type `pacman -S 3ds-portlibs` and install ALL. In the project directory, CD to the `/3ds` directory, type `make`.

### Android
- - -
Using Windows, install Android Studio. Clone the [SDL2 source](https://github.com/libsdl-org/SDL)'s `include`, `src` and `Android.mk` folders and files to the `android\app\jni\SDL` directory. Open the `android` directory with Android Studio, press `Build > Make Project`. If you want to add more source code files, edit the `android\app\jni\src\Android.mk` file.

### DreamCast
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). Setup [KOS](https://gist.github.com/erfg12/a55328f50abaea15bd06d6584ed435af#file-kos-setup-easy-md) first, then [OpenGL](https://gist.github.com/erfg12/64285ce6e466fccbe8316f2e7594861a#file-kos-sdl-with-opengl-md). In the project directory, CD to `/dreamcast`, type `make`.

### GameCube
- - -
Install [DevKitPro](https://devkitpro.org/wiki/Getting_Started). Open `DevKitPro > MSys2`. Type `pacman -S gamecube-portlibs` and install ALL. In the project directory, CD to the `/gamecube` directory, type `make`.

### Linux (Ubuntu)
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). In Terminal, type `sudo apt update`, then `sudo apt install build-essential libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev`, then in the project directory, CD to the `/linux` directory. Now type `make`.

### MacOS (+ iOS)
- - -
On a Mac computer, download [SDL2 dmg](https://github.com/libsdl-org/SDL/releases/latest), open the DMG, place the framework file in `/library/frameworks` directory. Open `macos/game.xcodeproj` with XCode, press build.

### PlayStation 2
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). Setup [PS2Dev environment](https://gist.github.com/erfg12/45bb0311f53bf2037d338c357c8c33f0). In the project directory, CD to `/ps2`, type `make`.

### PSVita
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). First install [VitaSDK](https://vitasdk.org/). In the project directory, CD to the `/psvita` directory, then `chmod a+x ./psvita.sh`, and run `./build.sh`. In `/build` you will have your .vpk file.

### Switch
- - -
Install [DevKitPro](https://devkitpro.org/wiki/Getting_Started). Open `DevKitPro > MSys2`. Type `pacman -S switch-portlibs` and install ALL. In the project directory, CD to the `/switch` directory, type `make`.

### Web
- - -
* Clone `https://github.com/emscripten-core/emsdk.git`. Navigate to `emsdk` dir. 
* Linux/MacOS: `./emsdk install latest`, `./emsdk activate latest`, `source ./emsdk_env.sh`. Don't close Terminal. Go back to `/web` dir, type `chmod a+x build.sh` and `./build.sh`. 
* Windows: `emsdk install latest`, `emsdk activate latest`, `emsdk_env.bat`. Don't close command window. Go back to `/web` dir and run `build.bat`
* For testing, run `emrun build/game.html`. 

### Wii
- - -
Install [DevKitPro](https://devkitpro.org/wiki/Getting_Started). Open `DevKitPro > MSys2`. Type `pacman -S wii-portlibs` and install ALL. In the project directory, CD to the `/wii` directory, type `make`. Inside the `wii/apps/SharkShark` directory should now be a `res` folder and `boot.dol` file. Copy the `apps` folder to your Wii SD card and launch through the Homebrew Browser app.

### Wii U
- - -
1. Install [DevKitPro](https://devkitpro.org/wiki/Getting_Started). Open `DevKitPro > MSys2`. Type `pacman -S wiiu-portlibs` and install ALL.
2. Install libromfs-wiiu:
```
git clone https://github.com/yawut/libromfs-wiiu.git
cd libromfs-wiiu
make
sudo make install
```
3. In the project directory, CD to the `/wiiu` directory, type `make`.

### Windows
- - -
On a Windows computer, download [SDL2 vc zip](https://github.com/libsdl-org/SDL/releases), [TTF vc zip](https://github.com/libsdl-org/SDL_ttf/releases), [Mixer vc zip](https://github.com/libsdl-org/SDL_mixer/releases) unzip `lib` and `includes` directories to the `windows\sdl2-vc` directory. Open `windows\game.sln` file with Visual Studio, press build.

### Windows 9x (old)
- - -
On a Windows (95, 98, ME) computer, download [SDL VC6 zip](https://libsdl.org/release/SDL-devel-1.2.14-VC6.zip), [TTF VC6 zip](https://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-devel-2.0.8-VC6.zip), [Mixer VC6 zip](https://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-devel-1.2.7-VC6.zip) unzip `includes` directories to the `win9x\sdl-vc` directory, and the `lib` directory files to `C:\Program Files\Microsoft Visual Studio\VC98\Lib` directory. Open `win9x\game.sln` file with Visual Studio 6.0, press build.

### Xbox (original)
- - -
Use a Linux distro like Ubuntu (WSL for Windows users).

First time setup:
```
sudo apt update
sudo apt install build-essential cmake flex bison clang lld git llvm
cd ./xbox
sudo git clone --recursive https://github.com/fgsfdsfgs/nxdk.git ./nxdk
```

Copy this [Makefile](https://raw.githubusercontent.com/fgsfdsfgs/nxdk/development/lib/sdl/SDL2_mixer/Makefile) text, place the text at the top of the `nxdk/lib/sdl`'s Makefile.

To build:
```
./nxdk/bin/activate
make
```
Your .xbe file will be in the `bin` directory.
