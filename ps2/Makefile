EE_BIN = game.elf

EE_OBJS = ../game/shared.o ../game/main.o

EE_INCS = -I$(PS2DEV)/ps2sdk/ports/include -I../include -I$(PS2DEV)/ps2sdk/ports/include/SDL -I$(PS2DEV)/ps2sdk/ports/include/freetype2
EE_LDFLAGS = -L$(PS2SDK)/ports/lib -L$(GSKIT)/lib
EE_LIBS = -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lmodplug -lps2_drivers -lcdvd -lgskit -ldmakit -lfreetype -lpng -lvorbis -lmikmod -lmad -lz -lmc -lromfs -lc -lstdc++
EE_CXXFLAGS = -D__PS2__ -Dmain=SDL_main -DHAVE_SDL2 -ffast-math -fsingle-precision-constant

# This is for the sbv patch
SBVLITE = $(PS2SDK)/sbv
EE_INCS += -I$(SBVLITE)/include
EE_LDFLAGS += -L$(SBVLITE)/lib
EE_LIBS += -lpatches

all: $(EE_BIN)

clean:
	rm -f $(EE_BIN) $(EE_OBJS)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal