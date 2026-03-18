# Variables
CC = gcc
CFLAGS = -I/opt/homebrew/include -std=c99
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework IOKit -framework Cocoa -framework OpenGL

# Target
all:
	$(CC) main.c -o game $(CFLAGS) $(LDFLAGS)

clean:
	rm game