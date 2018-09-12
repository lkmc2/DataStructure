// �ڽӱ����Ⱥ͹�����ȱ���
#include <stdio.h>
#include <malloc.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

#define MAXSIZE 9 // ���д洢�ռ��ʼ������
#define MAXVEX 100 // ��󶥵���

typedef int Status; // ִ��״̬��OK��ERROR��
typedef int Boolean; // ����ֵ��TRUE��FALSE��

typedef char VertexType; // ��������
typedef int EdgeType; // ���ϵ�Ȩֵ����

/**************** �õ����ڽӾ���ṹ ****************/

// �ڽӾ���ṹ
typedef struct {
    VertexType vexs[MAXVEX]; // �����
    EdgeType arc[MAXVEX][MAXVEX]; // �߱�
    int numNodes, numEdges; // ͼ�е�ǰ�Ķ�����������
}MGraph;

/**************** �õ����ڽӱ�ṹ ****************/

// �߱�ڵ�
typedef struct EdgeNode {
    int adjvex; // �ڽӵ��򣬴洢�ö����Ӧ���±�
    EdgeType info; // �����洢Ȩֵ������ͼ��û�У�
    struct EdgeNode *next; // ָ����һ���ڽӵ�
} EdgeNode;

// �����ڵ�
typedef struct VertexNode {
    int in; // �������
    VertexType data; // �����򣬴洢������Ϣ
    EdgeNode *firstEdge; // �߱�ͷָ��
} VertexNode, AdjList[MAXVEX];

// �ڽӱ�ṹ
typedef struct {
    AdjList adjList;// ���������
    int numNodes, numEdges; // ͼ�е�ǰ������������
} graphAdjList, *GraphAdjList;

/************** �õ��Ķ��нṹ�뺯�� **************/

// ѭ������˳��洢�ṹ
typedef struct {
    int data[MAXSIZE]; // ���ڴ�ֵ������
    int front; // ͷָ��
    int rear; // βָ�룬�����в��գ�ָ���βԪ�ص���һ��λ��
} Queue;

/**
 * ��ʼ��һ���ն���
 * @param Q ����
 * @return ִ��״̬
 */
