-include $(SIMDUINO)/common.mk

LIBS_SIM  += -L$(SIMDUINO) -Wl,-Bstatic -lSimduino
LIBS      += $(LIBS_SIM) -Wl,-Bdynamic -lm -Wl,--as-needed

CXX       ?= g++

CXXFLAGS  += -std=c++11 -g -pedantic -I$(SIMDUINO) -DSIM
LDFLAGS   += -g

# test timeout in seconds. 10sec default
TIMEOUT   ?= 14

# the number of sim loops to run. 3 loops default
TEST_ARGS ?= 3

all: $(BIN)

SRC_CXX = $(wildcard *.cpp)
SRC_PDE = $(wildcard *.pde)
SRC_C   = $(wildcard *.c)

OBJ     = $(SRC_PDE:.pde=.o) $(SRC_CXX:.cpp=.o) $(SRC_C:.c=.o) $(SIMDUINO)/libSimduino.a
DEP     = $(SRC_PDE:.pde=.d) $(SRC_CXX:.cpp=.d) $(SRC_C:.c=.d)

test: $(BIN)
	-$(Q)$(SIMDUINO)/test.sh $(TIMEOUT) ./$(BIN) $(TEST_ARGS)
	$(Q)mv output.gif $(BIN:.exe=.gif)

$(BIN): $(OBJ)
	$(Q)echo "  ld $@"
	$(Q)$(CXX) -o $@ $^ $(LIBS)

$(SIMDUINO)/libSimduino.a:
	$(Q)make -C $(SIMDUINO)

.c.o:
	$(Q)echo "  cc $<"
	$(Q)$(CXX) -c $(CXXFLAGS) $<

.c.d:
	$(Q)$(CXX) $(CXXFLAGS) -MM -MD -o $@ $<

%.o: %.cpp
	$(Q)echo "  cc $<"
	$(Q)$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.pde
	$(Q)echo "  cc $<"
	$(Q)$(CXX) $(CXXFLAGS) -c -x c++ -o $@ $<

.cpp.d:
	$(Q)$(CXX) $(CXXFLAGS) -MM -MD -o $@ $<

.pde.d:
	$(Q)$(CXX) $(CXXFLAGS) -MM -MD -o $@ $<

-include $(DEP)

# Suffixes and phony targets -----------------------------------------------

.SUFFIXES: .h .cpp .d

PHONY += all clean
scripts: ;
PHONY += FORCE
FORCE:

.PHONY: $(PHONY)

# Clean target -------------------------------------------------------------

clean:
	@rm -rf $(BIN) $(OBJ) $(DEP) *~ 
