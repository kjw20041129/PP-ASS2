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
    int height = 0, width = 0, first_width = 0;
    char buffer[MAX_DIM + 2]; // 额外空间处理长行
    char **temp_maze = NULL;

    // 第一阶段：计算迷宫尺寸
    while (fgets(buffer, sizeof(buffer), file)) {
        int current_width = strlen(buffer);
        // 仅删除行尾换行符（兼容Windows/Linux格式）
        while (current_width > 0 && (buffer[current_width - 1] == '\n' || buffer[current_width - 1] == '\r')) {
            buffer[current_width - 1] = '\0';
            current_width--;
        }

        // 检测行截断（关键修复）
        if (current_width >= MAX_DIM) {
            printf("Error: Line %d exceeds maximum width\n", height + 1);
            return 1;
        }

        // 首次读取时设置参考宽度
        if (height == 0) first_width = current_width;
        if (current_width != first_width) {
            printf("Error: Inconsistent width at line %d\n", height + 1);
            return 1;
        }
        width = current_width;
        height++;
    }

    // 验证尺寸合法性
    if (height < MIN_DIM || height > MAX_DIM || width < MIN_DIM || width > MAX_DIM) {
        printf("Error: Invalid dimensions %dx%d\n", height, width);
        return 1;
    }

    // 第二阶段：读取迷宫内容
    rewind(file);
    temp_maze = (char **)malloc(height * sizeof(char *));
    if (!temp_maze) return 1;

    for (int i = 0; i < height; i++) {
        if (!fgets(buffer, sizeof(buffer), file)) {
            printf("Error: Incomplete file\n");
            for (int j = 0; j < i; j++) free(temp_maze[j]); // 逐级释放
            free(temp_maze);
            return 1;
        }

        // 二次处理行尾（确保两次处理一致）
        int current_width = strlen(buffer);
        while (current_width > 0 && (buffer[current_width - 1] == '\n' || buffer[current_width - 1] == '\r')) {
            buffer[current_width - 1] = '\0';
            current_width--;
        }

        // 验证行宽一致性（关键修复）
        if (current_width != width) {
            printf("Error: Width mismatch at line %d\n", i + 1);
            for (int j = 0; j < i; j++) free(temp_maze[j]);
            free(temp_maze);
            return 1;
        }

        temp_maze[i] = (char *)malloc(width + 1); // 替代strdup
        if (!temp_maze[i]) {
            for (int j = 0; j < i; j++) free(temp_maze[j]);
            free(temp_maze);
            return 1;
        }
        strcpy(temp_maze[i], buffer);
    }

    // 第三阶段：填充迷宫结构
    if (create_maze(maze, height, width) != 0) {
        for (int i = 0; i < height; i++) free(temp_maze[i]);
        free(temp_maze);
        return 1;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char c = temp_maze[i][j];
            // 严格字符验证（保留有效空格）
            if (c != '#' && c != ' ' && c != 'S' && c != 'E') {
                printf("Error: Invalid char '%c' at (%d,%d)\n", c, i, j);
                free_maze(maze);
                for (int k = 0; k < height; k++) free(temp_maze[k]);
                free(temp_maze);
                return 1;
            }
            maze->maze[i][j] = c;
        }
        free(temp_maze[i]); // 逐行释放临时内存
    }
    free(temp_maze);

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
