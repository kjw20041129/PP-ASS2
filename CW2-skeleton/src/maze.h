#ifndef MAZE_H
#define MAZE_H
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

#include <stdio.h>

#define MAX_DIM 100
#define MIN_DIM 5

typedef struct {
    int width;
    int height;
    char **maze;
} Maze;

// Function prototypes
int create_maze(Maze *maze, int height, int width);
void free_maze(Maze *maze);
int read_maze(Maze *maze, FILE *file);
void print_maze(const Maze *maze, int player_x, int player_y);

#endif // MAZE_H
