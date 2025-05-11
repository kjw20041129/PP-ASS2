#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./maze <maze_file>\n");
        return EXIT_ARG_ERROR;
    }

    MazeGame game;
    load_maze(&game, argv[1]);

    printf("Welcome to the Maze Game!\n");
    print_maze(&game);

    while (!game.game_over) {
        char input;
        printf("Enter move (WASD) or 'M' to show maze, 'Q' to quit: ");
        scanf(" %c", &input);

        if (input == 'M' || input == 'm') {
            print_maze(&game);
        } else if (input == 'Q' || input == 'q') {
            game_quit(&game);
        } else {
            player_move(&game, input);
        }

        game.win = game_win(&game);
        game.game_over = game.win || input == 'Q' || input == 'q';
    }

    free_maze_game(&game);

    if (game.win) {
        printf("Congratulations! You've won the game!\n");
    }

    return 0;
}
