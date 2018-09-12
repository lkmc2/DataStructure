// ������
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
 * @param L ˳���
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
 * ��֪L->[s..m]�еļ�¼��L->value[s]���������ѵĶ���
 * ����L->value[s]�Ĺؼ��֣�ʹL->value[s..m]��Ϊһ���󶥶�
 * @param L ˳���
 * @param s ��Ҫ������Ԫ���±�
 * @param m ��Χ�����±�
 */
void HeapAdjust(SqList *L, int s, int m) {
    int temp, j;
    temp = L->value[s]; // �洢��Ҫ������Ԫ�ص�ֵ

    // ��s�±�λ�õĺ��ӽڵ�����ɸѡ
    for (j = 2 * s; j <= m; j *= 2) {
        // ����С���Һ��ӵ�ֵ
        if (j < m && L->value[j] < L->value[j + 1]) {
            j++; // ��¼�Һ��ӵ��±꣨��¼�ϴ�ֵ���±꣩
        }

        // �����нϴ�ֵ�ڵ�С�ڻ����tempԪ�ص�ֵ����ʱ�ҵ�����λ��
        if (L->value[j] <= temp) {
            break;
        }

        // Ԫ�������ƶ������ڵ�������ӻ��Һ��ӵ�ֵ
        L->value[s] = L->value[j];
        s = j; // ��¼�´�ѭ��ʱ�ĸ��ڵ��±�
    }
    L->value[s] = temp; // ��Ҫ����Ԫ�ص�ֵ������ж�Ӧλ��
}

/**
 * ������
 * @param L ˳���
 */
void HeapSort(SqList *L) {
    int i;

    // ��˳����е�r�����ɴ󶥶�
    for (i = L->length / 2; i > 0; i--) {
        HeapAdjust(L, i, L->length);
    }

    for (i = L->length; i > 1; i--) {
        swap(L, 1, i); // ���Ѷ�Ԫ�غ�δ����������������һ��Ԫ�ؽ���
        HeapAdjust(L, 1, i - 1); // ��L->r[1..i-1]���µ���Ϊ�󶥶�
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // ���ʼֵ������
    SqList L; // ˳���

    InitSqList(&L, d); // ��ʼ��˳���
    printf("���г�ʼ����");
    Print(L); // ����˳���

    HeapSort(&L); // ��˳�����ж���������
    printf("�����������");
    Print(L); // ����˳���

    return 0;
}