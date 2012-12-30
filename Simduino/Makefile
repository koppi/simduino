# Simduino Makefile ------------------------------------------------------

BIN = libSimduino.a

# G++ Compiler flags -----------------------------------------------------

CXX      ?= g++
AR       ?= ar
CXXFLAGS += -std=c++11 -g -I. -pedantic

# Main target ------------------------------------------------------------

-include common.mk

all: $(BIN)
	@echo " Built $(BIN)"

# Source files -----------------------------------------------------------

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

# Compile targets --------------------------------------------------------

$(BIN): $(OBJ) Makefile
	@echo "  ld $@"
	$(Q)$(AR) rcs $@ $^

.cpp.o: Makefile
	@echo "  cc $<"
	$(Q)$(CXX) -c $(CXXFLAGS) $<

# Dependency resolution targets ------------------------------------------

.cpp.d: Makefile
	$(Q)$(CXX) $(CXXFLAGS) -MM -MD -o $@ $<

-include $(DEP)

# Suffixes and phony targets ---------------------------------------------

.SUFFIXES: .h .cpp .d
.PHONY:    all clean

# Clean target -----------------------------------------------------------

clean:
	@rm -rf $(BIN) $(OBJ) $(DEP) *~ 
