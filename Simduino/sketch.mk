-include $(SIMDUINO)/common.mk

# Some extra libraries --------------------------------------------------------

ifeq ($(shell pkg-config --exists sdl && echo "1" || echo "0"), 1)
CXXFLAGS  += $(shell pkg-config --cflags sdl)
LIBS      += $(shell pkg-config --libs   sdl)
CXXFLAGS  += -DHAVE_SDL
endif

ifeq ($(shell pkg-config --exists SDL_gfx && echo "1" || echo "0"), 1)
CXXFLAGS  += $(shell pkg-config --cflags SDL_gfx)
LIBS      += $(shell pkg-config --libs   SDL_gfx)
CXXFLAGS  += -DHAVE_SDL_GFX
endif

ifeq ($(shell pkg-config --exists SDL_image && echo "1" || echo "0"), 1)
CXXFLAGS  += $(shell pkg-config --cflags SDL_image)
LIBS      += $(shell pkg-config --libs   SDL_image)
CXXFLAGS  += -DHAVE_SDL_IMAGE
endif

ifeq ($(shell pkg-config --exists SDL_ttf && echo "1" || echo "0"), 1)
CXXFLAGS  += $(shell pkg-config --cflags SDL_ttf)
LIBS      += $(shell pkg-config --libs   SDL_ttf)
CXXFLAGS  += -DHAVE_SDL_TTF
endif

# -----------------------------------------------------------------------------

LIBS_SIM  += -L$(SIMDUINO) -Wl,-Bstatic -lSimduino
LIBS      += $(LIBS_SIM) -Wl,-Bdynamic -lm -Wl,--as-needed

CXX       ?= g++

CXXFLAGS  += -std=c++11 -g -pedantic -I$(SIMDUINO) -DSIM
LDFLAGS   += -g

# test timeout in seconds. 10sec default
TIMEOUT   ?= 10

# the number of sim loops to run. 3 loops default
TEST_ARGS ?= 3

all: $(BIN)

SRC_CXX = $(wildcard *.cpp)
SRC_PDE = $(wildcard *.pde)
SRC_C   = $(wildcard *.c)

OBJ     = $(SRC_PDE:.pde=.o) $(SRC_CXX:.cpp=.o) $(SRC_C:.c=.o) $(SIMDUINO)/libSimduino.a
DEP     = $(SRC_PDE:.pde=.d) $(SRC_CXX:.cpp=.d) $(SRC_C:.c=.d)

test: $(BIN)
	-$(Q)$(SIMDUINO)/timeout.sh $(TIMEOUT) ./$(BIN) $(TEST_ARGS)

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
