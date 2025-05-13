#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MAZE_SIZE 100
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

typedef struct {
    int width;
    int height;
    char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
} Maze;

void initialize_maze(Maze *maze) {
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            maze->maze[i][j] = '#';
        }
    }
}

void print_maze(const Maze *maze) {
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            printf("%c", maze->maze[i][j]);
        }
        printf("\n");
    }
}

void generate_maze(Maze *maze) {
    int stack[MAX_MAZE_SIZE * MAX_MAZE_SIZE][2];
    int top = 0;

    int x = rand() % maze->width;
    int y = rand() % maze->height;

    maze->maze[y][x] = ' ';
    stack[top][0] = y;
    stack[top][1] = x;
    top++;

    while (top > 0) {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int valid_directions = 0;

        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i][1] * 2;
            int ny = y + directions[i][0] * 2;

            if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && maze->maze[ny][nx] == '#') {
                valid_directions++;
            }
        }

        if (valid_directions > 0) {
            int dir = rand() % valid_directions;
            for (int i = 0; i < 4; i++) {
                int nx = x + directions[i][1] * 2;
                int ny = y + directions[i][0] * 2;

                if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && maze->maze[ny][nx] == '#') {
                    if (dir == 0) {
                        maze->maze[y + directions[i][0]][x + directions[i][1]] = ' ';
                        maze->maze[ny][nx] = ' ';
                        stack[top][0] = ny;
                        stack[top][1] = nx;
                        top++;
                        x = nx;
                        y = ny;
                    }
                    dir--;
                }
            }
        } else {
            top--;
            if (top > 0) {
                y = stack[top - 1][0];
                x = stack[top - 1][1];
            }
        }
    }
}

void place_start_and_end(Maze *maze) {
    int start_x = rand() % maze->width;
    int start_y = rand() % maze->height;
    int end_x = rand() % maze->width;
    int end_y = rand() % maze->height;

    while (maze->maze[start_y][start_x] != ' ' || maze->maze[end_y][end_x] != ' ' || (start_x == end_x && start_y == end_y)) {
        start_x = rand() % maze->width;
        start_y = rand() % maze->height;
        end_x = rand() % maze->width;
        end_y = rand() % maze->height;
    }

    maze->maze[start_y][start_x] = 'S';
    maze->maze[end_y][end_x] = 'E';
}

void save_maze_to_file(const Maze *maze, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FILE_ERROR);
    }

    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            fputc(maze->maze[i][j], file);
        }
        fputc('\n', file);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./mazeGen <output_file> <width> <height>\n");
        return EXIT_ARG_ERROR;
    }

    int width = atoi(argv[2]);
    int height = atoi(argv[3]);

    if (width < 5 || width > 100 || height < 5 || height > 100) {
        printf("Error: Width and height must be between 5 and 100\n");
        return EXIT_MAZE_ERROR;
    }

    Maze maze = {width, height};
    initialize_maze(&maze);
    generate_maze(&maze);
    place_start_and_end(&maze);

    save_maze_to_file(&maze, argv[1]);

    return EXIT_SUCCESS;
}
