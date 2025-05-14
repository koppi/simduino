# Simduino top-level Makefile-------------------------------------------------

-include Simduino/common.mk

MAKEFLAGS += --no-print-directory

DIRS = $(shell find -mindepth 2 -name 'Makefile' -printf '%h\n' | sed -e 's/\.\///' | sort -u)

DIRS_BUILD = $(DIRS:%=build-%)
DIRS_TESTS = $(DIRS:%=tests-%)
DIRS_CLEAN = $(DIRS:%=clean-%)

all: $(DIRS_BUILD)

$(DIRS_BUILD):
	@echo " $(@:build-%=%)"
	$(Q)$(MAKE) -C $(@:build-%=%) all

test: $(DIRS_TESTS)

$(DIRS_TESTS):
	@echo " $(@:tests-%=%)"
	$(Q)$(MAKE) -C $(@:tests-%=%) test

clean: $(DIRS_CLEAN)

$(DIRS_CLEAN):
	@echo " $(@:clean-%=%)"
	$(Q)$(MAKE) -C $(@:clean-%=%) clean

.PHONY: all $(DIRS_BUILD) test $(DIRS_TESTS) clean $(DIRS_CLEAN)
