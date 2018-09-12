// �ڽӾ������Ⱥ͹�����ȱ���
#include <stdio.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

typedef int Status; // ִ��״̬��OK��ERROR��
typedef int Boolean; // ����ֵ��TRUE��FALSE��

typedef char VertexType; // ����Ԫ������
typedef int EdgeType; // ����Ȩֵ������

#define MAXSIZE 9 // ���д���ռ��ʼ������
#define MAXVEX 100 // ��󶥵���

// �ڽӾ���ṹ������ͼ��
typedef struct {
    VertexType vexs[MAXVEX]; // �����
    EdgeType arc[MAXVEX][MAXVEX]; // �߱�
    int numNodes, numEdges; // ͼ�Ķ�����������
} MGraph;

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

// ���ʱ�־������
Boolean visited[MAXVEX];


/**
 * �ڽӾ����������ȵݹ��㷨
 * @param G �ڽӾ���
 * @param i �����±�
 */
void DFS(MGraph G, int i) {
    int j; // ���ڱ���Ԫ��

    visited[i] = TRUE; // ��¼���±��Ԫ���ѱ�����

    printf("%c ", G.vexs[i]); // ��ӡ��λ�õĶ���ֵ

    // ����ͼ�еĶ���
    for (j = 0; j < G.numNodes; j++) {
        // ����i������j�б����������Ҷ���jδ�����ʹ�
        if (G.arc[i][j] == 1 && !visited[j]) {
            DFS(G, j); // �Զ���j���з���
        }
    }
}

/**
 * �ڽӾ������ȱ���
 * @param G �ڽӾ���
 */
void DFSTraverse(MGraph G) {
    int i; // ���ڱ���Ԫ��

    // ��ʼ���������ж��㶼û�����ʹ�
    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }

    // ��������i
    for (i = 0; i < G.numNodes; i++) {
        // �������iδ�����ʹ�
        if (!visited[i]) {
            DFS(G, i); // ���ʶ���i
        }
    }
}

/**
 * �ڽӾ���Ĺ�ȱ����㷨
 * @param G �ڽӾ���
 */
void BFSTraverse(MGraph G) {
    int i, j; // ���ڱ���Ԫ��
    Queue Q; // ����

    // ��ʼ����ͼ�����ж��㶼û�����ʹ�
    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }

    InitQueue(&Q); // ��ʼ������

    // ��ÿһ��������ѭ��
    for (i = 0; i < G.numNodes; i++) {
        if (!visited[i]) { // �ö���δ�����ʹ������д���
            visited[i] = TRUE; // ���øö���i�ѱ�����

            printf("%c ", G.vexs[i]); // ��ӡ�ö���i��ֵ

            EnQueue(&Q, i); // ���ö���i���

            // �����зǿ�ʱ������ѭ��
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i); // ����ͷԪ�س��ӣ���ֵ��i

                // ������ǰ�ڵ�����Ľڵ�j
                for (j = 0; j < G.numNodes; j++) {
                    // ������j�뵱ǰ�ڵ���ڱߣ�����δ�����ʹ�
                    if (G.arc[i][j] == 1 && !visited[j]) {
                        visited[j] = TRUE; // ���ö���j�ѱ�����
                        printf("%c ", G.vexs[j]); // ��ӡ����j��ֵ

                        EnQueue(&Q, j); // ������j���
                    }
                }
            }
        }
    }
}

int main() {
    MGraph G; // �ڽӾ���
    CreateMGraph(&G); // �����ڽӾ���
    printf("��ȱ�����");
    DFSTraverse(G); // ��ȱ����ڽӾ���

    printf("\n��ȱ�����");
    BFSTraverse(G); // ��ȱ����ڽӾ���

    return 0;
}
