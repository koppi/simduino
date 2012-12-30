# Modules of Simduino ----------------------------------------------------

TESTS = AccelStepper/Bounce \
		AccelStepper/AFMotor_ConstantSpeed \
		AccelStepper/AFMotor_MultiStepper

# Makefile Magic ---------------------------------------------------------

DIRS = $(addprefix tests/,$(TESTS))

DIRS_BUILD = $(DIRS:%=build-%)
DIRS_CLEAN = $(DIRS:%=clean-%)

all: $(DIRS_BUILD)

$(DIRS_BUILD):
	@echo " Building $(@:build-%=%)"
	@$(MAKE) --no-print-directory -C $(@:build-%=%)

clean: $(DIRS_CLEAN)
	@echo " Cleaning Simduino"
	@$(MAKE) --no-print-directory -C Simduino clean

$(DIRS_CLEAN):
	@echo " Cleaning $(@:clean-%=%)"
	@$(MAKE) --no-print-directory -C $(@:clean-%=%) clean

.PHONY: $(DIRS_BUILD) clean $(DIRS_CLEAN)
