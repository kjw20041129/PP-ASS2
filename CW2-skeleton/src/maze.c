#include "maze.h"
#include <stdlib.h>
#include <string.h>

int create_maze(Maze *maze, int height, int width) {
    maze->height = height;
    maze->width = width;
    maze->maze = (char **)malloc(height * sizeof(char *));
    if (!maze->maze) return 1; // Memory allocation failed

    for (int i = 0; i < height; i++) {
        maze->maze[i] = (char *)malloc(width * sizeof(char));
        if (!maze->maze[i]) {
            // Free previously allocated memory if allocation fails
            for (int j = 0; j < i; j++) {
                free(maze->maze[j]);
            }
            free(maze->maze);
            return 1;
        }
    }
    return 0;
}

void free_maze(Maze *maze) {
    for (int i = 0; i < maze->height; i++) {
        free(maze->maze[i]);
    }
    free(maze->maze);
}

int read_maze(Maze *maze, FILE *file) {
    int height = 0, width = 0;
    char buffer[MAX_DIM + 1];

    // Determine maze dimensions
    while (fgets(buffer, MAX_DIM + 1, file)) {
        width = strlen(buffer) - 1; // Remove newline character
        height++;
    }
    rewind(file);

    if (height < MIN_DIM || height > MAX_DIM || width < MIN_DIM || width > MAX_DIM) {
        return 1; // Invalid dimensions
    }

    if (create_maze(maze, height, width) != 0) {
        return 1; // Memory allocation failed
    }

    for (int i = 0; i < height; i++) {
        if (!fgets(buffer, MAX_DIM + 1, file)) {
            free_maze(maze);
            return 1; // File read error
        }
        for (int j = 0; j < width; j++) {
            maze->maze[i][j] = buffer[j];
        }
    }
    return 0;
}

void print_maze(const Maze *maze, int player_x, int player_y) {
    printf("\n");
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            if (player_x == j && player_y == i) {
                printf("X");
            } else {
                printf("%c", maze->maze[i][j]);
            }
        }
        printf("\n");
    }
}
