# Simduino top-level Makefile-------------------------------------------------

-include Simduino/common.mk

MAKEFLAGS += --no-print-directory

DIRS = $(shell find -mindepth 2 -name 'Makefile' -printf '%h\n' | sed -e 's/\.\///')

DIRS_BUILD = $(DIRS:%=build-%)
DIRS_CLEAN = $(DIRS:%=clean-%)

all: $(DIRS_BUILD)

$(DIRS_BUILD):
	@echo " Building $(@:build-%=%)"
	$(Q)$(MAKE) -C $(@:build-%=%)

clean: $(DIRS_CLEAN)

$(DIRS_CLEAN):
	@echo " Cleaning $(@:clean-%=%)"
	$(Q)$(MAKE) -C $(@:clean-%=%) clean

.PHONY: $(DIRS_BUILD) clean $(DIRS_CLEAN)
