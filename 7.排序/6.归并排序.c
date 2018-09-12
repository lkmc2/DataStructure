// �鲢����
#include <stdio.h>
#include <malloc.h>

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
 * �������SR[i..m]��SR[m+1 .. n]�鲢Ϊ�����TR[i..n]
 * @param SR ��Ҫ���й鲢��˳���
 * @param TR �鲢���ֵ��˳���
 * @param i ����±�
 * @param m �м���±�
 * @param n �յ��±�
 */
void Merge(int SR[], int TR[], int i, int m, int n) {
    int j, k, t;

    // ���αȽ�SR��ǰ�벿�ֺͺ�벿�ֶ�Ӧ�±��ֵ������TR��
    for (j = m + 1, k = i; i <= m && j <= n; k++) {
        // ǰ�벿�ֵĶ�Ӧλ�õ�ֵС�ں�벿��
        if (SR[i] < SR[j]) {
            TR[k] = SR[i++]; // ��ǰ�벿�ֵĶ�Ӧλ�õ�ֵ����TR
        } else { // ��벿�ֵĶ�Ӧλ�õ�ֵС��ǰ�벿��
            TR[k] = SR[j++]; // ����벿�ֵĶ�Ӧλ�õ�ֵ����TR
        }
    }

    // ��ʣ���SR[i..m]���Ƶ�TR
    if (i <= m) {
        for (t = 0; t <= m - i; t++) {
            TR[k + t] = SR[i + t];
        }
    }

    // ��ʣ���SR[j..n]���Ƶ�TR
    if (j <= n) {
        for (t = 0; t <= n - j; t++) {
            TR[k + t] = SR[j + t];
        }
    }
}

/************** �鲢���򣨵ݹ�棩**************/

/**
 * �鲢����
 * @param SR ��Ҫ�鲢��˳���
 * @param TR1 �洢�鲢���ֵ��˳���
 * @param s ����±�
 * @param t �յ��±�
 */
void MSort(int SR[], int TR1[], int s, int t) {
    int m;
    int TR2[N + 1]; // �洢˳����е���ʱ����

    // ���ֻʣһ��Ԫ��
    if (s == t) {
        TR1[s] = SR[s]; // ��SR��s�±��ֵ��ֵ��TR1
    } else {
        m = (s + t) / 2; // ����м���±�
        MSort(SR, TR2, s, m); // ��˳����ǰ�벿�ֵݹ�����
        MSort(SR, TR2, m + 1, t); // ��˳���ĺ�벿�ֵݹ�����
        Merge(TR2, TR1, s, m, t); // �ϲ�ǰ�벿�ֺͺ�벿�ֵ�ֵ������TR1��
    }
}

/**
 * ���ù鲢����
 * @param L ˳���
 */
void MergeSort(SqList *L) {
    MSort(L->value, L->value, 1, L->length); // ������˳�����й鲢����
}

/***********************************************/

/************** �鲢���򣨷ǵݹ�棩**************/

/**
 * �鲢���򣨷ǵݹ飩
 * @param SR ��Ҫ�鲢��˳���
 * @param TR1 �洢�鲢���ֵ��˳���
 * @param s ����±�
 * @param t �յ��±�
 */
void MergePass(int SR[], int TR[], int s, int n) {
    int i = 1;
    int j;

    while (i <= n - 2 * s + 1) {
        // �������������鲢
        Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
        i = i + 2 * s; // �����г��ȼӱ�
    }

    if (i < n - s + 1) {
        // �鲢�������������
        Merge(SR, TR, i, i + s - 1, n);
    } else {
        // �����ֻʣ�µ��������У�ֱ�ӽ�ֵ��ֵ��TR
        for (j = i; j <= n; j++) {
            TR[j] = SR[j];
        }
    }
}

/**
 * ���ù鲢���򣨷ǵݹ飩
 * @param L ˳���
 */
void MergeSort2(SqList *L) {
    int k = 1; // ������¼�����г���
    int *TR = (int *) malloc(L->length * sizeof(int)); // ����洢�ռ�

    while (k < L->length) {
        // ��L->value��ֵ�鲢��TR��
        MergePass(L->value, TR, k, L->length);
        k = 2 * k; // �����г��ȼӱ�

        // ��TR��ֵ�鲢��L->value��
        MergePass(TR, L->value, k, L->length);
        k = 2 * k; // �����г��ȼӱ�
    }
}

/***********************************************/

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // ���ʼֵ������
    SqList L; // ˳���

    InitSqList(&L, d); // ��ʼ��˳���
    printf("�ڽ��г�ʼ��֮��");
    Print(L); // ����˳���

    MergeSort(&L); // ��˳�����й鲢����
    printf("�鲢����(�ݹ�)��");
    Print(L); // ����˳���

    InitSqList(&L, d); // ��ʼ��˳���
    MergeSort2(&L); // ��˳�����й鲢����
    printf("�鲢����(�ǵݹ�)");
    Print(L); // ����˳���

    return 0;
}