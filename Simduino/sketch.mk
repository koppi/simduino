LIBS_SIM += -L$(SIMDUINO) -Wl,-Bstatic -lSimduino
LIBS     += $(LIBS_SIM) -Wl,-Bdynamic -lm -Wl,--as-needed

CXX       = g++

CXXFLAGS += -std=c++11 -g -pedantic -I$(SIMDUINO)
LDFLAGS  += -g

-include $(SIMDUINO)/common.mk

all: $(BIN)

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o) $(SIMDUINO)/libSimduino.a
DEP = $(SRC:.cpp=.d)

$(BIN): $(OBJ)
	$(Q)echo "  ld $@"
	$(Q)$(CXX) -o $@ $^ $(LIBS)

$(SIMDUINO)/libSimduino.a:
	$(Q)make -C $(SIMDUINO)

.cpp.o:
	$(Q)echo "  cc $<"
	$(Q)$(CXX) -c $(CXXFLAGS) $<

.cpp.d:
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
