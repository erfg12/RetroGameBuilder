XBE_TITLE = Game
GEN_XISO = $(XBE_TITLE).iso
SRCS = $(CURDIR)/../game/shared.cpp $(CURDIR)/../game/main.cpp
NXDK_DIR ?= $(CURDIR)/nxdk
NXDK_SDL = y

include $(NXDK_DIR)/Makefile

TARGET += $(OUTPUT_DIR)/../../game/res
$(GEN_XISO): $(OUTPUT_DIR)/../../game/res
$(OUTPUT_DIR): $(OUTPUT_DIR)/../../game/res $(OUTPUT_DIR)
	$(VE)cp -R '$<' '$@'
