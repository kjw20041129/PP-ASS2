#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

// 函数声明
void generate_maze(int width, int height, char *filename);
int find_and_mark_path(char maze[MAX_SIZE][MAX_SIZE], int width, int height); // 修改为返回 int 类型

#endif
