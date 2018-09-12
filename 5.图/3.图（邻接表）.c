// 图（邻接表）
#include <stdio.h>
#include <malloc.h>

#define MAXVEX 100 // 最大顶点数

typedef char VertexType; // 顶点类型
typedef int EdgeType; // 边上的权值类型

// 边表节点
typedef struct EdgeNode {
    int adjvex; // 邻接点域，存储该顶点对应的下标
    EdgeType info; // 用来存储权值（非网图可没有）
    struct EdgeNode *next; // 指向下一个邻接点
} EdgeNode;

// 顶点表节点
typedef struct VertexNode {
    VertexType data; // 顶点域，存储顶点信息
    EdgeNode *firstEdge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

// 邻接表结构
typedef struct {
    AdjList adjList;// 顶点表数组
    int numNodes, numEdges; // 图中当前顶点数，边数
} GraphAdjList;

/**
 * 创建邻接表
 * @param G 邻接表
 */
void CreateALGraph(GraphAdjList *G) {
    int i, j, k; // 用来遍历元素
    EdgeNode *e; // 边表节点

    printf("输入顶点数和边数：\n");
    scanf("%d,%d", &G->numNodes, &G->numEdges);
    getchar(); // 用来抵消回车

    printf("输入%d个顶点的信息：\n", G->numNodes);

    // 读取所有顶点的信息
    for (i = 0; i < G->numNodes; i++) {
        scanf("%c", &G->adjList[i].data); // 读取顶点信息
        getchar(); // 用来抵消回车

        G->adjList[i].firstEdge = NULL; // 将边表置为空表
    }

    // 读取所有边的信息
    for (k = 0; k < G->numEdges; k++) {
        printf("第%d条边：输入边（vi，vj）上的顶点序号：\n", k + 1);
        scanf("%d,%d", &i, &j); // 读取起点、终点序号
        getchar(); // 用来抵消回车

        e = (EdgeNode *) malloc(sizeof(EdgeNode)); // 为边表节点分配存储空间
        e->adjvex = j; // 邻接序号为j
        e->next = G->adjList[i].firstEdge; // 将e的指针指向当前顶点上指向的节点
        G->adjList[i].firstEdge = e; // 将当前顶点的指针指向e

        e = (EdgeNode *) malloc(sizeof(EdgeNode)); // 为边表节点分配存储空间
        e->adjvex = i; // 邻接序号为i
        e->next = G->adjList[j].firstEdge; // 将e的指针指向当前顶点上指向的节点
        G->adjList[j].firstEdge = e; // 将当前顶点的指针指向e
    }
}

/**
 * 打印邻接表
 * @param G 邻接表
 */
void Print(GraphAdjList *G) {
    int i, j; // 用来遍历元素
    EdgeNode *p;

    printf("顶点表的值为：\n");
    // 打印顶点表
    for (i = 0; i < G->numNodes; i++) {
        printf("v%d: %c\n", i, G->adjList[i].data);
    }

    printf("边表的值为：\n");
    for (i = 0; i < G->numNodes; i++) {
        printf("v%d ", i);

        p = G->adjList[i].firstEdge; // p指向顶点i的边表

        while (p) { // 边表未遍历完
            printf("-> %d", p->adjvex); // 打印邻接点
            p = p->next; // p移动到下一个边表节点
        }
        printf("\n");
    }
}

int main() {
    GraphAdjList G; // 邻接表
    CreateALGraph(&G); // 创建邻接表
    Print(&G); // 打印邻接表

    return 0;
}