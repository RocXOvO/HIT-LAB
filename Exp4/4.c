#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF 100000000
#define STEP 1000
/* 使用DFS算法找到钥匙'$'，输出每次移动的方向以及最后的路径长度 */
typedef struct {
    int r;
    int c;
} Point;

// 定义了一个栈帧的状态，其目的主要是表明该节点是否已经访问完所有的邻居。
typedef struct {
    Point p;
    int next_move; // 0 1 2 3 表明方向
} Point_Frame; 

typedef struct {
    Point p;
    int g_cost;
    int h_cost;
    int f_cost; // f_cost = g_cost + h_cost
} AStarNode;

int manhattan(int x1, int y1, int x2, int y2);
void findKey(char **maze, int width, int height, int startX, int startY) {
    Point_Frame stack[STEP];
    int top = -1;
    int dr[] = {0, 1, 0, -1};   // 右 下 左 上
    int dc[] = {1, 0, -1, 0};
    char dic_move[] = {'R', 'D', 'L', 'U'};
    char reverse_dic_move[] = {'L', 'U','R', 'D'}; //方便输出逆转的路径
    int visited[width][height]; // 行数由width决定，列数由height决定
    Point key_position = {-1, -1};
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            visited[i][j] = 0;
        }
    }
    // 记录每个点的先驱
    Point prev[width][height];
    // 记录前驱通过什么操作到达这个点
    char movement[width][height];

    stack[++top] = (Point_Frame) {{startX, startY}, 0};
    visited[startX][startY] = 1;
    prev[startX][startY] = (Point) {-1, -1};
    // 压栈
    while (top != -1) {

        Point_Frame *current_frame = &stack[top];
        Point u = current_frame->p;
        // 找到了KEY
        if (maze[u.r][u.c] == '$') {
            key_position = u;
            break;
        }
        // 查看邻居是否可以走
        // 要按 顺序存入栈，如果要访问就得反过来存进去
        if (current_frame->next_move < 4) {
            int direction = current_frame->next_move;
            current_frame->next_move++;
            Point next_point = (Point){u.r + dr[direction], u.c + dc[direction]};
            // 1.不越界 2.未访问过 3. 不是墙壁
            // 既可以压栈
            if (next_point.r >= 0 && next_point.r < width &&
                next_point.c >= 0 && next_point.c < height &&
                !visited[next_point.r][next_point.c] &&
                maze[next_point.r][next_point.c] != '1') {
                    visited[next_point.r][next_point.c] = 1;
                    prev[next_point.r][next_point.c] = u;
                    movement[next_point.r][next_point.c] = dic_move[direction];
                    stack[++top].p = next_point;
                    stack[top].next_move = 0;
                    printf("->%c", movement[next_point.r][next_point.c]);
                }
        } else {
            top--;
            if (top != -1) {
                for (int k = 0; k < 4; k++){
                    if (movement[u.r][u.c] == dic_move[k]) {
                        printf("->%c", reverse_dic_move[k]);
                        break;
                    }
                }
            }
        }
    }
    printf("\n");
    // 输出钥匙到起点的距离
    Point c_point = (Point) {key_position.r, key_position.c};
    int key_path_len = 0;
    while (prev[c_point.r][c_point.c].r != -1) {
        c_point = prev[c_point.r][c_point.c];
        key_path_len++;
    }
    printf("%d\n", key_path_len);
}

/* 返回两点之间的曼哈顿距离 */
int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

