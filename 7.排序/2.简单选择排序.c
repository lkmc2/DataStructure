// ��ѡ������
#include <stdio.h>

#define N 10 // �������ֵ

// ˳���ṹ
typedef struct {
    int value[N + 1]; // ˳����е�ֵ
    int length; // ˳�����
} SqList;

/**
 * ����˳���L��i��jԪ�ص�ֵ
 * @param L ˳���
 * @param i Ԫ��ֵ
 * @param j Ԫ��ֵ
 */
void swap(SqList *L, int i, int j) {
    int temp = L->value[i];
    L->value[i] = L->value[j];
    L->value[j] = temp;
}

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
 * ��ѡ������
 * @param L ˳���
 */
void SelectSort(SqList *L) {
    int i, j;
    int min; // ������¼ÿ��ѭ����ȡ����Сֵ���±�

    for (i = 1; i < L->length; i++) {
        min = i; // ���ñ�����СֵԪ�ص��±�

        for (j = i + 1; j < L->length; j++) {
            if (L->value[min] > L->value[j]) { // �����ǰԪ�ص�ֵС����СֵԪ��
                min = j; // ��¼��ǰԪ�ص��±�
            }
        }

        // ������СֵԪ�ص��±겻���ڳ�ʼֵ�������бȳ�ʼֵ��С��Ԫ��
        if (i != min) {
            swap(L, i, min); // �����ֵ���Сֵ�����Ķ�Ӧλ��
        }
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // ���ʼֵ������
    SqList L; // ˳���

    InitSqList(&L, d); // ��ʼ��˳���
    printf("�ս��г�ʼ����");
    Print(L); // ����˳���

    SelectSort(&L); // ��˳�����м�ѡ������
    printf("��ѡ�������");
    Print(L); // ����˳���

    return 0;
}