# Modules of Simduino ----------------------------------------------------

TESTS += Tutorial/00-BareMinimum \
         Tutorial/01-Blink \
         Tutorial/02-DigitalReadSerial

TESTS += AccelStepper/Bounce \
	 AccelStepper/AFMotor_ConstantSpeed \
	 AccelStepper/AFMotor_MultiStepper

# Makefile Magic ---------------------------------------------------------

include Simduino/common.mk

DIRS = $(addprefix tests/,$(TESTS))

DIRS_BUILD = $(DIRS:%=build-%)
DIRS_CLEAN = $(DIRS:%=clean-%)

all: $(DIRS_BUILD)

$(DIRS_BUILD):
	@echo " Building $(@:build-%=%)"
	$(Q)@$(MAKE) -C $(@:build-%=%)

clean: $(DIRS_CLEAN)
	@echo " Cleaning Simduino"
	$(Q)@$(MAKE) -C Simduino clean

$(DIRS_CLEAN):
	@echo " Cleaning $(@:clean-%=%)"
	$(Q)@$(MAKE) -C $(@:clean-%=%) clean

.PHONY: $(DIRS_BUILD) clean $(DIRS_CLEAN)
