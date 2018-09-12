// 图的拓扑排序算法
#include <stdio.h>
#include <malloc.h>

#define MAXEDGE 20 // 最大边数
#define MAXVEX 14 // 最大顶点数

#define OK 1 // 执行成功
#define ERROR 0 // 执行失败

typedef int Status; // 执行状态

// 邻接矩阵结构
typedef struct {
    int vexs[MAXVEX]; // 顶点表
    int arc[MAXVEX][MAXVEX]; // 边表
    int numNodes, numEdges; // 图中当前的顶点数，边数
} MGraph;

/**************** 用到的邻接表结构 ****************/

// 边表节点
typedef struct EdgeNode {
    int adjvex; // 邻接点域，存储该顶点对应的下标
    int weight; // 用来存储权值（非网图可没有）
    struct EdgeNode *next; // 指向下一个邻接点
} EdgeNode;

// 顶点表节点
typedef struct VertexNode {
    int in; // 顶点入度
    int data; // 顶点域，存储顶点信息
    EdgeNode *firstEdge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

// 邻接表结构
typedef struct {
    AdjList adjList;// 顶点表数组
    int numNodes, numEdges; // 图中当前顶点数，边数
} graphAdjList, *GraphAdjList;

/*************************************************/

/**
 * 生成邻接矩阵（图）
 * @param G 邻接矩阵（图）
 */
void CreateMGraph(MGraph *G) {
    int i, j; // 用于遍历元素

    G->numEdges = MAXEDGE; // 设置边数
    G->numNodes = MAXVEX; // 设置顶点数

    // 初始化图的顶点表
    for (i = 0; i < G->numNodes; i++) {
        G->vexs[i] = i;
    }

    // 初始化图的边表
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = 0; // 设置所有边的默认值为0
        }
    }

    // 设置特定边的权（值为1表示该位置有边）
    G->arc[0][4] = 1;
    G->arc[0][5] = 1;
    G->arc[0][11] = 1;

    G->arc[1][2] = 1;
    G->arc[1][4] = 1;
    G->arc[1][8] = 1;

    G->arc[2][5] = 1;
    G->arc[2][6] = 1;
    G->arc[2][9] = 1;

    G->arc[3][2] = 1;
    G->arc[3][13] = 1;

    G->arc[4][7] = 1;

    G->arc[5][8] = 1;
    G->arc[5][12] = 1;

    G->arc[6][5] = 1;

    G->arc[8][7] = 1;

    G->arc[9][10] = 1;
    G->arc[9][11] = 1;

    G->arc[10][13] = 1;

    G->arc[12][9] = 1;
}

/**
 * 使用邻接矩阵生成邻接表
 * @param G 邻接矩阵
 * @param GL 邻接表
 */
void CreateALGraph(MGraph G, GraphAdjList *GL) {
    int i, j; // 用于遍历元素
    EdgeNode *e; // 边表节点

    *GL = (GraphAdjList) malloc(sizeof(graphAdjList)); // 为邻接表表分配存储空间

    (*GL)->numNodes = G.numNodes; // 设置邻接表的顶点数
    (*GL)->numEdges = G.numEdges; // 设置邻接表的边数

    // 建立顶点表
    for (i = 0; i < G.numNodes; i++) {
        (*GL)->adjList[i].in = 0; // 设置下标为i位置的顶点入读为0
        (*GL)->adjList[i].data = G.vexs[i]; // 存入该顶点的权值
        (*GL)->adjList[i].firstEdge = NULL; // 设置顶点对应的边表为空
    }

    // 建立边表
    for (i = 0; i < G.numNodes; i++) {
        for (j = 0; j < G.numNodes; j++) {
            if (G.arc[i][j] == 1) {
                e = (EdgeNode *) malloc(sizeof(EdgeNode)); // 为边表节点分配存储空间
                e->adjvex = j; // 设置邻接序号为j
                e->next = (*GL)->adjList[i].firstEdge; // 新节点指针指向边表的头节点
                (*GL)->adjList[i].firstEdge = e; // 让新节点成为边表的头节点
                (*GL)->adjList[j].in++; // 边终点所指向的节点入度加1
            }
        }
    }
}

/**
 * 拓扑排序
 * 若邻接表无回路，则输出拓扑排序序列并返回OK，若有回路则返回ERROR
 * @param GL 邻接表
 * @return 执行状态
 */
Status TopologicalSort(GraphAdjList GL) {
    EdgeNode *e; // 边表节点
    int i, k, gettop; // i用于遍历元素，k用来获取顶点下标，gettop用来获取栈顶元素下标
    int top = 0; // 用于栈指针下标
    int count = 0; // 用于统计输出顶点的个数
    int *stack; // 存储入度为0的顶点的栈

    stack = (int *) malloc(GL->numNodes * sizeof(int)); // 为栈分配存储空间

    // 将所有入度为0的顶点入栈
    for (i = 0; i < GL->numNodes; i++) {
        if (GL->adjList[i].in == 0) { // 顶点入度为0
            stack[++top] = i; // 将该节点入栈
        }
    }

    // 未把所有入度为0的顶点出栈
    while (top != 0) {
        gettop = stack[top--]; // 获取入度为0的栈的栈顶元素
        printf("%d -> ", GL->adjList[gettop].data); // 打印该元素的顶点信息
        count++; // 输入顶点个数加1

        // 遍历该顶点的边表
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            k = e->adjvex; // 获取下个顶点（边终点所指向的节点）的下标

            // 将边终点所指向的节点的入度减1，如果该顶点入读为0，将顶点入栈
            if (!(--GL->adjList[k].in)) {
                stack[++top] = k; // 将顶点入栈
            }
        }
    }
    printf("\n");

    // 输出的顶点数小于邻接表的顶点数，邻接表中有回路，拓扑排序失败
    if (count < GL->numNodes) {
        return ERROR;
    } else { // 邻接表中无回路，拓扑排序成功
        return OK;
    }
}

int main() {
    MGraph G; // 邻接矩阵
    GraphAdjList GL; // 邻接表
    Status status; // 执行状态

    CreateMGraph(&G); // 创建邻接矩阵
    CreateALGraph(G, &GL); // 使用邻接矩阵创建邻接表

    status = TopologicalSort(GL); // 将邻接表进行拓扑排序，获取执行状态
    printf("status: %s", status == OK ? "执行成功" : "执行失败");

    return 0;
}