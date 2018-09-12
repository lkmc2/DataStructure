// 邻接表的深度和广度优先遍历
#include <stdio.h>
#include <malloc.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

#define MAXSIZE 9 // 队列存储空间初始分配量
#define MAXVEX 100 // 最大顶点数

typedef int Status; // 执行状态（OK、ERROR）
typedef int Boolean; // 布尔值（TRUE、FALSE）

typedef char VertexType; // 顶点类型
typedef int EdgeType; // 边上的权值类型

/**************** 用到的邻接矩阵结构 ****************/

// 邻接矩阵结构
typedef struct {
    VertexType vexs[MAXVEX]; // 顶点表
    EdgeType arc[MAXVEX][MAXVEX]; // 边表
    int numNodes, numEdges; // 图中当前的顶点数，边数
}MGraph;

/**************** 用到的邻接表结构 ****************/

// 边表节点
typedef struct EdgeNode {
    int adjvex; // 邻接点域，存储该顶点对应的下标
    EdgeType info; // 用来存储权值（非网图可没有）
    struct EdgeNode *next; // 指向下一个邻接点
} EdgeNode;

// 顶点表节点
typedef struct VertexNode {
    int in; // 顶点入度
    VertexType data; // 顶点域，存储顶点信息
    EdgeNode *firstEdge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

// 邻接表结构
typedef struct {
    AdjList adjList;// 顶点表数组
    int numNodes, numEdges; // 图中当前顶点数，边数
} graphAdjList, *GraphAdjList;

/************** 用到的队列结构与函数 **************/

// 循环队列顺序存储结构
typedef struct {
    int data[MAXSIZE]; // 用于存值的数组
    int front; // 头指针
    int rear; // 尾指针，若队列不空，指向队尾元素的下一个位置
} Queue;

/**
 * 初始化一个空队列
 * @param Q 队列
 * @return 执行状态
 */
Status InitQueue(Queue *Q) {
    Q->front = Q->rear=  0; // 队头和队尾指针都指向0
    return OK;
}

/**
 * 判断队列是否为空
 * @param Q 队列
 * @return 队列是否为空
 */
Boolean QueueEmpty(Queue Q) {
    if (Q.front == Q.rear) { // 队头等于队尾指针，队列为空
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 将元素e插入队列Q的队尾
 * @param Q 队列
 * @param e 插入的元素
 * @return 执行状态
 */
Status EnQueue(Queue *Q, int e) {
    // 队列已满，插入失败
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return ERROR;
    }

    // 将元素e插入队尾
    Q->data[Q->rear] = e;

    // 设置队尾指针指向下一个位置，若到最后则转向头部
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

/**
 * 队头元素出队，用e返回其值
 * @param Q 队列
 * @param e 队头元素的值
 * @return 执行状态
 */
Status DeQueue(Queue *Q, int *e) {
    // 对头指针等于对尾指针，此时队列为空，出队失败
    if (Q->front == Q->rear) {
        return ERROR;
    }

    // 将队头元素的值赋给元素e
    *e = Q->data[Q->front];

    // 设置队头指针指向下一个位置，若到最后则转向头部
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

/*************************************************/

/**
 * 生成邻接矩阵
 * @param G 邻接矩阵
 */
void CreateMGraph(MGraph *G) {
    int i, j; // 用于遍历元素

    G->numEdges = 15; // 设置有15条边
    G->numNodes = 9; // 设置有9个顶点

    // 读入顶点信息，建立顶点表
    G->vexs[0] = 'A';
    G->vexs[1] = 'B';
    G->vexs[2] = 'C';
    G->vexs[3] = 'D';
    G->vexs[4] = 'E';
    G->vexs[5] = 'F';
    G->vexs[6] = 'G';
    G->vexs[7] = 'H';
    G->vexs[8] = 'I';

    // 初始化图的边
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = 0; // 设置所有边的值都为0
        }
    }

    // 设置特定边（如果arc[i][j] = 1，代表顶点i到顶点j有边相连）
    G->arc[0][1] = 1;
    G->arc[0][5] = 1;

    G->arc[1][2] = 1;
    G->arc[1][8] = 1;
    G->arc[1][6] = 1;

    G->arc[2][3] = 1;
    G->arc[2][8] = 1;

    G->arc[3][4] = 1;
    G->arc[3][7] = 1;
    G->arc[3][6] = 1;
    G->arc[3][8] = 1;

    G->arc[4][5] = 1;
    G->arc[4][7] = 1;

    G->arc[5][6] = 1;

    G->arc[6][7] = 1;

    // 设置对称边
    for (i = 0; i < G->numNodes; i++) {
        for (j = i; j < G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/**
 * 利用邻接矩阵G生成邻接链表GL
 * @param G 邻接矩阵
 * @param GL 邻接链表
 */
void CreateALGraph(MGraph G, GraphAdjList *GL) {
    int i, j; // 用于遍历元素
    EdgeNode *e; // 边表的节点

    *GL = (GraphAdjList)malloc(sizeof(graphAdjList)); // 为邻接表分配存储空间

    (*GL)->numNodes = G.numNodes; // 设置邻接表的顶点数
    (*GL)->numEdges = G.numEdges; // 设置连接表的边数

    // 设置邻接表中顶点表信息
    for (i = 0; i < G.numNodes; i++) {
        (*GL)->adjList[i].in = 0; // 设置顶点入度
        (*GL)->adjList[i].data = G.vexs[i]; // 设置顶点的值
        (*GL)->adjList[i].firstEdge = NULL; // 将边表置为空表
    }

    // 设置邻接表中边表信息
    for (i = 0; i <G.numNodes; i++) {
        for (j = 0;j < G.numNodes; j++) {
            if (G.arc[i][j] == 1) {
                e = (EdgeNode *) malloc(sizeof(EdgeNode)); // 为边表的节点分配存储空间
                e->adjvex = j; // 设置邻接序号为j
                e->next = (*GL)->adjList[i].firstEdge; // 将e的指针指向当前顶点上指向的节点
                (*GL)->adjList[i].firstEdge = e; // 将当前顶点的指针指向e
            }
        }
    }
}

// 访问标志的数组
Boolean visited[MAXVEX];

/**
 * 邻接表的深度优先递归算法
 * @param GL 邻接表
 * @param i 顶点下标
 */
void DFS(GraphAdjList GL, int i) {
    EdgeNode *p; // 边表节点
    visited[i] = TRUE; // 设置当前下标节点已被访问

    printf("%c ", GL->adjList[i].data); // 打印顶点值

    p = GL->adjList[i].firstEdge; // p指向当前顶点的边表第一个节点

    while (p) { // 当边表未遍历完
        if (!visited[p->adjvex]) { // 当前边表节点的邻接点未被访问
            DFS(GL, p->adjvex); // 对改邻接点递归调用
        }
        p = p->next; // 移动到边表的下一个节点
    }
}

/**
 * 深度遍历邻接表
 * @param GL 邻接表
 */
void DFSTraverse(GraphAdjList GL) {
    int i; // 用于遍历元素

    // 设置所有顶点都未被访问过
    for (i = 0; i < GL->numNodes; i++) {
        visited[i] = FALSE;
    }

    // 对所有顶点进行遍历
    for (i = 0; i < GL->numNodes; i++) {
        if (!visited[i]) {  // 如果顶点i未被访问过
            DFS(GL, i); // 访问顶点i
        }
    }
}

/**
 * 广度优先遍历邻接表
 * @param GL 邻接表
 */
void BFSTraverse(GraphAdjList GL) {
    int i; // 用于遍历元素
    EdgeNode *p; // 边表节点
    Queue Q; // 队列

    // 设置所有顶点都未被访问过
    for (i = 0; i < GL->numNodes; i++) {
        visited[i] = FALSE;
    }

    InitQueue(&Q); // 初始化队列

    // 遍历所有顶点
    for (i = 0; i < GL->numNodes; i++) {
        if (!visited[i]) { // 该顶点未被访问过，进行处理
            visited[i] = TRUE; // 设置该顶点i已被访问

            printf("%c ", GL->adjList[i].data); // 打印顶点数据

            EnQueue(&Q, i); // 将顶点i入队

            // 当队列非空时，进行循环
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i); // 将队头元素出队，赋值给i

                p = GL->adjList[i].firstEdge; // p指向当前顶点的边表第一个节点

                while (p) { // 当边表未遍历完
                    if (!visited[p->adjvex]) { // 此顶点未被访问过
                        visited[p->adjvex] = TRUE; // 设置该顶点已被访问

                        printf("%c ", GL->adjList[p->adjvex].data); // 打印顶点数据

                        EnQueue(&Q, p->adjvex); // 将此顶点入队
                    }
                    p = p->next; // p指向下一个邻接点
                }

            }
        }
    }
}

int main() {
    MGraph G; // 邻接矩阵
    GraphAdjList GL; // 邻接表

    CreateMGraph(&G); // 创建邻接矩阵
    CreateALGraph(G, &GL); // 利用邻接矩阵创建邻接表

    printf("深度遍历：");
    DFSTraverse(GL); // 深度遍历邻接表

    printf("\n广度遍历：");
    BFSTraverse(GL); // 深度遍历邻接表

    return 0;
}