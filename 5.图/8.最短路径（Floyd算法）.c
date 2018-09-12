// 最短路径（Floyd算法）
#include <stdio.h>

#define MAXVEX 20 // 最大顶点数
#define INFINITY 65535 // 无穷

typedef int Patharc[MAXVEX][MAXVEX]; // 用于存储起点v到其他顶点的最短路径
typedef int ShortPathTable[MAXVEX][MAXVEX]; // 用于存储起点v到其他顶点的带权长度

// 邻接矩阵结构
typedef struct {
    int vexs[MAXVEX]; // 顶点表
    int arc[MAXVEX][MAXVEX]; // 边表
    int numNodes, numEdges; // 图中当前的顶点数，边数
} MGraph;

/**
 * 生成邻接矩阵（图）
 * @param G 邻接矩阵（图）
 */
void CreateMGraph(MGraph *G) {
    int i, j; // 用于遍历元素

    G->numEdges = 16; // 设置有16条边
    G->numNodes = 9; // 设置有9个顶点

    // 初始化图的顶点
    for (i = 0; i < G->numNodes; i++) {
        G->vexs[i] = i;
    }

    // 初始化图的边
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            if (i == j) { // 对角线边的值设置为0
                G->arc[i][j] = 0;
            } else { // 其他位置的边设置为无穷
                G->arc[i][j] = G->arc[j][i] = INFINITY;
            }
        }
    }

    // 设置特定边的权
    G->arc[0][1]=1;
    G->arc[0][2]=5;

    G->arc[1][2]=3;
    G->arc[1][3]=7;
    G->arc[1][4]=5;

    G->arc[2][4]=1;
    G->arc[2][5]=7;

    G->arc[3][4]=2;
    G->arc[3][6]=3;

    G->arc[4][5]=3;
    G->arc[4][6]=6;
    G->arc[4][7]=9;

    G->arc[5][7]=5;

    G->arc[6][7]=2;
    G->arc[6][8]=7;

    G->arc[7][8]=4;

    // 设置对称边的权
    for (i = 0; i < G->numNodes; i++) {
        for (j = i; j < G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/**
 * 最短路径Floyd算法
 * @param G 邻接矩阵（图）
 * @param P 存存储起点v到其他顶点的最短路径的数组
 * @param D 存存储起点v到其他顶点的带权长度的数组
 */
void ShortestPath_Floyd(MGraph G, Patharc *P, ShortPathTable *D) {
    int v, w, k; // 用来遍历元素

    // 初始化D和P
    for (v = 0; v < G.numNodes; v++) {
        for (w = 0; w < G.numNodes; w++) {
            (*D)[v][w] = G.arc[v][w]; // 存储对应边的权值
            (*P)[v][w] = w; // 设置该列的值为该列的下标
        }
    }

    for (k = 0; k < G.numNodes; k++) {
        for (v = 0; v < G.numNodes; v++) {
            for (w = 0; w < G.numNodes; w++) {
                // 如果下标下标为k的顶点的路径比原两点间路径更短
                // 如果D[1][3] > D[1][2] + D[2][3]
                if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
                    // 将当前两点间权值设置为通过中间点k的路径的权值
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    // 路径设置为经过下标为k的顶点
                    (*P)[v][w] = (*P)[v][k];
                }
            }
        }
    }
}

/**
 * 打印最短路径
 * @param G 邻接矩阵（图）
 * @param P 存储最短路径前驱节点下标的数组
 * @param D 存储v0到各点最短路径的权值和的数组
 */
void PrintShortPath(MGraph G, Patharc P, ShortPathTable D) {
    int v, w, k; // 用于遍历元素

    printf("各顶点间最短路径如下：\n");
    for (v = 0; v < G.numNodes; v++) {
        for (w = v + 1; w < G.numNodes; w++) {
            printf("v%d-v%d weight: %2d ", v, w, D[v][w]);

            k = P[v][w]; // 获取顶点v到w的权值
            printf(" path: %d", v); // 打印起点

            while (k != w) { // 循环未到达末端顶点
                printf(" -> %d", k); // 打印路径顶点
                k = P[k][w]; // 获取下一个路径顶点的下标
            }
            printf(" -> %d\n", w); // 打印终点
        }
        printf("\n");
    }
}

int main() {
    MGraph G; // 邻接矩阵（图）
    Patharc P; // 存储起点v到其他顶点的最短路径
    ShortPathTable D; // 存储起点v到其他顶点的带权长度

    CreateMGraph(&G); // 初始化邻接矩阵（图）
    ShortestPath_Floyd(G, &P, &D); // 对图求最短路径
    PrintShortPath(G, P, D); // 打印最短路径

    return 0;
}