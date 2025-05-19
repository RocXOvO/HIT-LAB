
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];

typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int* node_degree);
double clusteringCoefficient(Graph g);
int Diameter(Graph g);
int Radius(Graph g);
int dijkstra(Graph g, int start, int end, int* path);
void printPath(int d, int* diameter_path, Graph g);


/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int**)malloc(sizeof(int*) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int*)malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype*)malloc(sizeof(vextype) * g.N);
    return g;
}


/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *diameter_path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s->", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
}


/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    // BFS
    if (g.N == 0 || g.N == 1) {
        return 1;
    }
    // 初始化
    int *visited = malloc(sizeof(int) * g.N);
    // 0 表示未访问 1表示已经访问过了
    int visited_num = 0;
    for (int i = 0; i < g.N; i++) {
        visited[i] = 0;
    }

    // 构建一个队列
    int *queue = malloc(sizeof(int) * g.N);
    int head = 0;
    int tail = 0;
    // 随便选一个节点作为开始节点
    int start_node = 0;
    queue[tail++] = start_node;
    visited[start_node] = 1;
    visited_num = 1;
    while (head < tail) {
        int visited_node = queue[head++];
        for (int i = 0; i < g.N; i++) {
            if (g.matrix[visited_node][i] != max_dis && g.matrix[visited_node][i] != 0 && visited[i] == 0) {
                queue[tail++] = i;
                visited[i] = 1;
                visited_num++;
            }
        }
    }
    free(visited);
    free(queue);
    return visited_num == g.N;
}


/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    for (int i = 0; i < g.N; i++) {
        node_degree[i] = 0;
    }
    for (int i = 0; i < g.N; i++) {
        for (int j = i + 1; j < g.N; j++) {
            if (g.matrix[i][j] != max_dis && g.matrix[i][j] != 0) {
                node_degree[i]++;
                node_degree[j]++;
            }
        }
    }

}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    double total_clusting = 0;
    for (int i = 0; i < g.N; i++) {
        // 寻找每个节点的neighbor
        double clusting = 0;
        int *neighbor = malloc(sizeof(int) * g.N);
        int k = 0;
        for (int j = 0; j < g.N; j++) {
            if (j != i && g.matrix[i][j] != max_dis && g.matrix[i][j] != 0) neighbor[k++] = j; // 当前这个节点的相邻节点，k表示当前节点有多少个，数列中存储的邻居是哪个。
        }

        if (k < 2) {
            free(neighbor);
            continue;
        }
        int links_cnt = 0;
        // 循环neighbor，看neighbor会不会有连通，如果连通，则links_cnt++
        for (int node1 = 0; node1 < k; node1++) {
            for (int node2 = node1 + 1; node2 < k; node2++) {
                if (g.matrix[neighbor[node1]][neighbor[node2]] != max_dis && g.matrix[neighbor[node1]][neighbor[node2]] != 0) {
                    links_cnt++;
                }
            }
        }
        // 计算单个节点的聚类值
        clusting = (double)links_cnt / (double) (k * (k - 1) / 2);
        total_clusting += clusting; 
    }
    return total_clusting / g.N;
}


/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    if (start < 0 || start > g.N - 1 || end < 0 || end > g.N - 1) {
        printf("start或者end索引越界\n");
        for (int i = 0; i < g.N; i++)path[i] = -1;
        return max_dis;
    }
    int dist[g.N];
    int prev[g.N];
    int visited[g.N];
    // 初始化
    for (int i = 0; i < g.N; i++) {
        dist[i] = max_dis;
        prev[i] = -1; 
        visited[i] = 0;
        path[i] = -1;
    }
    dist[start] = 0;
    // i表示的是迭代次数。只要迭代g.N - 1次就可以了
    // 题目要求迭代到end处既可
    for (int cnt = 0; cnt < g.N - 1; cnt++) {
        int u = -1;// 迭代的节点
        int min_dist = max_dis;
        //选取当前最小的dist并且没有被访问过。
        for (int j = 0; j < g.N;j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }

        }
        // 如果没有节点则返回max_dis表示不能到达。
        if (u == -1 || min_dist == max_dis) {
            return max_dis;
        }

        visited[u] = 1; //表示该节点已经访问。

        // 如果已经迭代到end处，那么直接就退出循环，u纳入集合中后，即为最短路径了。
        if (u == end) {
            break;
        }

        // 从u出发 更新一些节点的dist值
        for (int i = 0; i < g.N; i++) {
            if (!visited[i] && g.matrix[u][i] != 0 && g.matrix[u][i] != max_dis && dist[i] > dist[u] + g.matrix[u][i]) {
                dist[i] = dist[u] + g.matrix[u][i];
                prev[i] = u;
            }
        }
    }
    // 判断end是否可达，如果不可达，则不进入路径构建，直接返回
    if (dist[end] == max_dis) {
        return max_dis;
    }

    // 路径构建

    int temp_path[g.N]; // 记录反向路径，后续变更
    int current_node = end;
    int count = 1;
    // 迭代找路径，直到最后prev是-1
    for (int i = 0; i < g.N; i++) {
        if (prev[current_node] == -1) {
            temp_path[i] = current_node;
            break;
        }
        temp_path[i] = current_node;
        current_node = prev[current_node];
        count++;
    }

    // 反转temp_path既可得到正确的路径

    for (int i = 0, j = count - 1; i < count && j >= 0; i++ ,j--) {
        path[i] = temp_path[j];
    }
    return dist[end];
}

/**
 * Floyd多源最短路径计算。
 */
void Floyd(Graph g) {
    int dist[g.N][g.N];

}


/**
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
int Diameter(Graph g) {
    //TODO
}


/**
 * 计算图的半径
 * @param g 图
 * @return 半径长度
 */
int Radius(Graph g) {
    //TODO
}


int main() {
    int node_num;
    int edge_num;

    scanf("%d %d", &node_num, &edge_num);

    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }

    for (int i = 0; i < edge_num; i++) {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }
    printf("connected: %d\n", isConnected(g));

    int *degree = (int *)malloc(sizeof(int) * g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for(int i=0; i<g.N; i++)
    {
        printf("node%s:%d,", g.vertex[i], degree[i]);
    }
    printf("\n");
    double c = clusteringCoefficient(g);
    printf("clustering coefficient:%f\n", c);

    if (isConnected(g))
    {
        int* short_path = (int*)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 1, 3, short_path);
        printf("the minimum fare between 1 and 3: %d\n", dis);
        printPath(dis, short_path, g);
        free(short_path);
        int d = Diameter(g);
        printf("diameter:%d\n", d);

        int r = Radius(g);
        printf("radius:%d\n", r);
    }

    return 0;
}