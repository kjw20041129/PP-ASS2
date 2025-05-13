#include "mazegen.h"

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

typedef struct {
    int x;
    int y;
} Point;

// 深度优先搜索生成迷宫
void dfs(char maze[MAX_SIZE][MAX_SIZE], int x, int y, int width, int height) {
    int dir[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int temp = dir[i];
        dir[i] = dir[j];
        dir[j] = temp;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + 2 * dx[dir[i]];
        int ny = y + 2 * dy[dir[i]];
        if (nx >= 0 && nx < height && ny >= 0 && ny < width && maze[nx][ny] == '#') {
            maze[nx][ny] = ' ';
            maze[x + dx[dir[i]]][y + dy[dir[i]]] = ' ';
            dfs(maze, nx, ny, width, height);
        }
    }
}

// 使用BFS找到路径并标记
void find_and_mark_path(char maze[MAX_SIZE][MAX_SIZE], int width, int height) {
    Point start = {-1, -1};
    Point end = {-1, -1};

    // 找到起点和终点
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (maze[i][j] == 'S') {
                start.x = i;
                start.y = j;
            } else if (maze[i][j] == 'E') {
                end.x = i;
                end.y = j;
            }
        }
    }

    if (start.x == -1 || end.x == -1) {
        printf("Start or end point not found\n");
        return;
    }

    // BFS
    int visited[MAX_SIZE][MAX_SIZE] = {0};
    Point parent[MAX_SIZE][MAX_SIZE];
    Point queue[MAX_SIZE * MAX_SIZE];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start.x][start.y] = 1;

    while (front < rear) {
        Point current = queue[front++];
        if (current.x == end.x && current.y == end.y) {
            // 找到路径
            Point at = end;
            while (at.x != start.x || at.y != start.y) {
                Point p = parent[at.x][at.y];
                maze[p.x][p.y] = ' ';
                at = p;
            }
            maze[start.x][start.y] = 'S'; // 保留起点
            maze[end.x][end.y] = 'E';     // 保留终点
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 && nx < height && ny >= 0 && ny < width && maze[nx][ny] != '#' && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                parent[nx][ny] = current;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }

    printf("No path found\n");
}

// 生成迷宫并保存到文件
void generate_maze(int width, int height, char *filename) {
    if (width < 5 || height < 5 || width > 100 || height > 100) {
        printf("Invalid maze size\n");
        return;
    }

    char maze[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            maze[i][j] = '#';
        }
    }

    int start_x = 1 + (rand() % (height - 2));
    int start_y = 1 + (rand() % (width - 2));
    maze[start_x][start_y] = 'S';

    dfs(maze, start_x, start_y, width, height);

    int end_x = 1 + (rand() % (height - 2));
    int end_y = 1 + (rand() % (width - 2));
    while (maze[end_x][end_y] == '#') {
        end_x = 1 + (rand() % (height - 2));
        end_y = 1 + (rand() % (width - 2));
    }
    maze[end_x][end_y] = 'E';

    find_and_mark_path(maze, width, height);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fputc(maze[i][j], file);
        }
        fputc('\n', file);
    }
    fclose(file);

    printf("Maze generated and saved to %s\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <filename> <width> <height>\n", argv[0]);
        return 1;
    }

    int width = atoi(argv[2]);
    int height = atoi(argv[3]);

    srand(time(NULL)); // 初始化随机数种子
    generate_maze(width, height, argv[1]);

    return 0;
}
