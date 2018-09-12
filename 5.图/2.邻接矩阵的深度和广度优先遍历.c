// 邻接矩阵的深度和广度优先遍历
#include <stdio.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

typedef int Status; // 执行状态（OK、ERROR）
typedef int Boolean; // 布尔值（TRUE、FALSE）

typedef char VertexType; // 顶点元素类型
typedef int EdgeType; // 边上权值的类型

#define MAXSIZE 9 // 队列储存空间初始分配量
#define MAXVEX 100 // 最大顶点数

// 邻接矩阵结构（无向图）
typedef struct {
    VertexType vexs[MAXVEX]; // 顶点表
    EdgeType arc[MAXVEX][MAXVEX]; // 边表
    int numNodes, numEdges; // 图的顶点数、边数
} MGraph;

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

// 访问标志的数组
Boolean visited[MAXVEX];


/**
 * 邻接矩阵的深度优先递归算法
 * @param G 邻接矩阵
 * @param i 顶点下标
 */
void DFS(MGraph G, int i) {
    int j; // 用于遍历元素

    visited[i] = TRUE; // 记录该下标的元素已被访问

    printf("%c ", G.vexs[i]); // 打印该位置的顶点值

    // 遍历图中的顶点
    for (j = 0; j < G.numNodes; j++) {
        // 顶点i到顶点j有边相连，并且顶点j未被访问过
        if (G.arc[i][j] == 1 && !visited[j]) {
            DFS(G, j); // 对顶点j进行访问
        }
    }
}

/**
 * 邻接矩阵的深度遍历
 * @param G 邻接矩阵
 */
void DFSTraverse(MGraph G) {
    int i; // 用于遍历元素

    // 初始化设置所有顶点都没被访问过
    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }

    // 遍历顶点i
    for (i = 0; i < G.numNodes; i++) {
        // 如果顶点i未被访问过
        if (!visited[i]) {
            DFS(G, i); // 访问顶点i
        }
    }
}

/**
 * 邻接矩阵的广度遍历算法
 * @param G 邻接矩阵
 */
void BFSTraverse(MGraph G) {
    int i, j; // 用于遍历元素
    Queue Q; // 队列

    // 初始设置图的所有顶点都没被访问过
    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }

    InitQueue(&Q); // 初始化队列

    // 对每一个顶点做循环
    for (i = 0; i < G.numNodes; i++) {
        if (!visited[i]) { // 该顶点未被访问过，进行处理
            visited[i] = TRUE; // 设置该顶点i已被访问

            printf("%c ", G.vexs[i]); // 打印该顶点i的值

            EnQueue(&Q, i); // 将该顶点i入队

            // 当队列非空时，进行循环
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i); // 将队头元素出队，赋值给i

                // 遍历当前节点以外的节点j
                for (j = 0; j < G.numNodes; j++) {
                    // 若顶点j与当前节点存在边，并且未被访问过
                    if (G.arc[i][j] == 1 && !visited[j]) {
                        visited[j] = TRUE; // 设置顶点j已被访问
                        printf("%c ", G.vexs[j]); // 打印顶点j的值

                        EnQueue(&Q, j); // 将顶点j入队
                    }
                }
            }
        }
    }
}

int main() {
    MGraph G; // 邻接矩阵
    CreateMGraph(&G); // 创建邻接矩阵
    printf("深度遍历：");
    DFSTraverse(G); // 深度遍历邻接矩阵

    printf("\n广度遍历：");
    BFSTraverse(G); // 广度遍历邻接矩阵

    return 0;
}
