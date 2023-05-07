EE_BIN = game.elf

EE_OBJS = ../game/shared.o ../game/main.o

EE_INCS = -I$(PS2DEV)/ps2sdk/ports/include -I../include -I$(PS2DEV)/ps2sdk/ports/include/SDL -I$(PS2DEV)/ps2sdk/ports/include/freetype2
EE_LIBS = -L. -L$(PS2DEV)/ps2sdk/ports/lib -L$(PS2DEV)/ps2sdk/ports/lib -L$(PS2DEV)/ps2sdk/ports/lib -L$(GSKIT)/lib -L$(DMAKIT)/lib -L../lib -L$(PS2SDK)/ee/lib -lpatches -lsdlmixer -lSDL_ttf -lsdl -lcdvd -lgskit -ldmakit -lfreetype -lpng -lz
EE_CXXFLAGS = -D__PS2__

all: $(EE_BIN)

clean:
	rm -rf $(EE_BIN) $(EE_OBJS)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
