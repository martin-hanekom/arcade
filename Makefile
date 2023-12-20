IDIR=include
CC=g++
CFLAGS=-I$(IDIR)
LIBS=-lsfml-graphics -lsfml-system -lsfml-window
SOURCES=$(wildcard src/%.cpp) $(wildcard src/*/%.cpp)
SDIR=src
ODIR=build

_DEPS=*.hpp
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o game.o resource.o bubbles.o player.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

sources := $(wildcard $(SDIR)/*.cpp) $(wildcard $(SDIR)/*/*.cpp)
objects := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(sources))

$(ODIR)/*/%.o: $(SDIR)/*/%.cpp
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

#$(ODIR)/%.o: $(SOURCES)
#mkdir -p $(ODIR)
#$(CC) -c -o $@ $< $(CFLAGS)

arcade: $(objects)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(ODIR) *~ core arcade $(IDIR)/*~