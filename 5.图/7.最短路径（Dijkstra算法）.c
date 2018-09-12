// 最短路径（Dijkstra算法）
#include <stdio.h>

#define MAXVEX 20 // 最大顶点数
#define INFINITY 65535 // 无穷

typedef int Patharc[MAXVEX]; // 用于存储最短路径前驱结点下标的数组
typedef int ShortPathTable[MAXVEX]; // 用于存储到各点最短路径的权值和

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
 * 最短路径Dijkstra算法
 * 求有向网G的v0顶点到其余顶点v的最短路径P[v]即带权长度D[v]
 * P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和
 * @param G 邻接矩阵（图）
 * @param v0 图的起始顶点
 * @param P 存储最短路径前驱节点下标的数组
 * @param D 存储v0到各点最短路径的权值和的数组
 */
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D) {
    int v, w, k, min; // v、w用来遍历元素，k记录最小权值节点的下标，min记录最小权值
    int final[MAXVEX]; // final[w]=1表示v0至vw的最短路径

    // 初始化数据
    for (v = 0; v < G.numNodes; v++) {
        final[v] = 0; // 全部顶点初始化为位置最短路径状态
        (*D)[v] = G.arc[v0][v]; // 记录与v0有连线的顶点的权值
        (*P)[v] = -1; // 初始化路径数组P为-1
    }

    (*D)[v0] = 0; // 设置v0至v0路径的权值为0
    final[v0] = 1; // v0至v0不需要求路径，设置为1

    // 开始主循环，每次求得v0到某个v顶点的最短路径
    for (v = 1; v < G.numNodes; v++) {
        min = INFINITY; // 记录本次循环距离v0最近的距离

        // 寻找离v0最近的顶点
        for (w = 0; w < G.numNodes; w++) {
            // final[w]为0表示该顶点还没有记录与它最近的顶点
            // final[w]为0，并且该顶点的权值小于无穷
            if (!final[w] && (*D)[w] < min) {
                k = w; // 记录最小权值的下标
                min = (*D)[w]; // 记录最小权值
            }
        }

        // 将目前找到的最接近v0的顶点的下标的位置置为1，表示该顶点已被记录
        final[k] = 1;

        // 修正当前最短路径即距离
        for (w = 0; w < G.numNodes; w++) {
            // 如果经过v顶点的路径比现在这条路径短的话
            if (!final[w] && (min + G.arc[k][w] < (*D)[w])) {
                (*D)[w] = min + G.arc[k][w]; // 修改顶点w距离v0的最短长度
                (*P)[w] = k; // 存储最短路径前驱节点的下标
            }
        }
    }
}

/**
 * 打印最短路径
 * @param G 邻接矩阵（图）
 * @param v0 图的起始顶点
 * @param P 存储最短路径前驱节点下标的数组
 * @param D 存储v0到各点最短路径的权值和的数组
 */
void PrintShortPath(MGraph G, int v0, Patharc P, ShortPathTable D) {
    int i, j; // 用于遍历元素

    printf("存储最短路径前驱结点下标的数组P的值为：\n");
    printf("数组下标：");
    for (i = 0; i < G.numNodes; i++) {
        printf("%2d ", i);
    }
    printf("\n数组的值：");
    for (i = 0; i < G.numNodes; i++) {
        printf("%2d ", P[i]);
    }

    /*
        存储最短路径前驱结点下标的数组P的值为：
        数组下标： 0  1  2  3  4  5  6  7  8
        数组的值：-1 -1  1  4  2  4  3  6  7

        当P[8] = 7时表示，顶点8的前驱结点是顶点7，
        找到顶点7，发现P[7] = 6，表示顶点7的前驱节点是顶点6，
        所以由顶点8到顶点0的最短路径为：
        8 -> 7 -> 6 -> 3 -> 4 ->2 -> 1
        将这个顺序倒过来即可得到顶点0到顶点8的最短路径
     */

    printf("\n\n最短路径倒序如下：\n");
    for (i = 1; i < G.numNodes; i++) {
        printf("v%d - v%d : ", v0, i);
        j = i; // j用于遍历while循环

        while (P[j] != -1) { // P[j] = 1表示该顶点不可通
            printf("%d ", P[j]);
            j = P[j]; // 获取与该顶点距离最近的顶点下标
        }
        printf("\n");
    }

    printf("\n原点v%d到各顶点的最短路径长度为：\n", v0);
    for (i = 1; i < G.numNodes; i++) {
        // D数组中存v0到各顶点的最短路径和
        printf("v%d - v%d : %d \n", G.vexs[0], G.vexs[i], D[i]);
    }
}

int main() {
    int v0; // 图的起始顶点下标
    MGraph G; // 邻接矩阵（图）
    Patharc P; // 用于存储最短路径前驱结点下标的数组
    ShortPathTable D; // 用于存储到各点最短路径的权值和

    v0 = 0; // 将0下标的顶点设置为图的起点

    CreateMGraph(&G); // 初始化邻接矩阵（图）
    ShortestPath_Dijkstra(G, v0, &P, &D); // 对图求最短路径
    PrintShortPath(G, v0, P, D); // 打印最短路径

    return 0;
}