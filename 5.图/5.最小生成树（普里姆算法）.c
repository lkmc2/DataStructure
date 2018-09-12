// 最小生成树（普里姆算法）
#include <stdio.h>

#define MAXVEX 100 // 最大顶点数
#define INFINITY 65535 // 无穷

typedef int EdgeType; // 边上的权值类型

// 邻接矩阵结构
typedef struct {
    EdgeType arc[MAXVEX][MAXVEX]; // 边表
    int numNodes, numEdges; // 图中当前的顶点数，边数
}MGraph;


/**
 * 生成邻接矩阵
 * @param G 邻接矩阵
 */
void CreateMGraph(MGraph *G) {
    int i, j; // 用于遍历元素

    G->numEdges = 15; // 设置有15条边
    G->numNodes = 9; // 设置有9个顶点

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
    G->arc[0][1] = 10;
    G->arc[0][5] = 11;

    G->arc[1][2] = 18;
    G->arc[1][8] = 12;
    G->arc[1][6] = 16;

    G->arc[2][3] = 22;
    G->arc[2][8] = 21;

    G->arc[3][4] = 20;
    G->arc[3][7] = 16;
    G->arc[3][6] = 24;
    G->arc[3][8] = 21;

    G->arc[4][5] = 26;
    G->arc[4][7] = 7;

    G->arc[5][6] = 17;

    G->arc[6][7] = 19;

    // 设置对称边的权
    for (i = 0; i < G->numNodes; i++) {
        for (j = i; j < G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/**
 * 打印下标
 */
void PrintIndex() {
    printf(" index: ");
    for (int i = 0; i < 9; ++i) {
        printf("\t%d ", i);
    }
    printf("\n");
}

/**
 * 打印lowcost数组
 * @param lowcost 存备用最小权值的数组
 */
void PrintLowcost(int lowcost[]) {
    printf("lowcost: ");
    for (int i = 0; i < 9; ++i) {
        printf("\t%d ", lowcost[i]);
    }
    printf("\n");
}

/**
 * 打印adjvex数组
 * @param adjvex 存边对应顶点的数组
 */
void PrintAdjvex(int adjvex[]) {
    printf("adjvex: ");
    for (int i = 0; i < 9; ++i) {
        printf("\t%d ", adjvex[i]);
    }
    printf("\n");
}

/**
 * Prim算法生成最小生成树
 * @param G 最小生成树
 */
void MiniSpanTree_Prim(MGraph G) {
    int min, k, i, j; // min存储最小值，k用来存储最小值下标，i、j用于遍历元素
    int adjvex[MAXVEX]; // 存储顶点下标
    int lowcost[MAXVEX]; // 保存顶点间边的权值

    // 初始化第一个权值为0，即将v0加入生成树，lowcost的值为0，表示改下标的顶点已加入生成树
    lowcost[0] = 0;
    adjvex[0] = 0; // 初始化第一个顶点下标为0

    // 对下标为0以外的顶点进行遍历
    for (i = 1; i < G.numNodes; i++) {
        lowcost[i] = G.arc[0][i]; // 将与v0顶点有边的权值存入数组
        adjvex[i] = 0; // 顶点初始化都为v0的下标
    }

    // 对下标为0以外的顶点进行遍历
    for (i = 1; i < G.numNodes; i++) {
        min = INFINITY; // 初始化本次循环的边最小值为无穷

        j = 1; // 用来遍历v0以外的顶点
        k = 0; // 记录最小边的下标

        // 循环全部顶点
        while (j < G.numNodes) {
            // 权值不为0（权值为0表示已加入生成树）并且小于min
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j]; // 让当前权值成为最小值
                k = j; // 使用k记录当前最小值的下标
            }
            j++; // j向后移动
        }

        PrintIndex(); // 打印下标
        PrintAdjvex(adjvex); // 打印adjvex数组
        PrintLowcost(lowcost); // 打印lowcost数组

        printf("最小权为：%d，边为：(%d, %d)\n\n", min, adjvex[k], k); // 打印与顶点相连的边中权值最小的边
        lowcost[k] = 0; // 设置当前顶点的权值为0，表示该顶点已完成任务

        // 对下标为0以外的顶点进行遍历
        for (j = 1; j < G.numNodes; j++) {
            // 对本次有最小权值的顶点k，把与k相连的边加入数组中
            // 值不为0（权值为0表示已加入生成树）并且小于对应列的lowcost
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
                lowcost[j] = G.arc[k][j]; // 将较小的权值存入lowcost的相应位置
                adjvex[j] = k; // 因为与顶点k相连，将下标为k的顶点存入adjvex
            }
        }

    }
}

int main() {
    MGraph G; // 邻接矩阵
    CreateMGraph(&G); // 创建邻接矩阵
    MiniSpanTree_Prim(G); // Prim算法生成最小生成树

    return 0;
}