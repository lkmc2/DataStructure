// ֱ�Ӳ�������
#include <stdio.h>

#define N 10 // �������ֵ

// ˳���ṹ
typedef struct {
    int value[N + 1]; // ˳����е�ֵ
    int length; // ˳�����
} SqList;

/**
 * ��ʼ��˳���
 * @param L ˳���
 * @param d ���ʼֵ������
 */
void InitSqList(SqList *L, int *d) {
    int i;

    for (i = 0; i < N; ++i) {
        L->value[i + 1] = d[i];
    }
    L->length = N;
}

/**
 * ����˳�����Ԫ�ص�ֵ
 * @param L ˳���Ԫ��
 */
void Print(SqList L) {
    int i;

    printf("˳����е�ֵΪ��");
    for (i = 1; i < L.length; i++) {
        printf("%d, ", L.value[i]);
    }
    printf("%d", L.value[i]);
    printf("\n");
}

/**
 * ֱ�Ӳ�������
 * @param L ˳���
 */
void InsertSort(SqList *L) {
    int i, j;

    for (i = 2; i <= L->length; i++) {
        // �����Ԫ�ر�ǰ��Ԫ��С���轫L->value[i]���������ӱ�
        if (L->value[i] < L->value[i - 1]) {
            L->value[0] = L->value[i]; // �����ڱ�

            // �������ӱ��У����ڱ�λ��Ԫ�ش��Ԫ�ض�����ƶ�һ��λ��
            for (j = i - 1; L->value[j] > L->value[0]; j--) {
                L->value[j + 1] = L->value[j];
            }
            // ���ڱ�λ�õ�Ԫ�ز�����ȷ��λ��
            L->value[j + 1] = L->value[0];
        }
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // ���ʼֵ������
    SqList L; // ˳���

    InitSqList(&L, d); // ��ʼ��˳���
    printf("�ս��г�ʼ����");
    Print(L); // ����˳���

    InsertSort(&L); // ��˳������ֱ�Ӳ�������
    printf("ֱ�Ӳ��������");
    Print(L); // ����˳���

    return 0;
}