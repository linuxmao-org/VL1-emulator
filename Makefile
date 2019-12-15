#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX, Christopher Arndt, and Patrick Desaulniers
#

include dpf/Makefile.base.mk

all: libs plugins gen

# --------------------------------------------------------------

submodules:
	git submodule update --init --recursive

libs:
	$(MAKE) -C dpf/dgl ../build/libdgl-cairo.a
#	$(MAKE) -C dpf/dgl ../build/libdgl-opengl.a

plugins: libs res
	$(MAKE) all -C plugins/VL1

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen: plugins dpf/utils/lv2_ttl_generator.exe
	@$(CURDIR)/dpf/utils/generate-ttl.sh

dpf/utils/lv2_ttl_generator.exe:
	$(MAKE) -C dpf/utils/lv2-ttl-generator WINDOWS=true
endif

# --------------------------------------------------------------

res: gen/VL1EditRes.cpp

gen/VL1EditRes.cpp: resources/VL1EditRes.json utils/bin/rescc$(APP_EXT)
	@install -d gen
	utils/bin/rescc$(APP_EXT) $< > $@

utils/bin/rescc$(APP_EXT):
	$(MAKE) bin/rescc$(APP_EXT) -C utils

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/VL1
	$(MAKE) clean -C utils
	rm -rf bin build gen

install: all
	$(MAKE) install -C plugins/VL1

install-user: all
	$(MAKE) install-user -C plugins/VL1

# --------------------------------------------------------------

.PHONY: all clean install install-user submodule libs plugins gen res
