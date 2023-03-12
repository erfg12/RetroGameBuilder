XBE_TITLE = Game
GEN_XISO = $(XBE_TITLE).iso
SRCS = $(CURDIR)/../game/shared.cpp $(CURDIR)/../game/main.cpp
NXDK_DIR ?= $(CURDIR)/nxdk
NXDK_SDL = y

include $(NXDK_DIR)/Makefile

TARGET += $(CURDIR)/../game/res
$(GEN_XISO): $(CURDIR)/../game/res
$(OUTPUT_DIR): $(CURDIR)/../game/res $(OUTPUT_DIR)/res
	$(VE)cp -R '$<' '$@'