/* 使用A*算法寻找出口'#'，输出每次扩展的点以及最后的路径 */
void findDoor(char **maze, int width, int height, int startX, int startY, int endX, int endY) {
    AStarNode open_set[height * width];
    int open_set_count = 0;
    int visited[width][height];
    Point prev[width][height];
    int cost[width][height];
    Point path_expand[STEP]; // 记录A*算法访问每个点的路径。
    int count = 0;
    // 初始化
    for (int i = 0;i < width; i++) {
        for (int j = 0; j < height; j++) {
            visited[i][j] = 0;
            cost[i][j] = INF;
        }
    }
    prev[startX][startY] = (Point) {-1, -1};
    Point start_node = (Point) {startX, startY};
    int start_node_f_cost = manhattan(startX, startY, endX, endY);
    open_set[open_set_count++] = (AStarNode) {start_node, 0, start_node_f_cost, start_node_f_cost};

    int dr[] = {0, 1, 0, -1};   // 右 下 左 上
    int dc[] = {1, 0, -1, 0};
    char dic_move[] = {'R', 'D', 'L', 'U'};

    // 添加节点
    while (open_set_count > 0) {
        int min_cost = INF;
        int min_index = -1;
        // 找最小的值，并有最小值找寻策略。
        for (int i = open_set_count - 1; i >= 0; i--) {
            if (open_set[i].f_cost < min_cost) {
                min_cost = open_set[i].f_cost; // 得到最小值
                min_index = i;
            } else if (open_set[i].f_cost == min_cost) {
                if (open_set[i].p.r > open_set[min_index].p.r) {
                    min_index = i;
                } else if (open_set[i].p.r == open_set[min_index].p.r && open_set[i].p.c > open_set[min_index].p.c) {
                    min_index = i;
                }
            }
        }
        Point current_point = open_set[min_index].p; // 当前访问的节点。
        int current_point_g_cost = open_set[min_index].g_cost;
        visited[current_point.r][current_point.c] = 1;
        // 判断当前节点是否到达了门
        if (maze[current_point.r][current_point.c] == '#') {
            path_expand[count++] = current_point;
            break;
        }
        // 将该节点移出，并且让最后一个节点填补最小的节点。
        path_expand[count++] = current_point;
        open_set[min_index] = open_set[open_set_count - 1];
        open_set_count--;
        
        for (int j = 0; j < 4; j++) {
            // 记录下一个要访问的节点
            Point next_point = (Point) {current_point.r + dr[j], current_point.c + dc[j]};
            // 1.不越界 2.未访问过 3. 不是墙壁
            if (next_point.r >= 0 && next_point.r < width &&
                next_point.c >= 0 && next_point.c < height &&
                !visited[next_point.r][next_point.c] &&
                maze[next_point.r][next_point.c] != '1') {
                    int next_point_g_cost = current_point_g_cost + 1;
                    if (next_point_g_cost < cost[next_point.r][next_point.c]) {
                        cost[next_point.r][next_point.c] = next_point_g_cost;

                        prev[next_point.r][next_point.c] = current_point;
                        open_set[open_set_count++].p = next_point;
                        // 处理节点代价
                        open_set[open_set_count - 1].h_cost = manhattan(next_point.r, next_point.c, endX, endY);
                        open_set[open_set_count - 1].g_cost = next_point_g_cost;
                        open_set[open_set_count - 1].f_cost = open_set[open_set_count - 1].h_cost + open_set[open_set_count - 1].g_cost;
                    }
                }
        }
    }
    
    // 输出A*拓展的路径
    for (int i = 0; i < count; i++) {
        printf("->(%d,%d)", path_expand[i].r, path_expand[i].c);
    }
    printf("\n");
    // 输出最终A*走的路径
    Point c = (Point) {endX, endY};
    Point reverse_path[width * height];
    Point path[width * height];
    int path_length = 0;
    while (prev[c.r][c.c].r != -1 ) {
        reverse_path[path_length++] = c;
        c = prev[c.r][c.c];

    }
    reverse_path[path_length++] = (Point) {startX, startY};

    for (int i = 0 ; i < path_length; i++) {
        path[i] = reverse_path[path_length - 1 - i];
        printf("->(%d,%d)", path[i].r, path[i].c);
    }

}

int main() {
    int width, height;
    scanf("%d %d\n", &width, &height);
    char **maze = (char **)malloc(width * sizeof(char *));
    for(int i = 0; i < width; i++) {
        maze[i] = (char *)malloc(height * sizeof(char));
        scanf("%s", maze[i]);
    }
    
    int startX = 0, startY = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (maze[i][j] == '*') {
                startX = i;
                startY = j;
            }
        }
    }

    findKey(maze, width, height, startX, startY);

    int endX = 0, endY = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (maze[i][j] == '$') {
                startX = i;
                startY = j;
            }
            if (maze[i][j] == '#') {
                endX = i;
                endY = j;
            }
        }
    }
    findDoor(maze, width, height, startX, startY, endX, endY);
    
    for(int i = 0; i < width; i++) {
        free(maze[i]);
    }
    free(maze);
    return 0;
}