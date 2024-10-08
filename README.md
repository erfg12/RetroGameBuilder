## About

This project's goal is compiling a game across multiple consoles and computers. The game's code is stored in the `/game` directory.

Currently most systems don't compile. Check the TO-DO section below to see what systems currently build.

## TO-DO
- [x] 3DS
- [x] Android
- [ ] DreamCast (no TTF lib)
- [x] iOS
- [x] Linux
- [x] MacOS
- [ ] Mac OS X (no PPC Frameworks)
- [ ] PlayStation 2 (issues loading mixer and ttf assets from CD)
- [x] PSP
- [x] PSVita
- [x] Switch
- [x] Windows 9x
- [x] Windows
- [x] Web
- [x] Wii
- [ ] Wii U (builds, but black screen)
- [x] Xbox (Original) (no audio)
- [X] Xbox (UWP)

## How To Build:

### 3DS
- - -
Install [DevKitPro](https://devkitpro.org/wiki/Getting_Started). Open `DevKitPro > MSys2`. Type `pacman -S 3ds-portlibs` and install ALL. In the project directory, CD to the `/3ds` directory, type `make`.

### Android
- - -
Using Windows, install Android Studio. Download the [SDL2 release source](https://github.com/libsdl-org/SDL)'s `include`, `src` and `Android.mk` folders and files to the `android\app\jni\SDL` directory. Do the same with [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases/) and [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases/). Copy the `game\res` directory to `android\app\src\main\assets` directory. Open the `android` directory with Android Studio, press `Build > Make Project`. If you want to add more source code files, edit the `android\app\jni\src\Android.mk` file.

### DreamCast
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). Setup [KOS](https://gist.github.com/erfg12/a55328f50abaea15bd06d6584ed435af#file-kos-setup-easy-md) first, then [OpenGL](https://gist.github.com/erfg12/64285ce6e466fccbe8316f2e7594861a#file-kos-sdl-with-opengl-md). In the project directory, CD to `/dreamcast`, type `make`.

### GameCube
- - -
Install [DevKitPro](https://devkitpro.org/wiki/Getting_Started). Open `DevKitPro > MSys2`. Type `pacman -S gamecube-portlibs` and install ALL. In the project directory, CD to the `/gamecube` directory, type `make`.

### iOS
- - -
On a Mac computer, download [SDL2](https://github.com/libsdl-org/SDL/releases), [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases) and [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases) sources. Unzip their contents into their `ios/libs` directories. Open `project/project.xcodeproj` with XCode, press build.

### Linux
- - -
Use a Linux distro like Ubuntu (WSL for Windows users). In Terminal, type `sudo apt update`, then `sudo apt install build-essential libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev`, then in the project directory, CD to the `/linux` directory. Now type `make`.

### MacOS
- - -
On a Mac computer, download [SDL2 dmg](https://github.com/libsdl-org/SDL/releases), [SDL2_ttf dmg](https://github.com/libsdl-org/SDL_ttf/releases) and [SDL2_mixer dmg](https://github.com/libsdl-org/SDL_mixer/releases) open the DMGs, place the framework files in the `/library/frameworks` directory. Open `macos/game.xcodeproj` with XCode, press build.

### PlayStation 2
- - -
On Windows, download Docker. Run docker, now open a command prompt at the RetroGameBuilder directory. Type: `docker run --rm -it -v %cd%:/usr/local/project -w /usr/local/project ps2dev/ps2dev sh`. You should now be in the Docker engine. Type: `apk add make mpc1-dev mpfr freetype libpng xorriso`, then `cd ./ps2`, `make`.

To build an iso disc image, use the command `mkisofs ./APP -o ./game.iso -allow-lowercase`

### PSP
- - -
Install [PSPDEV](https://pspdev.github.io/installation.html).

```
cd ./psp
mkdir build && cd build
psp-cmake ..
make
```

To edit the EBOOT file and add an icon, use [PSPBrew](https://www.brewology.com/downloads/get.php?id=5487).

To make a PSP ISO you need [EBOOT2ISO](https://www.brewology.com/downloads/get.php?id=10102) and [UMDGen](https://sea-02.dlo4d.com/files/umdgen/UMDGen_v4.00.rar).

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

If you plan on embeding the game into a website, you may want to change the canvas element to: `<canvas class="emscripten" id="canvas" tabindex=1></canvas>` and add the script `document.getElementById('canvas').focus();`. Also delete the emscripten svg and use `style="display:none;"` on the textarea output.

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

### Xbox (UWP)
- - -
Install Visual Studio with C++ UWP stuff. Download SDL2 source code releases (TTF and Mixer) and place zip contents into `uwp-xbone/sdl-sln` directories. Copy `game/res` directory to `uwp-xbone\XboxSDL`. Click build or debug on your console.

If SDL TTF Mixer projects are missing/blank even after adding source code to the `uwp-xbone/sdl-sln` directory, you have to add the `VisualC-WinRT/*.vcxproj` files. On TTF and Mixer you need to Add > Reference SDL-UWP, and on the game project, Add > Reference SDL TTF and Mixer. If it still doesn't build and says it can't find the .h files, you have to open the game project properties and add the include directory paths. 

NOTE: The `game/res` folder path is hard coded in the game project's .vcxproj file.
