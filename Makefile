CFLAGS := $(shell pkg-config --cflags gtk4)
LIBS   := $(shell pkg-config --libs gtk4)

all:
	gcc src/main.c $(CFLAGS) $(LIBS)

