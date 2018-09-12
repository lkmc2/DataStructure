// ͼ�Ĺؼ�·���㷨
#include <stdio.h>
#include <malloc.h>

#define OK 1 // ִ�гɹ�
#define ERROR 0 // ִ��ʧ��

#define MAXVEX 14 // ��󶥵���
#define INFINITY 65535 // ����

typedef int Status; // ִ��״̬

int *etv, *ltv; // �¼����緢��ʱ����¼���ٷ���ʱ�����飬ȫ�ֱ���
int *stack2; // ���ڴ洢�������е�ջ
int top2; // ����stack2��ָ��

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

    G->numEdges = 13; // ���ñ���
    G->numNodes = 10; // ���ö�����

    // ��ʼ��ͼ�Ķ����
    for (i = 0; i < G->numNodes; i++) {
        G->vexs[i] = i;
    }

    // ��ʼ��ͼ�ı߱�
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            if (i == j) { // ����ǶԽ��߶������ڱ�
                G->arc[i][j] = 0; // ���ñߵ�ȨֵΪ0
            } else { // ������
                G->arc[i][j] = INFINITY; // ����ȨֵΪ����
            }
        }
    }

    // �����ض��ߵ�Ȩֵ
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
            // ����ñ���·����ͨ
            if (G.arc[i][j] != 0 && G.arc[i][j] < INFINITY) {
                e = (EdgeNode *) malloc(sizeof(EdgeNode)); // Ϊ�߱�ڵ����洢�ռ�
                e->adjvex = j; // �����ڽ����Ϊj
                e->weight = G.arc[i][j]; // ���ýڵ��Ȩֵ
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

    top2 = 0; // ����stack2��ջ��ָ��Ϊ0

    etv = (int *) malloc(GL->numNodes * sizeof(int)); // �¼����緢��ʱ������
    for (i = 0; i < GL->numNodes; i++) {
        etv[i] = 0; // ��ʼ���¼����緢��ʱ�䶼Ϊ0
    }

    stack2 = (int *) malloc(GL->numNodes * sizeof(int)); // ��ʼ����������ջ

    printf("��������\n");
    // δ���������Ϊ0�Ķ����ջ
    while (top != 0) {
        gettop = stack[top--]; // ��ȡ���Ϊ0��ջ��ջ��Ԫ��
        printf("%d -> ", GL->adjList[gettop].data); // ��ӡ��Ԫ�صĶ�����Ϣ
        count++; // ���붥�������1

        stack2[++top2] = gettop; // �������Ķ������ѹ���������е�ջ

        // �����ö���ı߱�
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            k = e->adjvex; // ��ȡ�¸����㣨���յ���ָ��Ľڵ㣩���±�

            // �����յ���ָ��Ľڵ����ȼ�1������ö������Ϊ0����������ջ
            if (!(--GL->adjList[k].in)) {
                stack[++top] = k; // ��������ջ
            }

            // ��������¼������緢��ʱ��etv��ֵ
            // ���������ֵ���ϱ��ϵ�Ȩֵ���ڱ��յ��ֵ
            if (etv[gettop] + e->weight > etv[k]) {
                // ���ñ��յ��ֵΪ������ֵ���ϱ��ϵ�Ȩֵ
                etv[k] = etv[gettop] + e->weight;
                // �綥��1�Ͷ���2�����ﶥ��3��
                // ��ô����3�����翪ʼʱ��Ϊmax������1 + ���ϵ�Ȩֵ������2 + ���ϵ�Ȩֵ��
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

/**
 * �ؼ�·���㷨
 * @param GL �ڽӱ�
 */
void CriticalPath(GraphAdjList GL) {
    EdgeNode *e; // �߱�ڵ�
    int i, j, k ;  // i��j��������Ԫ�أ�k������ȡ�߱�ڵ���±�
    int gettop;  // gettop������ȡ��������ջ��ջ��Ԫ�ص��±�
    int ete, lte; // ��¼����緢��ʱ�䣬���ٷ���ʱ��

    TopologicalSort(GL); // ���������У���������etv��stack2��ֵ

    ltv = (int *) malloc(GL->numNodes * sizeof(int)); // Ϊ�¼���ٷ���ʱ���������洢�ռ�
    for (i = 0; i < GL->numNodes; i++) { // ��ʼ���¼���ٷ���ʱ������
        ltv[i] = etv[GL->numNodes - 1]; // ����ֵΪ�¼����緢��ʱ������Ľ���ʱ��
    }

    // ��ӡ�¼����緢��ʱ������
    printf("etv:\n");
    for (i = 0; i < GL->numNodes; i++) {
        printf("%d -> ", etv[i]);
    }
    printf("\n");

    // �������е�ջδ��ջ��
    while (top2 != 0) {
        gettop = stack2[top2--]; // ��ȡ��������ջ��ջ��Ԫ��

        // ������ö��������ı�
        // ��������¼�����ٷ���ʱ��ltv��ֵ
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            k = e->adjvex; // ��ȡ�ڵ��±�
            // ������յ��ֵ��ȥ�ߵ�ȨֵС�ڱ�����ֵ
            // ltv[9] - 3 < ltv[8] = 24��ltv[8] = 27��min(27, 24) = 24
            if (ltv[k] - e->weight < ltv[gettop]) {
                // ���ñ�����ֵΪ���յ��ֵ��ȥ�ߵ�Ȩֵ
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }

    // ��ӡ�¼���ٷ���ʱ������
    printf("ltv:\n");
    for (i = 0; i < GL->numNodes; i++) {
        printf("%d -> ", ltv[i]);
    }
    printf("\n");

    printf("�������·�����ȣ�\n");
    for (j = 0; j < GL->numNodes; j++) {
        for (e = GL->adjList[j].firstEdge; e; e = e->next) {
            k = e->adjvex; // ��ȡ��ǰ������±�
            ete = etv[j];  // ����緢��ʱ��
            lte = ltv[k] - e->weight; // ���ٷ���ʱ��

            // ����緢��ʱ�������ٷ���ʱ�䣬������ȱ�ʾ�ڹؼ�·����
            if (ete == lte) {
                printf("<v%d - v%d> length: %d \n", GL->adjList[j].data, GL->adjList[k].data, e->weight);
            }
        }
    }
}

int main() {
    MGraph G; // �ڽӾ���
    GraphAdjList GL; // �ڽӱ�

    CreateMGraph(&G); // �����ڽӾ���
    CreateALGraph(G, &GL); // ʹ���ڽӾ��󴴽��ڽӱ�
    CriticalPath(GL); // ��ͼ�Ĺؼ�·��

    return 0;
}