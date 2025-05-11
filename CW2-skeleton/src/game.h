#ifndef GAME_H
#define GAME_H

#include "maze.h"

// 定义游戏结构体
typedef struct {
    Maze maze;          // 迷宫数据
    int player_x;       // 玩家的水平位置
    int player_y;       // 玩家的垂直位置
    int game_over;      // 游戏是否结束
    int win;            // 玩家是否胜利
} MazeGame;

// 函数原型声明
void load_maze(MazeGame *game, const char *filename);
// 加载迷宫文件并初始化游戏状态

void print_maze(const MazeGame *game);
// 打印迷宫，显示玩家当前位置

int player_move(MazeGame *game, char direction);
// 根据输入的方向移动玩家，返回是否成功移动

void game_quit(MazeGame *game);
// 退出游戏，设置游戏结束标志

int game_win(const MazeGame *game);
// 检查玩家是否到达终点，返回是否胜利

void free_maze_game(MazeGame *game);
// 释放游戏资源，包括迷宫内存

#endif // GAME_H
