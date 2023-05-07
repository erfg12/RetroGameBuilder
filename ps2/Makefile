EE_BIN = game.elf

EE_OBJS = ../game/shared.o ../game/main.o

EE_INCS = -I$(PS2DEV)/ps2sdk/ports/include -I../include -I$(PS2DEV)/ps2sdk/ports/include/SDL -I$(PS2DEV)/ps2sdk/ports/include/freetype2
EE_LIBS = -L. -L$(PS2DEV)/ps2sdk/ports/lib -L$(PS2DEV)/ps2sdk/ports/lib -L$(PS2DEV)/ps2sdk/ports/lib -L$(GSKIT)/lib -L$(DMAKIT)/lib -L../lib -L$(PS2SDK)/ee/lib -lpatches -lromfs -lsdlmixer -lSDL_ttf -lsdl -lcdvd -lgskit -ldmakit -lfreetype -lpng -lz
EE_CXXFLAGS = -D__PS2__

# ROMFS substitutions... :)
EE_CFLAGS += -Dfopen=ropen
EE_CFLAGS += -Dfclose=rclose
EE_CFLAGS += -Dfread=rread
EE_CFLAGS += -Dfwrite=rwrite
EE_CFLAGS += -Dfseek=rseek
EE_CFLAGS += -Dftell=rtell
EE_CFLAGS += -Dfgetc=rgetc
EE_CFLAGS += -Dfgets=rgets
EE_CFLAGS += -Dmmap=rmmap

#GENROMFS_PATH = $(PS2SDK)/bin
#GENROMFS = $(GENROMFS_PATH)/genromfs

all: $(EE_BIN)

#$(EE_BIN):
#	@$(GENROMFS) -f $@ -d res

clean:
	rm -rf $(EE_BIN) $(EE_OBJS)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal