CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
TARGETS = maze mazegen

# 主程序maze的源文件
MAZE_SOURCES = main.c game.c maze.c
MAZE_OBJECTS = $(MAZE_SOURCES:.c=.o)

# Maze Generator的源文件
MAZEGEN_SOURCES = mazegen.c
MAZEGEN_OBJECTS = $(MAZEGEN_SOURCES:.c=.o)

all: $(TARGETS)

maze: $(MAZE_OBJECTS)
	$(CC) $(CFLAGS) -o maze $(MAZE_OBJECTS)

mazegen: $(MAZEGEN_OBJECTS)
	$(CC) $(CFLAGS) -o mazegen $(MAZEGEN_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAZE_OBJECTS) $(MAZEGEN_OBJECTS) $(TARGETS)
