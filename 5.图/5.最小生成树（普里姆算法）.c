// ��С������������ķ�㷨��
#include <stdio.h>

#define MAXVEX 100 // ��󶥵���
#define INFINITY 65535 // ����

typedef int EdgeType; // ���ϵ�Ȩֵ����

// �ڽӾ���ṹ
typedef struct {
    EdgeType arc[MAXVEX][MAXVEX]; // �߱�
    int numNodes, numEdges; // ͼ�е�ǰ�Ķ�����������
}MGraph;


/**
 * �����ڽӾ���
 * @param G �ڽӾ���
 */
void CreateMGraph(MGraph *G) {
    int i, j; // ���ڱ���Ԫ��

    G->numEdges = 15; // ������15����
    G->numNodes = 9; // ������9������

    // ��ʼ��ͼ�ı�
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            if (i == j) { // �Խ��߱ߵ�ֵ����Ϊ0
                G->arc[i][j] = 0;
            } else { // ����λ�õı�����Ϊ����
                G->arc[i][j] = G->arc[j][i] = INFINITY;
            }
        }
    }

    // �����ض��ߵ�Ȩ
    G->arc[0][1] = 10;
    G->arc[0][5] = 11;

    G->arc[1][2] = 18;
    G->arc[1][8] = 12;
    G->arc[1][6] = 16;

    G->arc[2][3] = 22;
    G->arc[2][8] = 21;

    G->arc[3][4] = 20;
    G->arc[3][7] = 16;
    G->arc[3][6] = 24;
    G->arc[3][8] = 21;

    G->arc[4][5] = 26;
    G->arc[4][7] = 7;

    G->arc[5][6] = 17;

    G->arc[6][7] = 19;

    // ���öԳƱߵ�Ȩ
    for (i = 0; i < G->numNodes; i++) {
        for (j = i; j < G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/**
 * ��ӡ�±�
 */
void PrintIndex() {
    printf(" index: ");
    for (int i = 0; i < 9; ++i) {
        printf("\t%d ", i);
    }
    printf("\n");
}

/**
 * ��ӡlowcost����
 * @param lowcost �汸����СȨֵ������
 */
void PrintLowcost(int lowcost[]) {
    printf("lowcost: ");
    for (int i = 0; i < 9; ++i) {
        printf("\t%d ", lowcost[i]);
    }
    printf("\n");
}

/**
 * ��ӡadjvex����
 * @param adjvex ��߶�Ӧ���������
 */
void PrintAdjvex(int adjvex[]) {
    printf("adjvex: ");
    for (int i = 0; i < 9; ++i) {
        printf("\t%d ", adjvex[i]);
    }
    printf("\n");
}

/**
 * Prim�㷨������С������
 * @param G ��С������
 */
void MiniSpanTree_Prim(MGraph G) {
    int min, k, i, j; // min�洢��Сֵ��k�����洢��Сֵ�±꣬i��j���ڱ���Ԫ��
    int adjvex[MAXVEX]; // �洢�����±�
    int lowcost[MAXVEX]; // ���涥���ߵ�Ȩֵ

    // ��ʼ����һ��ȨֵΪ0������v0������������lowcost��ֵΪ0����ʾ���±�Ķ����Ѽ���������
    lowcost[0] = 0;
    adjvex[0] = 0; // ��ʼ����һ�������±�Ϊ0

    // ���±�Ϊ0����Ķ�����б���
    for (i = 1; i < G.numNodes; i++) {
        lowcost[i] = G.arc[0][i]; // ����v0�����бߵ�Ȩֵ��������
        adjvex[i] = 0; // �����ʼ����Ϊv0���±�
    }

    // ���±�Ϊ0����Ķ�����б���
    for (i = 1; i < G.numNodes; i++) {
        min = INFINITY; // ��ʼ������ѭ���ı���СֵΪ����

        j = 1; // ��������v0����Ķ���
        k = 0; // ��¼��С�ߵ��±�

        // ѭ��ȫ������
        while (j < G.numNodes) {
            // Ȩֵ��Ϊ0��ȨֵΪ0��ʾ�Ѽ���������������С��min
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j]; // �õ�ǰȨֵ��Ϊ��Сֵ
                k = j; // ʹ��k��¼��ǰ��Сֵ���±�
            }
            j++; // j����ƶ�
        }

        PrintIndex(); // ��ӡ�±�
        PrintAdjvex(adjvex); // ��ӡadjvex����
        PrintLowcost(lowcost); // ��ӡlowcost����

        printf("��СȨΪ��%d����Ϊ��(%d, %d)\n\n", min, adjvex[k], k); // ��ӡ�붥�������ı���Ȩֵ��С�ı�
        lowcost[k] = 0; // ���õ�ǰ�����ȨֵΪ0����ʾ�ö������������

        // ���±�Ϊ0����Ķ�����б���
        for (j = 1; j < G.numNodes; j++) {
            // �Ա�������СȨֵ�Ķ���k������k�����ı߼���������
            // ֵ��Ϊ0��ȨֵΪ0��ʾ�Ѽ���������������С�ڶ�Ӧ�е�lowcost
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
                lowcost[j] = G.arc[k][j]; // ����С��Ȩֵ����lowcost����Ӧλ��
                adjvex[j] = k; // ��Ϊ�붥��k���������±�Ϊk�Ķ������adjvex
            }
        }

    }
}

int main() {
    MGraph G; // �ڽӾ���
    CreateMGraph(&G); // �����ڽӾ���
    MiniSpanTree_Prim(G); // Prim�㷨������С������

    return 0;
}