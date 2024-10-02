PSP_LARGE_MEMORY = 1

TARGET = sharkshark
OBJS = ../game/shared.o ../game/main.o

INCDIR =
CFLAGS = -G0 -O2 -Wall -g -DPSP -DCONSOLE -D__PSP__
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lSDL2main -lSDL2_image -lpng -ljpeg -lSDL2_mixer -lstdc++ -lpspgum_vfpu -lpspvfpu -lSDL2_ttf -lSDL2 -lGL -lGLU -lglut -lfreetype -lharfbuzz -lz -lvorbis -lvorbisfile -lpspvfpu -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lm -lpspvram -lxmp -logg -lmodplug -lzip -lbz2

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = SharkShark
PSP_EBOOT_ICON = psp/icon.png
PSP_EBOOT_PIC1 = psp/pic.png

PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)
include $(PSPSDK)/lib/build.mak

