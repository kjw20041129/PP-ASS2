#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    // 定义迷宫游戏的结构体
    int width; // 迷宫的宽度
    int height; // 迷宫的高度
    char** maze; // 二维数组迷宫
    int player_x; // 玩家的水平位置
    int player_y; // 玩家的垂直位置
    int game_over; // 游戏是否结束
    int win; // 玩家是否胜利
    //int move_count; // 玩家移动次数
    //time_t start_time; // 游戏开始时间
    //time_t win_time; // 玩家通关时间
} MazeGame;

void load_maze(MazeGame* game, const char* filename);
//加载迷宫，初始化玩家位置


void print_maze(const MazeGame* game);
//打印迷宫


int player_move(MazeGame* game, char direction);
//玩家通过键盘输入控制移动


void game_quit(MazeGame* game);
//玩家退出游戏


int game_win(const MazeGame* game);
//玩家到达终点，游戏结束


void free_maze_game(MazeGame* game);
//释放内存

int main(int argc, char* argv[]) {
    //检查命令行参数
    if (argc != 2) {
        printf("Usage: ./maze <maze_file>\n");
        return 1;
    }

    MazeGame game; //创建实例

    //初始化游戏
    load_maze(&game, argv[1]);

    //游戏主循环
    while (!game.game_over) {
        char input;
        scanf(" %c", &input); //获取玩家输入

        if (input == 'M' || input == 'm') {
            //打印迷宫
            print_maze(&game);
        } else if (input == 'Q' || input == 'q') {
            //退出游戏
            game_quit(&game);
        } else {
            //玩家移动
            player_move(&game, input);
        }

        //检查是否到达终点
        game.win = game_win(&game);
        //更新游戏状态
        game.game_over = game.win || input == 'Q' || input == 'q';
    }

    //释放资源
    free_maze_game(&game);

    //输出胜利信息
    if (game.win) {
        printf("Congratulations! You've won the game!\n");
    }

    return 0;
}