Status InitQueue(Queue *Q) {
    Q->front = Q->rear=  0; // ��ͷ�Ͷ�βָ�붼ָ��0
    return OK;
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ����
 * @return �����Ƿ�Ϊ��
 */
Boolean QueueEmpty(Queue Q) {
    if (Q.front == Q.rear) { // ��ͷ���ڶ�βָ�룬����Ϊ��
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��Ԫ��e�������Q�Ķ�β
 * @param Q ����
 * @param e �����Ԫ��
 * @return ִ��״̬
 */
Status EnQueue(Queue *Q, int e) {
    // ��������������ʧ��
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return ERROR;
    }

    // ��Ԫ��e�����β
    Q->data[Q->rear] = e;

    // ���ö�βָ��ָ����һ��λ�ã����������ת��ͷ��
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

/**
 * ��ͷԪ�س��ӣ���e������ֵ
 * @param Q ����
 * @param e ��ͷԪ�ص�ֵ
 * @return ִ��״̬
 */
Status DeQueue(Queue *Q, int *e) {
    // ��ͷָ����ڶ�βָ�룬��ʱ����Ϊ�գ�����ʧ��
    if (Q->front == Q->rear) {
        return ERROR;
    }

    // ����ͷԪ�ص�ֵ����Ԫ��e
    *e = Q->data[Q->front];

    // ���ö�ͷָ��ָ����һ��λ�ã����������ת��ͷ��
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

/*************************************************/

/**
 * �����ڽӾ���
 * @param G �ڽӾ���
 */
void CreateMGraph(MGraph *G) {
    int i, j; // ���ڱ���Ԫ��

    G->numEdges = 15; // ������15����
    G->numNodes = 9; // ������9������

    // ���붥����Ϣ�����������
    G->vexs[0] = 'A';
    G->vexs[1] = 'B';
    G->vexs[2] = 'C';
    G->vexs[3] = 'D';
    G->vexs[4] = 'E';
    G->vexs[5] = 'F';
    G->vexs[6] = 'G';
    G->vexs[7] = 'H';
    G->vexs[8] = 'I';

    // ��ʼ��ͼ�ı�
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = 0; // �������бߵ�ֵ��Ϊ0
        }
    }

    // �����ض��ߣ����arc[i][j] = 1��������i������j�б�������
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

    // ���öԳƱ�
    for (i = 0; i < G->numNodes; i++) {
        for (j = i; j < G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/**
 * �����ڽӾ���G�����ڽ�����GL
 * @param G �ڽӾ���
 * @param GL �ڽ�����
 */
void CreateALGraph(MGraph G, GraphAdjList *GL) {
    int i, j; // ���ڱ���Ԫ��
    EdgeNode *e; // �߱�Ľڵ�

    *GL = (GraphAdjList)malloc(sizeof(graphAdjList)); // Ϊ�ڽӱ����洢�ռ�

    (*GL)->numNodes = G.numNodes; // �����ڽӱ�Ķ�����
    (*GL)->numEdges = G.numEdges; // �������ӱ�ı���

    // �����ڽӱ��ж������Ϣ
    for (i = 0; i < G.numNodes; i++) {
        (*GL)->adjList[i].in = 0; // ���ö������
        (*GL)->adjList[i].data = G.vexs[i]; // ���ö����ֵ
        (*GL)->adjList[i].firstEdge = NULL; // ���߱���Ϊ�ձ�
    }

    // �����ڽӱ��б߱���Ϣ
    for (i = 0; i <G.numNodes; i++) {
        for (j = 0;j < G.numNodes; j++) {
            if (G.arc[i][j] == 1) {
                e = (EdgeNode *) malloc(sizeof(EdgeNode)); // Ϊ�߱�Ľڵ����洢�ռ�
                e->adjvex = j; // �����ڽ����Ϊj
                e->next = (*GL)->adjList[i].firstEdge; // ��e��ָ��ָ��ǰ������ָ��Ľڵ�
                (*GL)->adjList[i].firstEdge = e; // ����ǰ�����ָ��ָ��e
            }
        }
    }
}

// ���ʱ�־������
Boolean visited[MAXVEX];

/**
 * �ڽӱ��������ȵݹ��㷨
 * @param GL �ڽӱ�
 * @param i �����±�
 */
void DFS(GraphAdjList GL, int i) {
    EdgeNode *p; // �߱�ڵ�
    visited[i] = TRUE; // ���õ�ǰ�±�ڵ��ѱ�����

    printf("%c ", GL->adjList[i].data); // ��ӡ����ֵ

    p = GL->adjList[i].firstEdge; // pָ��ǰ����ı߱��һ���ڵ�

    while (p) { // ���߱�δ������
        if (!visited[p->adjvex]) { // ��ǰ�߱�ڵ���ڽӵ�δ������
            DFS(GL, p->adjvex); // �Ը��ڽӵ�ݹ����
        }
        p = p->next; // �ƶ����߱����һ���ڵ�
    }
}

/**
 * ��ȱ����ڽӱ�
 * @param GL �ڽӱ�
 */
void DFSTraverse(GraphAdjList GL) {
    int i; // ���ڱ���Ԫ��

    // �������ж��㶼δ�����ʹ�
    for (i = 0; i < GL->numNodes; i++) {
        visited[i] = FALSE;
    }

    // �����ж�����б���
    for (i = 0; i < GL->numNodes; i++) {
        if (!visited[i]) {  // �������iδ�����ʹ�
            DFS(GL, i); // ���ʶ���i
        }
    }
}

/**
 * ������ȱ����ڽӱ�
 * @param GL �ڽӱ�
 */
void BFSTraverse(GraphAdjList GL) {
    int i; // ���ڱ���Ԫ��
    EdgeNode *p; // �߱�ڵ�
    Queue Q; // ����

    // �������ж��㶼δ�����ʹ�
    for (i = 0; i < GL->numNodes; i++) {
        visited[i] = FALSE;
    }

    InitQueue(&Q); // ��ʼ������

    // �������ж���
    for (i = 0; i < GL->numNodes; i++) {
        if (!visited[i]) { // �ö���δ�����ʹ������д���
            visited[i] = TRUE; // ���øö���i�ѱ�����

            printf("%c ", GL->adjList[i].data); // ��ӡ��������

            EnQueue(&Q, i); // ������i���

            // �����зǿ�ʱ������ѭ��
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i); // ����ͷԪ�س��ӣ���ֵ��i

                p = GL->adjList[i].firstEdge; // pָ��ǰ����ı߱��һ���ڵ�

                while (p) { // ���߱�δ������
                    if (!visited[p->adjvex]) { // �˶���δ�����ʹ�
                        visited[p->adjvex] = TRUE; // ���øö����ѱ�����

                        printf("%c ", GL->adjList[p->adjvex].data); // ��ӡ��������

                        EnQueue(&Q, p->adjvex); // ���˶������
                    }
                    p = p->next; // pָ����һ���ڽӵ�
                }

            }
        }
    }
}

int main() {
    MGraph G; // �ڽӾ���
    GraphAdjList GL; // �ڽӱ�

    CreateMGraph(&G); // �����ڽӾ���
    CreateALGraph(G, &GL); // �����ڽӾ��󴴽��ڽӱ�

    printf("��ȱ�����");
    DFSTraverse(GL); // ��ȱ����ڽӱ�

    printf("\n��ȱ�����");
    BFSTraverse(GL); // ��ȱ����ڽӱ�

    return 0;
}