/**
 * @file maze.c
 * @author Jiawen Kang
 * @brief Code for the maze game for COMP1921 Assignment 2
 * NOTE - You can remove or edit this file however you like - this is just a provided skeleton code
 * which may be useful to anyone who did not complete assignment 1.
 */

#include "maze.h"
#include <stdlib.h>
#include <string.h>

int create_maze(Maze *this, int height, int width) {
    this->height = height;
    this->width = width;
    this->map = (char **)malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) {
        this->map[i] = (char *)malloc(width * sizeof(char));
        if (this->map[i] == NULL) {
            return 1; // Memory allocation failed
        }
    }
    return 0;
}

void free_maze(Maze *this) {
    for (int i = 0; i < this->height; i++) {
        free(this->map[i]);
    }
    free(this->map);
}

int get_width(FILE *file) {
    int width = 0;
    char ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF) {
        width++;
    }
    rewind(file); // Reset file pointer
    return width;
}

int get_height(FILE *file) {
    int height = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            height++;
        }
    }
    rewind(file); // Reset file pointer
    return height + 1; // Include the last row
}

int read_maze(Maze *this, FILE *file) {
    int height = get_height(file);
    int width = get_width(file);
    if (height < MIN_DIM || height > MAX_DIM || width < MIN_DIM || width > MAX_DIM) {
        return 1; // Invalid dimensions
    }
    if (create_maze(this, height, width) != 0) {
        return 1; // Memory allocation failed
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->map[i][j] = fgetc(file);
            if (this->map[i][j] == 'S') {
                this->start.x = j;
                this->start.y = i;
            } else if (this->map[i][j] == 'E') {
                this->end.x = j;
                this->end.y = i;
            }
        }
        fgetc(file); // Consume newline
    }
    return 0;
}

void print_maze(Maze *this, Coord *player) {
    printf("\n");
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (player->x == j && player->y == i) {
                printf("X");
            } else {
                printf("%c", this->map[i][j]);
            }
        }
        printf("\n");
    }
}
