// ���·����Floyd�㷨��
#include <stdio.h>

#define MAXVEX 20 // ��󶥵���
#define INFINITY 65535 // ����

typedef int Patharc[MAXVEX][MAXVEX]; // ���ڴ洢���v��������������·��
typedef int ShortPathTable[MAXVEX][MAXVEX]; // ���ڴ洢���v����������Ĵ�Ȩ����

// �ڽӾ���ṹ
typedef struct {
    int vexs[MAXVEX]; // �����
    int arc[MAXVEX][MAXVEX]; // �߱�
    int numNodes, numEdges; // ͼ�е�ǰ�Ķ�����������
} MGraph;

/**
 * �����ڽӾ���ͼ��
 * @param G �ڽӾ���ͼ��
 */
void CreateMGraph(MGraph *G) {
    int i, j; // ���ڱ���Ԫ��

    G->numEdges = 16; // ������16����
    G->numNodes = 9; // ������9������

    // ��ʼ��ͼ�Ķ���
    for (i = 0; i < G->numNodes; i++) {
        G->vexs[i] = i;
    }

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
    G->arc[0][1]=1;
    G->arc[0][2]=5;

    G->arc[1][2]=3;
    G->arc[1][3]=7;
    G->arc[1][4]=5;

    G->arc[2][4]=1;
    G->arc[2][5]=7;

    G->arc[3][4]=2;
    G->arc[3][6]=3;

    G->arc[4][5]=3;
    G->arc[4][6]=6;
    G->arc[4][7]=9;

    G->arc[5][7]=5;

    G->arc[6][7]=2;
    G->arc[6][8]=7;

    G->arc[7][8]=4;

    // ���öԳƱߵ�Ȩ
    for (i = 0; i < G->numNodes; i++) {
        for (j = i; j < G->numNodes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/**
 * ���·��Floyd�㷨
 * @param G �ڽӾ���ͼ��
 * @param P ��洢���v��������������·��������
 * @param D ��洢���v����������Ĵ�Ȩ���ȵ�����
 */
void ShortestPath_Floyd(MGraph G, Patharc *P, ShortPathTable *D) {
    int v, w, k; // ��������Ԫ��

    // ��ʼ��D��P
    for (v = 0; v < G.numNodes; v++) {
        for (w = 0; w < G.numNodes; w++) {
            (*D)[v][w] = G.arc[v][w]; // �洢��Ӧ�ߵ�Ȩֵ
            (*P)[v][w] = w; // ���ø��е�ֵΪ���е��±�
        }
    }

    for (k = 0; k < G.numNodes; k++) {
        for (v = 0; v < G.numNodes; v++) {
            for (w = 0; w < G.numNodes; w++) {
                // ����±��±�Ϊk�Ķ����·����ԭ�����·������
                // ���D[1][3] > D[1][2] + D[2][3]
                if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
                    // ����ǰ�����Ȩֵ����Ϊͨ���м��k��·����Ȩֵ
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    // ·������Ϊ�����±�Ϊk�Ķ���
                    (*P)[v][w] = (*P)[v][k];
                }
            }
        }
    }
}

/**
 * ��ӡ���·��
 * @param G �ڽӾ���ͼ��
 * @param P �洢���·��ǰ���ڵ��±������
 * @param D �洢v0���������·����Ȩֵ�͵�����
 */
void PrintShortPath(MGraph G, Patharc P, ShortPathTable D) {
    int v, w, k; // ���ڱ���Ԫ��

    printf("����������·�����£�\n");
    for (v = 0; v < G.numNodes; v++) {
        for (w = v + 1; w < G.numNodes; w++) {
            printf("v%d-v%d weight: %2d ", v, w, D[v][w]);

            k = P[v][w]; // ��ȡ����v��w��Ȩֵ
            printf(" path: %d", v); // ��ӡ���

            while (k != w) { // ѭ��δ����ĩ�˶���
                printf(" -> %d", k); // ��ӡ·������
                k = P[k][w]; // ��ȡ��һ��·��������±�
            }
            printf(" -> %d\n", w); // ��ӡ�յ�
        }
        printf("\n");
    }
}

int main() {
    MGraph G; // �ڽӾ���ͼ��
    Patharc P; // �洢���v��������������·��
    ShortPathTable D; // �洢���v����������Ĵ�Ȩ����

    CreateMGraph(&G); // ��ʼ���ڽӾ���ͼ��
    ShortestPath_Floyd(G, &P, &D); // ��ͼ�����·��
    PrintShortPath(G, P, D); // ��ӡ���·��

    return 0;
}