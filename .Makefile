CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c23
CPPFLAGS = -Iinclude/glad/include -Iinclude $(shell pkg-config --cflags glfw3)
LDLIBS  = $(shell pkg-config --libs glfw3) -lm -ldl

SRC = main.c include/glad/src/gl.c

all: main

main: $(SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(SRC) $(LDLIBS)
	./main

check: $(SRC)
	$(CC) $(CFLAGS) -fsyntax-only $(CPPFLAGS) $(SRC)

clean:
	rm -f main

.PHONY: all clean check
