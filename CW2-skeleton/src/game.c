#include "game.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void load_maze(MazeGame *game, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open maze file");
        exit(EXIT_FILE_ERROR);
    }

    if (read_maze(&game->maze, file) != 0) {
        fprintf(stderr, "Invalid maze file\n");
        fclose(file);
        exit(EXIT_MAZE_ERROR);
    }

    // Find start position
    for (int i = 0; i < game->maze.height; i++) {
        for (int j = 0; j < game->maze.width; j++) {
            if (game->maze.maze[i][j] == 'S') {
                game->player_x = j;
                game->player_y = i;
                game->maze.maze[i][j] = ' '; // Clear start marker
                break;
            }
        }
    }

    game->game_over = 0;
    game->win = 0;
    fclose(file);
}

void print_game_maze(const MazeGame *game) {
    print_maze(&game->maze, game->player_x, game->player_y);
}

int player_move(MazeGame *game, char direction) {
    int new_x = game->player_x;
    int new_y = game->player_y;

    switch (direction) {
        case 'W': case 'w': new_y--; break;
        case 'A': case 'a': new_x--; break;
        case 'S': case 's': new_y++; break;
        case 'D': case 'd': new_x++; break;
        default: return 0; // Invalid direction
    }

    if (new_x < 0 || new_x >= game->maze.width || new_y < 0 || new_y >= game->maze.height) {
        printf("Cannot move out of bounds\n");
        return 0;
    }

    if (game->maze.maze[new_y][new_x] == '#') {
        printf("Cannot move through walls\n");
        return 0;
    }

    game->player_x = new_x;
    game->player_y = new_y;
    return 1;
}

void game_quit(MazeGame *game) {
    game->game_over = 1;
}

int game_win(const MazeGame *game) {
    return game->maze.maze[game->player_y][game->player_x] == 'E';
}

void free_maze_game(MazeGame *game) {
    free_maze(&game->maze);
}
