// ð������
#include <stdio.h>

#define TRUE 1 // ��
#define FALSE 0 // ��

#define N 10 // �������ֵ
typedef int Status; // �������ؽ������

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
 * ð�����򣨳����棩
 * ��˳�����ǰ��������ʼ���Ƚϣ�ÿһ�����򶼽�ȷ����NСԪ�ص�λ��
 * @param L ˳���
 */
void BubbleSort0(SqList *L) {
    int i, j;

    for (i = 1; i < L->length; i++) {
        for (j = i + 1; j < L->length; j++) {
            if (L->value[i] > L->value[j]) { // �������ǰ���Ԫ�رȺ����Ԫ�ش�
                swap(L, i, j); // ����������Ԫ�ص�λ��
            }
        }
    }
}

/**
 * ð��������ʽ�棩
 * ��˳��������������ʼ��ǰ�Ƚϣ�ÿһ�����򶼽�ȷ����NСԪ�ص�λ��
 * @param L ˳���
 */
void BubbleSort(SqList *L) {
    int i, j;

    for (i = 1; i < L->length; i++) {
        for (j = L->length - 1; j >= i; j--) {
            if (L->value[j] > L->value[j + 1]) { // �������ǰ���Ԫ�رȺ����Ԫ�ش�
                swap(L, j, j + 1); // ����������Ԫ�ص�λ��
            }
        }
    }
}

/**
 * ð�����򣨸Ľ��㷨��
 * ��˳��������������ʼ��ǰ�Ƚϣ�ÿһ�����򶼽�ȷ����NСԪ�ص�λ��
 * ���ĳ������û�н������������������Ч�ʱ�ð�������
 * @param L
 */
void BubbleSort2(SqList *L) {
    int i, j;
    Status flag = TRUE; // ָʾÿһѭ���Ƿ��н����ı��

    for (i = 1; i < L->length && flag; i++) {
        flag = FALSE; // ���ñ���ѭ��δ��������

        for (j = L->length - 1; j >= i; j--) {
            if (L->value[j] > L->value[j + 1]) { // �������ǰ���Ԫ�رȺ����Ԫ�ش�
                swap(L, j, j + 1); // ����������Ԫ�ص�λ��
                flag = TRUE; // ���ñ��ֽ��������ݽ���
            }
        }
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // ���ʼֵ������
    SqList L; // ˳���

    InitSqList(&L, d); // ��ʼ��˳���
    printf("�ս��г�ʼ����");
    Print(L); // ����˳���

    BubbleSort0(&L); // ��˳�����г���ð������
    printf("����ð�������");
    Print(L); // ����˳���

    InitSqList(&L, d); // ��ʼ��˳���
    BubbleSort(&L); // ��˳��������ʽð������
    printf("��ʽð�������");
    Print(L); // ����˳���

    InitSqList(&L, d); // ��ʼ��˳���
    BubbleSort2(&L); // ��˳�����иĽ�ð������
    printf("�Ľ�ð�������");
    Print(L); // ����˳���
}