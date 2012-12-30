LIBS_SIM += -L$(SIMDUINO) -Wl,-Bstatic -lSimduino
LIBS     += $(LIBS_SIM) -Wl,-Bdynamic -lm -Wl,--as-needed

CXXFLAGS += -std=c++11 -g -pedantic -I$(SIMDUINO)
LDFLAGS  += -g

all: $(BIN)

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o) $(SIMDUINO)/libSimduino.a
DEP = $(SRC:.cpp=.d)

$(BIN): $(OBJ)
	@echo "  ld $@"
	@$(CXX) -o $@ $^ $(LIBS)

$(SIMDUINO)/libSimduino.a:
	@make --no-print-directory -C $(SIMDUINO)

.cpp.o:
	@echo "  cc $<"
	@$(CXX) -c $(CXXFLAGS) $<

.cpp.d:
	@$(CXX) $(CXXFLAGS) -MM -MD -o $@ $<

-include $(DEP)

# Suffixes and phony targets -----------------------------------------------

.SUFFIXES: .h .cpp .d
.PHONY:    all clean

# Clean target -------------------------------------------------------------

clean:
	@rm -rf $(BIN) $(OBJ) $(DEP) *~ 
