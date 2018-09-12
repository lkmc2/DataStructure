// ͼ�����������㷨
#include <stdio.h>
#include <malloc.h>

#define MAXEDGE 20 // ������
#define MAXVEX 14 // ��󶥵���

#define OK 1 // ִ�гɹ�
#define ERROR 0 // ִ��ʧ��

typedef int Status; // ִ��״̬

// �ڽӾ���ṹ
typedef struct {
    int vexs[MAXVEX]; // �����
    int arc[MAXVEX][MAXVEX]; // �߱�
    int numNodes, numEdges; // ͼ�е�ǰ�Ķ�����������
} MGraph;

/**************** �õ����ڽӱ�ṹ ****************/

// �߱�ڵ�
typedef struct EdgeNode {
    int adjvex; // �ڽӵ��򣬴洢�ö����Ӧ���±�
    int weight; // �����洢Ȩֵ������ͼ��û�У�
    struct EdgeNode *next; // ָ����һ���ڽӵ�
} EdgeNode;

// �����ڵ�
typedef struct VertexNode {
    int in; // �������
    int data; // �����򣬴洢������Ϣ
    EdgeNode *firstEdge; // �߱�ͷָ��
} VertexNode, AdjList[MAXVEX];

// �ڽӱ�ṹ
typedef struct {
    AdjList adjList;// ���������
    int numNodes, numEdges; // ͼ�е�ǰ������������
} graphAdjList, *GraphAdjList;

/*************************************************/

/**
 * �����ڽӾ���ͼ��
 * @param G �ڽӾ���ͼ��
 */
void CreateMGraph(MGraph *G) {
    int i, j; // ���ڱ���Ԫ��

    G->numEdges = MAXEDGE; // ���ñ���
    G->numNodes = MAXVEX; // ���ö�����

    // ��ʼ��ͼ�Ķ����
    for (i = 0; i < G->numNodes; i++) {
        G->vexs[i] = i;
    }

    // ��ʼ��ͼ�ı߱�
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = 0; // �������бߵ�Ĭ��ֵΪ0
        }
    }

    // �����ض��ߵ�Ȩ��ֵΪ1��ʾ��λ���бߣ�
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
 * ʹ���ڽӾ��������ڽӱ�
 * @param G �ڽӾ���
 * @param GL �ڽӱ�
 */
void CreateALGraph(MGraph G, GraphAdjList *GL) {
    int i, j; // ���ڱ���Ԫ��
    EdgeNode *e; // �߱�ڵ�

    *GL = (GraphAdjList) malloc(sizeof(graphAdjList)); // Ϊ�ڽӱ�����洢�ռ�

    (*GL)->numNodes = G.numNodes; // �����ڽӱ�Ķ�����
    (*GL)->numEdges = G.numEdges; // �����ڽӱ�ı���

    // ���������
    for (i = 0; i < G.numNodes; i++) {
        (*GL)->adjList[i].in = 0; // �����±�Ϊiλ�õĶ������Ϊ0
        (*GL)->adjList[i].data = G.vexs[i]; // ����ö����Ȩֵ
        (*GL)->adjList[i].firstEdge = NULL; // ���ö����Ӧ�ı߱�Ϊ��
    }

    // �����߱�
    for (i = 0; i < G.numNodes; i++) {
        for (j = 0; j < G.numNodes; j++) {
            if (G.arc[i][j] == 1) {
                e = (EdgeNode *) malloc(sizeof(EdgeNode)); // Ϊ�߱�ڵ����洢�ռ�
                e->adjvex = j; // �����ڽ����Ϊj
                e->next = (*GL)->adjList[i].firstEdge; // �½ڵ�ָ��ָ��߱��ͷ�ڵ�
                (*GL)->adjList[i].firstEdge = e; // ���½ڵ��Ϊ�߱��ͷ�ڵ�
                (*GL)->adjList[j].in++; // ���յ���ָ��Ľڵ���ȼ�1
            }
        }
    }
}

/**
 * ��������
 * ���ڽӱ��޻�·������������������в�����OK�����л�·�򷵻�ERROR
 * @param GL �ڽӱ�
 * @return ִ��״̬
 */
Status TopologicalSort(GraphAdjList GL) {
    EdgeNode *e; // �߱�ڵ�
    int i, k, gettop; // i���ڱ���Ԫ�أ�k������ȡ�����±꣬gettop������ȡջ��Ԫ���±�
    int top = 0; // ����ջָ���±�
    int count = 0; // ����ͳ���������ĸ���
    int *stack; // �洢���Ϊ0�Ķ����ջ

    stack = (int *) malloc(GL->numNodes * sizeof(int)); // Ϊջ����洢�ռ�

    // ���������Ϊ0�Ķ�����ջ
    for (i = 0; i < GL->numNodes; i++) {
        if (GL->adjList[i].in == 0) { // �������Ϊ0
            stack[++top] = i; // ���ýڵ���ջ
        }
    }

    // δ���������Ϊ0�Ķ����ջ
    while (top != 0) {
        gettop = stack[top--]; // ��ȡ���Ϊ0��ջ��ջ��Ԫ��
        printf("%d -> ", GL->adjList[gettop].data); // ��ӡ��Ԫ�صĶ�����Ϣ
        count++; // ���붥�������1

        // �����ö���ı߱�
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            k = e->adjvex; // ��ȡ�¸����㣨���յ���ָ��Ľڵ㣩���±�

            // �����յ���ָ��Ľڵ����ȼ�1������ö������Ϊ0����������ջ
            if (!(--GL->adjList[k].in)) {
                stack[++top] = k; // ��������ջ
            }
        }
    }
    printf("\n");

    // ����Ķ�����С���ڽӱ�Ķ��������ڽӱ����л�·����������ʧ��
    if (count < GL->numNodes) {
        return ERROR;
    } else { // �ڽӱ����޻�·����������ɹ�
        return OK;
    }
}

int main() {
    MGraph G; // �ڽӾ���
    GraphAdjList GL; // �ڽӱ�
    Status status; // ִ��״̬

    CreateMGraph(&G); // �����ڽӾ���
    CreateALGraph(G, &GL); // ʹ���ڽӾ��󴴽��ڽӱ�

    status = TopologicalSort(GL); // ���ڽӱ�����������򣬻�ȡִ��״̬
    printf("status: %s", status == OK ? "ִ�гɹ�" : "ִ��ʧ��");

    return 0;
}