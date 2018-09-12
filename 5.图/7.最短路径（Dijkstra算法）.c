// ���·����Dijkstra�㷨��
#include <stdio.h>

#define MAXVEX 20 // ��󶥵���
#define INFINITY 65535 // ����

typedef int Patharc[MAXVEX]; // ���ڴ洢���·��ǰ������±������
typedef int ShortPathTable[MAXVEX]; // ���ڴ洢���������·����Ȩֵ��

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
 * ���·��Dijkstra�㷨
 * ��������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����D[v]
 * P[v]��ֵΪǰ�������±꣬D[v]��ʾv0��v�����·�����Ⱥ�
 * @param G �ڽӾ���ͼ��
 * @param v0 ͼ����ʼ����
 * @param P �洢���·��ǰ���ڵ��±������
 * @param D �洢v0���������·����Ȩֵ�͵�����
 */
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D) {
    int v, w, k, min; // v��w��������Ԫ�أ�k��¼��СȨֵ�ڵ���±꣬min��¼��СȨֵ
    int final[MAXVEX]; // final[w]=1��ʾv0��vw�����·��

    // ��ʼ������
    for (v = 0; v < G.numNodes; v++) {
        final[v] = 0; // ȫ�������ʼ��Ϊλ�����·��״̬
        (*D)[v] = G.arc[v0][v]; // ��¼��v0�����ߵĶ����Ȩֵ
        (*P)[v] = -1; // ��ʼ��·������PΪ-1
    }

    (*D)[v0] = 0; // ����v0��v0·����ȨֵΪ0
    final[v0] = 1; // v0��v0����Ҫ��·��������Ϊ1

    // ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��
    for (v = 1; v < G.numNodes; v++) {
        min = INFINITY; // ��¼����ѭ������v0����ľ���

        // Ѱ����v0����Ķ���
        for (w = 0; w < G.numNodes; w++) {
            // final[w]Ϊ0��ʾ�ö��㻹û�м�¼��������Ķ���
            // final[w]Ϊ0�����Ҹö����ȨֵС������
            if (!final[w] && (*D)[w] < min) {
                k = w; // ��¼��СȨֵ���±�
                min = (*D)[w]; // ��¼��СȨֵ
            }
        }

        // ��Ŀǰ�ҵ�����ӽ�v0�Ķ�����±��λ����Ϊ1����ʾ�ö����ѱ���¼
        final[k] = 1;

        // ������ǰ���·��������
        for (w = 0; w < G.numNodes; w++) {
            // �������v�����·������������·���̵Ļ�
            if (!final[w] && (min + G.arc[k][w] < (*D)[w])) {
                (*D)[w] = min + G.arc[k][w]; // �޸Ķ���w����v0����̳���
                (*P)[w] = k; // �洢���·��ǰ���ڵ���±�
            }
        }
    }
}

/**
 * ��ӡ���·��
 * @param G �ڽӾ���ͼ��
 * @param v0 ͼ����ʼ����
 * @param P �洢���·��ǰ���ڵ��±������
 * @param D �洢v0���������·����Ȩֵ�͵�����
 */
void PrintShortPath(MGraph G, int v0, Patharc P, ShortPathTable D) {
    int i, j; // ���ڱ���Ԫ��

    printf("�洢���·��ǰ������±������P��ֵΪ��\n");
    printf("�����±꣺");
    for (i = 0; i < G.numNodes; i++) {
        printf("%2d ", i);
    }
    printf("\n�����ֵ��");
    for (i = 0; i < G.numNodes; i++) {
        printf("%2d ", P[i]);
    }

    /*
        �洢���·��ǰ������±������P��ֵΪ��
        �����±꣺ 0  1  2  3  4  5  6  7  8
        �����ֵ��-1 -1  1  4  2  4  3  6  7

        ��P[8] = 7ʱ��ʾ������8��ǰ������Ƕ���7��
        �ҵ�����7������P[7] = 6����ʾ����7��ǰ���ڵ��Ƕ���6��
        �����ɶ���8������0�����·��Ϊ��
        8 -> 7 -> 6 -> 3 -> 4 ->2 -> 1
        �����˳�򵹹������ɵõ�����0������8�����·��
     */

    printf("\n\n���·���������£�\n");
    for (i = 1; i < G.numNodes; i++) {
        printf("v%d - v%d : ", v0, i);
        j = i; // j���ڱ���whileѭ��

        while (P[j] != -1) { // P[j] = 1��ʾ�ö��㲻��ͨ
            printf("%d ", P[j]);
            j = P[j]; // ��ȡ��ö����������Ķ����±�
        }
        printf("\n");
    }

    printf("\nԭ��v%d������������·������Ϊ��\n", v0);
    for (i = 1; i < G.numNodes; i++) {
        // D�����д�v0������������·����
        printf("v%d - v%d : %d \n", G.vexs[0], G.vexs[i], D[i]);
    }
}

int main() {
    int v0; // ͼ����ʼ�����±�
    MGraph G; // �ڽӾ���ͼ��
    Patharc P; // ���ڴ洢���·��ǰ������±������
    ShortPathTable D; // ���ڴ洢���������·����Ȩֵ��

    v0 = 0; // ��0�±�Ķ�������Ϊͼ�����

    CreateMGraph(&G); // ��ʼ���ڽӾ���ͼ��
    ShortestPath_Dijkstra(G, v0, &P, &D); // ��ͼ�����·��
    PrintShortPath(G, v0, P, D); // ��ӡ���·��

    return 0;
}