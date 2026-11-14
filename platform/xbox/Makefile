# Standalone nxdk platform/memory probe, NOT the complete emulator.
XBE_TITLE = EKA2L1\ Port\ Probe
SRCS = $(CURDIR)/main.cpp $(CURDIR)/memory_probe.cpp
CXXFLAGS += -std=c++20
ifndef NXDK_DIR
$(error NXDK_DIR is required: activate nxdk using its bin/activate script)
endif
include $(NXDK_DIR)/Makefile
