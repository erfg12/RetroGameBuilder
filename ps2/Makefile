EE_BIN = game.elf

EE_OBJS = ../game/sdl1/sdl1.o ../game/main.o

EE_INCS = -I$(HOME)/ps2dev/ps2sdk/ports/include
EE_LIBS = -L. -L$(HOME)/ps2dev/ps2sdk/ports/lib -L$(GSKIT)/lib -L../lib -lsdl -lcdvd
EE_CXXFLAGS = -D__PS2__

all: $(EE_BIN)

clean:
	rm -rf $(EE_BIN) $(EE_OBJS)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
