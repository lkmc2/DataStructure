// ��С����������³˹�����㷨��
#include <stdio.h>

#define MAXVEX 20 // ��󶥵���
#define MAXEDGE 20 // ������
#define INFINITY 65535 // ����

typedef int EdgeType; // ���ϵ�Ȩֵ����

// �ڽӾ���ṹ
typedef struct {
    EdgeType arc[MAXVEX][MAXVEX]; // �߱�
    int numNodes, numEdges; // ͼ�е�ǰ�Ķ�����������
}MGraph;

// �߼�����ڵ�
typedef struct {
    int begin; // �ߵ����
    int end; // �ߵ��յ�
    int weight; // �ߵ�Ȩֵ
} Edge;

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

    G->arc[2][8] = 8;
    G->arc[2][3] = 22;

    G->arc[3][8] = 21;
    G->arc[3][6] = 24;
    G->arc[3][7] = 16;
    G->arc[3][4] = 20;

    G->arc[4][7] = 7;
    G->arc[4][5] = 26;

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
 * �����߼�����ڵ���i��jλ�õ�Ȩֵ���Լ������յ�
 * @param edges �߼�����ڵ�
 * @param i �±�
 * @param j �±�
 */
void Swapn(Edge *edges, int i, int j) {
    int temp; // ���ڽ�������ʱ����
    
    // ����i��jλ�õ����
    temp = edges[i].begin;
    edges[i].begin = edges[j].begin; 
    edges[j].begin = temp;
    
    // ����i��jλ�õ��յ�
    temp = edges[i].end;
    edges[i].end = edges[j].end;
    edges[j].end = temp;

    // ����i��jλ�õ�Ȩֵ
    temp = edges[i].weight;
    edges[i].weight = edges[j].weight;
    edges[j].weight = temp;
}

/**
 * �Ա߼������Ȩֵ��������
 * @param edges �߼�����
 * @param G �ڽӾ���
 */
void sort(Edge edges[], MGraph *G) {
    int i, j; // ��������Ԫ��

    // ʹ��ð������Ա߼������������
    for (i = 0; i < G->numEdges; i++) {
        for (j = i + 1; j < G->numEdges; j++) {
            // ǰ��ڵ�Ⱥ���ڵ��Ȩֵ��
            if (edges[i].weight > edges[j].weight) {
                // �����ڵ�i�ͽڵ�j
                Swapn(edges, i, j);
            }
        }
    }

    printf("Ȩ����֮���ֵΪ��\n");
    for (i = 0; i < G->numEdges; i++) {
        printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
    }
}

/**
 * �������߶����β���±�
 * @param parent �жϱ�����Ƿ��γɻ�·������
 * @param f �����±�
 * @return ������Ƿ��γɻ�·������
 */
int Find(int *parent, int f) {
    // ��parent[f]��Ϊ0ʱ����ʾ�ñ���������������
    // һֱ˳�������ı�ֱ��һ�����������������ıߣ�parent[f] = 0��
    // ���ظñߵĶ����±�
    while (parent[f] > 0) {
        f = parent[f];
    }
    return f;
}

/**
 * ʹ��Kruskal�㷨������С������
 * @param G �ڽӾ���
 */
void MiniSpanTree_Kruskal(MGraph G) {
    int i, j, m, n; // i��j��������Ԫ�أ�m��n������ȡ
    int k = 0; // ���������߼�������±�
    int parent[MAXVEX]; // �жϱ�����Ƿ��γɻ�·������
    Edge edges[MAXEDGE]; // �߼�����

    // ʹ���ڽӾ����������߼�����
    for (i = 0; i < G.numNodes - 1; i++) {
        for (j = i + 1; j < G.numNodes; j++) {
            if (G.arc[i][j] < INFINITY) {
                edges[k].begin = i; // ���ñ߼�����ڵ�����
                edges[k].end = j; // ���ýڵ���յ�
                edges[k].weight = G.arc[i][j]; // ���ýڵ��Ȩֵ
                k++; // ���������߼�����
            }
        }
    }

    sort(edges, &G); // �Ա߼������Ȩֵ��������

    // ��ʼ���жϱ�����Ƿ��γɻ�·������
    for (i = 0; i < G.numNodes; i++) {
        parent[i] = 0; // ��������������ֵ��Ϊ0
    }

    printf("��ӡ��С��������\n");
    // ѭ��ÿһ����
    for (i = 0; i < G.numEdges; i++) {
        n = Find(parent, edges[i].begin); // ��ȡ��ö����������һ��������±�
        m = Find(parent, edges[i].end);

        // n��m����ȣ�˵���˱�û�к������������γɻ�·
        if (n != m) {
            parent[n] = m; // ���˱ߵĽ�β�������parent���飬��ʾ�˶����Ѿ���������������

            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }

}

int main() {
    MGraph G; // �ڽӾ���
    CreateMGraph(&G); // �����ڽӾ���
    MiniSpanTree_Kruskal(G); // Kruskal�㷨������С������

    return 0;
}