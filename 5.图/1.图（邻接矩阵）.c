// ͼ���ڽӾ���
#include <stdio.h>

#define MAXVEX 100 // ��󶥵���
#define INFINITY 65535 // ����

typedef char VertexType; // ����Ԫ������
typedef int EdgeType; // ����Ȩֵ������

// �ڽӾ���ṹ������ͼ��
typedef struct {
    VertexType vexs[MAXVEX]; // �����
    EdgeType arc[MAXVEX][MAXVEX]; // �߱�
    int numNodes, numEdges; // ͼ�Ķ�����������
} MGraph;

/**
 * ��������ͼ���ٽӾ����ʾ
 * @param G �ڽӾ�������ͼ��
 */
void CreateMGraph(MGraph *G) {
    int i, j, k, w;

    printf("�����붥�����ͱ�����\n");
    scanf("%d,%d", &G->numNodes, &G->numEdges); // ��ȡ�������ͱ���
    getchar(); // ���ڵ����س���

    printf("������%d�������ֵ��\n", G->numNodes);
    // �������붥�����Ϣ
    for (i = 0; i < G->numNodes; i++) {
        scanf("%c", &G->vexs[i]); // ��ȡ�û������ֵ���������
        getchar();  // ���ڵ����س���
    }

    printf("������%d���ߵ�ֵ��\n", G->numEdges);
    // ��ʼ���߱�
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = INFINITY; // ���ñ߱������е�ֵΪ����
        }
    }

    // ��������߱���Ϣ
    for (k = 0; k < G->numEdges; k++) {
        printf("�����%d���ߣ�(vi,vj)=w���±�i���±�j��Ȩֵw\n", k + 1);
        scanf("%d,%d,%d", &i, &j, &w); // ����ߣ�vi��vj���ϵ�Ȩ
        getchar(); // ���ڵ����س���

        G->arc[i][j] = w; // ���ñߣ�vi��vj���ϵ�Ȩֵ
        G->arc[j][i] = G->arc[i][j]; // ��Ϊ������ͼ������Գƣ��ߣ�vj��vi�����ڱߣ�vi��vj��
    }
}

/**
 * ��ӡ����ͼ
 * @param G �ڽӾ�������ͼ��
 */
void Print(MGraph *G) {
    int i, j; // ��������Ԫ��

    printf("������ֵΪ��\n");
    // ��ӡ�����
    for (i = 0; i < G->numNodes; i++) {
        printf("v%d: %c\n", i, G->vexs[i]);
    }
    printf("\n");

    printf("�߱��ֵΪ��\n");
    // ��ӡ�߱�
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            if (G->arc[i][j] != INFINITY) { // Ԫ�ز�Ϊ�����ʾ�ñ���ֵ
                printf("<v%d, v%d>: %d\n", i, j, G->arc[i][j]);
            }
        }
    }
}

int main() {
    MGraph G; // �ڽӾ���
    CreateMGraph(&G); // �����ڽӾ�������ͼ��
    Print(&G); // ��ӡ�ڽӾ�������ͼ��

    return 0;
}
