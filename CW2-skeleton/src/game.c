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

    int start_found = 0;
    int end_found = 0;

    // Find start and end positions
    for (int i = 0; i < game->maze.height; i++) {
        for (int j = 0; j < game->maze.width; j++) {
            if (game->maze.maze[i][j] == 'S') {
                game->player_x = j;
                game->player_y = i;
                start_found = 1;
            } else if (game->maze.maze[i][j] == 'E') {
                end_found = 1;
            }
        }
    }

    fclose(file);

    if (!start_found) {
        fprintf(stderr, "Error: Maze lacks a starting point 'S'\n");
        exit(EXIT_MAZE_ERROR);
    }

    if (!end_found) {
        fprintf(stderr, "Error: Maze lacks an ending point 'E'\n");
        exit(EXIT_MAZE_ERROR);
    }

    game->game_over = 0;
    game->win = 0;
}


void print_game_maze(const MazeGame *game) {
    printf("\n");
    for (int i = 0; i < game->maze.height; i++) {
        for (int j = 0; j < game->maze.width; j++) {
            // 检查当前位置是否是起点或终点
            if (game->maze.maze[i][j] == 'S' || game->maze.maze[i][j] == 'E') {
                printf("%c", game->maze.maze[i][j]);
            } else if (game->player_x == j && game->player_y == i) {
                // 如果不是起点或终点，再检查是否是玩家位置
                printf("X");
            } else {
                // 其他位置正常打印迷宫内容
                printf("%c", game->maze.maze[i][j]);
            }
        }
        printf("\n");
    }
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
