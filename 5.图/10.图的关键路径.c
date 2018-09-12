// 图的关键路径算法
#include <stdio.h>
#include <malloc.h>

#define OK 1 // 执行成功
#define ERROR 0 // 执行失败

#define MAXVEX 14 // 最大顶点数
#define INFINITY 65535 // 无穷

typedef int Status; // 执行状态

int *etv, *ltv; // 事件最早发生时间和事件最迟发生时间数组，全局变量
int *stack2; // 用于存储拓扑序列的栈
int top2; // 用于stack2的指针

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

    G->numEdges = 13; // 设置边数
    G->numNodes = 10; // 设置顶点数

    // 初始化图的顶点表
    for (i = 0; i < G->numNodes; i++) {
        G->vexs[i] = i;
    }

    // 初始化图的边表
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            if (i == j) { // 如果是对角线顶点所在边
                G->arc[i][j] = 0; // 设置边的权值为0
            } else { // 其他边
                G->arc[i][j] = INFINITY; // 设置权值为无穷
            }
        }
    }

    // 设置特定边的权值
    G->arc[0][1]=3;
    G->arc[0][2]=4;

    G->arc[1][3]=5;
    G->arc[1][4]=6;

    G->arc[2][3]=8;
    G->arc[2][5]=7;

    G->arc[3][4]=3;

    G->arc[4][6]=9;
    G->arc[4][7]=4;

    G->arc[5][7]=6;
    G->arc[6][9]=2;
    G->arc[7][8]=5;
    G->arc[8][9]=3;
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
            // 如果该边有路径可通
            if (G.arc[i][j] != 0 && G.arc[i][j] < INFINITY) {
                e = (EdgeNode *) malloc(sizeof(EdgeNode)); // 为边表节点分配存储空间
                e->adjvex = j; // 设置邻接序号为j
                e->weight = G.arc[i][j]; // 设置节点的权值
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

    top2 = 0; // 设置stack2的栈顶指针为0

    etv = (int *) malloc(GL->numNodes * sizeof(int)); // 事件最早发生时间数组
    for (i = 0; i < GL->numNodes; i++) {
        etv[i] = 0; // 初始化事件最早发生时间都为0
    }

    stack2 = (int *) malloc(GL->numNodes * sizeof(int)); // 初始化拓扑序列栈

    printf("拓扑排序：\n");
    // 未把所有入度为0的顶点出栈
    while (top != 0) {
        gettop = stack[top--]; // 获取入度为0的栈的栈顶元素
        printf("%d -> ", GL->adjList[gettop].data); // 打印该元素的顶点信息
        count++; // 输入顶点个数加1

        stack2[++top2] = gettop; // 将弹出的顶点序号压入拓扑序列的栈

        // 遍历该顶点的边表
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            k = e->adjvex; // 获取下个顶点（边终点所指向的节点）的下标

            // 将边终点所指向的节点的入度减1，如果该顶点入读为0，将顶点入栈
            if (!(--GL->adjList[k].in)) {
                stack[++top] = k; // 将顶点入栈
            }

            // 求各顶点事件的最早发生时间etv的值
            // 如果边起点的值加上边上的权值大于边终点的值
            if (etv[gettop] + e->weight > etv[k]) {
                // 设置边终点的值为边起点的值加上边上的权值
                etv[k] = etv[gettop] + e->weight;
                // 如顶点1和顶点2都到达顶点3，
                // 那么顶点3的最早开始时间为max（顶点1 + 边上的权值，顶点2 + 边上的权值）
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

/**
 * 关键路径算法
 * @param GL 邻接表
 */
void CriticalPath(GraphAdjList GL) {
    EdgeNode *e; // 边表节点
    int i, j, k ;  // i和j用来遍历元素，k用来获取边表节点的下标
    int gettop;  // gettop用来获取拓扑序列栈的栈顶元素的下标
    int ete, lte; // 记录活动最早发生时间，活动最迟发生时间

    TopologicalSort(GL); // 求拓扑序列，计算数组etv和stack2的值

    ltv = (int *) malloc(GL->numNodes * sizeof(int)); // 为事件最迟发生时间数组分配存储空间
    for (i = 0; i < GL->numNodes; i++) { // 初始化事件最迟发生时间数组
        ltv[i] = etv[GL->numNodes - 1]; // 设置值为事件最早发生时间数组的结束时间
    }

    // 打印事件最早发生时间数组
    printf("etv:\n");
    for (i = 0; i < GL->numNodes; i++) {
        printf("%d -> ", etv[i]);
    }
    printf("\n");

    // 拓扑序列的栈未出栈完
    while (top2 != 0) {
        gettop = stack2[top2--]; // 获取拓扑序列栈的栈顶元素

        // 遍历与该顶点相连的边
        // 求各顶点事件的最迟发生时间ltv的值
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            k = e->adjvex; // 获取节点下标
            // 如果边终点的值减去边的权值小于边起点的值
            // ltv[9] - 3 < ltv[8] = 24，ltv[8] = 27，min(27, 24) = 24
            if (ltv[k] - e->weight < ltv[gettop]) {
                // 设置边起点的值为边终点的值减去边的权值
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }

    // 打印事件最迟发生时间数组
    printf("ltv:\n");
    for (i = 0; i < GL->numNodes; i++) {
        printf("%d -> ", ltv[i]);
    }
    printf("\n");

    printf("各顶点间路径长度：\n");
    for (j = 0; j < GL->numNodes; j++) {
        for (e = GL->adjList[j].firstEdge; e; e = e->next) {
            k = e->adjvex; // 获取当前顶点的下标
            ete = etv[j];  // 活动最早发生时间
            lte = ltv[k] - e->weight; // 活动最迟发生时间

            // 活动最早发生时间等于最迟发生时间，两者相等表示在关键路径上
            if (ete == lte) {
                printf("<v%d - v%d> length: %d \n", GL->adjList[j].data, GL->adjList[k].data, e->weight);
            }
        }
    }
}

int main() {
    MGraph G; // 邻接矩阵
    GraphAdjList GL; // 邻接表

    CreateMGraph(&G); // 创建邻接矩阵
    CreateALGraph(G, &GL); // 使用邻接矩阵创建邻接表
    CriticalPath(GL); // 求图的关键路径

    return 0;
}