// ͼ���ڽӱ�
#include <stdio.h>
#include <malloc.h>

#define MAXVEX 100 // ��󶥵���

typedef char VertexType; // ��������
typedef int EdgeType; // ���ϵ�Ȩֵ����

// �߱�ڵ�
typedef struct EdgeNode {
    int adjvex; // �ڽӵ��򣬴洢�ö����Ӧ���±�
    EdgeType info; // �����洢Ȩֵ������ͼ��û�У�
    struct EdgeNode *next; // ָ����һ���ڽӵ�
} EdgeNode;

// �����ڵ�
typedef struct VertexNode {
    VertexType data; // �����򣬴洢������Ϣ
    EdgeNode *firstEdge; // �߱�ͷָ��
} VertexNode, AdjList[MAXVEX];

// �ڽӱ�ṹ
typedef struct {
    AdjList adjList;// ���������
    int numNodes, numEdges; // ͼ�е�ǰ������������
} GraphAdjList;

/**
 * �����ڽӱ�
 * @param G �ڽӱ�
 */
void CreateALGraph(GraphAdjList *G) {
    int i, j, k; // ��������Ԫ��
    EdgeNode *e; // �߱�ڵ�

    printf("���붥�����ͱ�����\n");
    scanf("%d,%d", &G->numNodes, &G->numEdges);
    getchar(); // ���������س�

    printf("����%d���������Ϣ��\n", G->numNodes);

    // ��ȡ���ж������Ϣ
    for (i = 0; i < G->numNodes; i++) {
        scanf("%c", &G->adjList[i].data); // ��ȡ������Ϣ
        getchar(); // ���������س�

        G->adjList[i].firstEdge = NULL; // ���߱���Ϊ�ձ�
    }

    // ��ȡ���бߵ���Ϣ
    for (k = 0; k < G->numEdges; k++) {
        printf("��%d���ߣ�����ߣ�vi��vj���ϵĶ�����ţ�\n", k + 1);
        scanf("%d,%d", &i, &j); // ��ȡ��㡢�յ����
        getchar(); // ���������س�

        e = (EdgeNode *) malloc(sizeof(EdgeNode)); // Ϊ�߱�ڵ����洢�ռ�
        e->adjvex = j; // �ڽ����Ϊj
        e->next = G->adjList[i].firstEdge; // ��e��ָ��ָ��ǰ������ָ��Ľڵ�
        G->adjList[i].firstEdge = e; // ����ǰ�����ָ��ָ��e

        e = (EdgeNode *) malloc(sizeof(EdgeNode)); // Ϊ�߱�ڵ����洢�ռ�
        e->adjvex = i; // �ڽ����Ϊi
        e->next = G->adjList[j].firstEdge; // ��e��ָ��ָ��ǰ������ָ��Ľڵ�
        G->adjList[j].firstEdge = e; // ����ǰ�����ָ��ָ��e
    }
}

/**
 * ��ӡ�ڽӱ�
 * @param G �ڽӱ�
 */
void Print(GraphAdjList *G) {
    int i, j; // ��������Ԫ��
    EdgeNode *p;

    printf("������ֵΪ��\n");
    // ��ӡ�����
    for (i = 0; i < G->numNodes; i++) {
        printf("v%d: %c\n", i, G->adjList[i].data);
    }

    printf("�߱��ֵΪ��\n");
    for (i = 0; i < G->numNodes; i++) {
        printf("v%d ", i);

        p = G->adjList[i].firstEdge; // pָ�򶥵�i�ı߱�

        while (p) { // �߱�δ������
            printf("-> %d", p->adjvex); // ��ӡ�ڽӵ�
            p = p->next; // p�ƶ�����һ���߱�ڵ�
        }
        printf("\n");
    }
}

int main() {
    GraphAdjList G; // �ڽӱ�
    CreateALGraph(&G); // �����ڽӱ�
    Print(&G); // ��ӡ�ڽӱ�

    return 0;
}