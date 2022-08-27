XBE_TITLE = Game
GEN_XISO = $(XBE_TITLE).iso
SRCS = $(CURDIR)/../game/sdl2/sdl2.cpp $(CURDIR)/../game/main.cpp
NXDK_DIR ?= $(CURDIR)/nxdk
NXDK_SDL = y

include $(NXDK_DIR)/Makefile

TARGET += $(OUTPUT_DIR)/resources
$(GEN_XISO): $(OUTPUT_DIR)/resources
$(OUTPUT_DIR)/resources: $(CURDIR)/resources $(OUTPUT_DIR)
	$(VE)cp -R '$<' '$@'
