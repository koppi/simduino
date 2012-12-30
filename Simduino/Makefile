# Simduino Makefile ------------------------------------------------------

BIN = libSimduino.a

# G++ Compiler flags -----------------------------------------------------

CXXFLAGS += -std=c++11 -g -I. -pedantic

# Main target ------------------------------------------------------------

all: $(BIN)
	@echo " Built $(BIN)"

# Source files -----------------------------------------------------------

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

# Compile targets --------------------------------------------------------

$(BIN): $(OBJ) Makefile
	@echo "  ld $@"
	@$(AR) rcs $@ $^

.cpp.o: Makefile
	@echo "  cc $<"
	@$(CXX) -c $(CXXFLAGS) $<

# Dependency resolution targets ------------------------------------------

.cpp.d: Makefile
	@$(CXX) $(CXXFLAGS) -MM -MD -o $@ $<

-include $(DEP)

# Suffixes and phony targets ---------------------------------------------

.SUFFIXES: .h .cpp .d
.PHONY:    all clean

# Clean target -----------------------------------------------------------

clean:
	@rm -rf $(BIN) $(OBJ) $(DEP) *~ 
