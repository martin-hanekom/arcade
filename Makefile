IDIR=include
CC=g++
CFLAGS=-I$(IDIR)
LIBS=-lsfml-graphics -lsfml-system -lsfml-window
SDIR=src
ODIR=build

_DEPS=*.hpp
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o resource.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

arcade: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(ODIR) *~ core arcade $(IDIR)/*~