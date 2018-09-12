// 图（邻接矩阵）
#include <stdio.h>

#define MAXVEX 100 // 最大顶点数
#define INFINITY 65535 // 无穷

typedef char VertexType; // 顶点元素类型
typedef int EdgeType; // 边上权值的类型

// 邻接矩阵结构（无向图）
typedef struct {
    VertexType vexs[MAXVEX]; // 顶点表
    EdgeType arc[MAXVEX][MAXVEX]; // 边表
    int numNodes, numEdges; // 图的顶点数、边数
} MGraph;

/**
 * 创建无向图的临接矩阵表示
 * @param G 邻接矩阵（无向图）
 */
void CreateMGraph(MGraph *G) {
    int i, j, k, w;

    printf("请输入顶点数和边数：\n");
    scanf("%d,%d", &G->numNodes, &G->numEdges); // 读取顶点数和边数
    getchar(); // 用于抵消回车键

    printf("请输入%d个顶点的值：\n", G->numNodes);
    // 依次输入顶点表信息
    for (i = 0; i < G->numNodes; i++) {
        scanf("%c", &G->vexs[i]); // 读取用户输入的值到顶点表中
        getchar();  // 用于抵消回车键
    }

    printf("请输入%d条边的值：\n", G->numEdges);
    // 初始化边表
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = INFINITY; // 设置边表中所有的值为无穷
        }
    }

    // 依次输入边表信息
    for (k = 0; k < G->numEdges; k++) {
        printf("输入第%d条边：(vi,vj)=w，下标i，下标j和权值w\n", k + 1);
        scanf("%d,%d,%d", &i, &j, &w); // 输入边（vi，vj）上的权
        getchar(); // 用于抵消回车键

        G->arc[i][j] = w; // 设置边（vi，vj）上的权值
        G->arc[j][i] = G->arc[i][j]; // 因为是无向图，矩阵对称，边（vj，vi）等于边（vi，vj）
    }
}

/**
 * 打印无向图
 * @param G 邻接矩阵（无向图）
 */
void Print(MGraph *G) {
    int i, j; // 用来遍历元素

    printf("顶点表的值为：\n");
    // 打印顶点表
    for (i = 0; i < G->numNodes; i++) {
        printf("v%d: %c\n", i, G->vexs[i]);
    }
    printf("\n");

    printf("边表的值为：\n");
    // 打印边表
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            if (G->arc[i][j] != INFINITY) { // 元素不为无穷，表示该边有值
                printf("<v%d, v%d>: %d\n", i, j, G->arc[i][j]);
            }
        }
    }
}

int main() {
    MGraph G; // 邻接矩阵
    CreateMGraph(&G); // 创建邻接矩阵（无向图）
    Print(&G); // 打印邻接矩阵（无向图）

    return 0;
}
