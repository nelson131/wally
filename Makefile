CFLAGS := $(shell pkg-config --cflags gtk4 gtk4-layer-shell-0)
LIBS   := $(shell pkg-config --libs gtk4 gtk4-layer-shell-0)

all:
	gcc src/main.c src/ui.c $(CFLAGS) $(LIBS)

