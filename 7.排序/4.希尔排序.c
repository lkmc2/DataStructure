// ϣ������
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
 * ϣ������
 * @param L ˳���
 */
void ShellSort(SqList *L) {
    int i, j;
    int k = 0; // ͳ�Ʊ�������
    int increment = L->length; // ��������

    do {
        increment = increment / 3 + 1; // ������������Ϊԭ��������֮һ���������4��

        for (i = increment + 1; i <= L->length; i++) {
            // �Ƚϵ�5���͵�(5 - 4) = 1��Ԫ�أ�����5��Ԫ�رȵ�1��Ԫ�ص�ֵС
            if (L->value[i] < L->value[i - increment]) {
                L->value[0] = L->value[i]; // ��5λ�õ�ֵ�ݴ���0λ��

                // j = 5 - 4 = 1����0Ԫ�ص�ֵС��1Ԫ�أ���ʱ������������
                for (j = i - increment; j > 0 && L->value[0] < L->value[j]; j -= increment) {
                    // ��5Ԫ�ص�ֵ��ֵΪ1Ԫ�ص�ֵ����¼���ƣ��ҵ�����0Ԫ�ز����λ�ã�
                    L->value[j + increment] = L->value[j];
                }

                // ��0Ԫ�ص�ֵ���뵽���ʵ�λ�ã�5Ԫ�أ�
                L->value[j + increment] = L->value[0];
            }
        }
        printf("��%d������֮��,", ++k);
        Print(*L); // ����˳���
    } while (increment > 1);
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // ���ʼֵ������
    SqList L; // ˳���

    InitSqList(&L, d); // ��ʼ��˳���
    printf("�ս��г�ʼ����");
    Print(L); // ����˳���

    ShellSort(&L); // ��˳������ϣ������
    printf("ϣ�����������");
    Print(L); // ����˳���

    return 0;
}