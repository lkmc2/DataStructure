// ��������
#include <stdio.h>
#include <malloc.h>

#define N 10 // �������ֵ
#define MAX_LENGTH_INSERT_SORT 7 // ���ڿ�������ʱ�ж��Ƿ�ѡ�ò���������ֵ

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

/************** �������� **************/

/**
 * ��˳�����зָʹ�ڹؼ���ǰ���Ԫ�ض��������������Ԫ�ض�С����
 * @param L ˳���
 * @param low ����±�
 * @param high �յ��±�
 * @return �ָ�������ֺ󣬹ؼ��ֵ��±�
 */
int Partition(SqList *L, int low, int high) {
    int pivotkey; // �洢�ؼ���

    pivotkey = L->value[low]; // ���ùؼ���Ϊ��Сֵ

    while (low < high) { // ��λ�±�С�ڸ�λ�±�
        // ��λ�±�С�ڸ�λ�±꣬���Ҹ�λԪ�ص�ֵ���ڵ��ڹؼ���
        while (low < high && L->value[high] >= pivotkey) {
            high--; // ��λ�±���ǰ�ƶ�
        }
        swap(L, low, high); // ���ȹؼ���С��Ԫ�ص�ֵ�ŵ�ǰ��low��λ��

        // ��λ�±�С�ڸ�λ�±꣬���ҵ�λԪ�ص�ֵС�ڵ��ڹؼ���
        while (low < high && L->value[low] <= pivotkey) {
            low++; // ��λ����ƶ�
        }
        swap(L, low, high); // ���ȹؼ��ִ��Ԫ�ص�ֵ�ŵ�����high��λ��
    }
    return low; // ���عؼ��ֵ��±�
}

/**
 * ��������
 * @param L ˳���
 * @param low ����±�
 * @param high �յ��±�
 */
void QSort(SqList *L, int low, int high) {
    int pivot; // �洢�ָ�ؼ����±�

    // ��λС�ڸ�λ
    if (low < high) {
        pivot = Partition(L, low, high); // ��L->value[low..high]һ��Ϊ������ȡ�ؼ����±�
        QSort(L, low, pivot - 1); // ��ǰ�벿�ֵݹ�����
        QSort(L, pivot + 1, high); // �Ժ�벿�ֵݹ�����
    }
}

/**
 * ���ÿ�������
 * @param L ˳���
 */
void QuickSort(SqList *L) {
    QSort(L, 1, L->length); // ������˳�����п�������
}

/**************************************/

/************** �������򣨸Ľ��棩 **************/

/**
 * ��˳�����зָʹ�ڹؼ���ǰ���Ԫ�ض��������������Ԫ�ض�С����
 * @param L ˳���
 * @param low ����±�
 * @param high �յ��±�
 * @return �ָ�������ֺ󣬹ؼ��ֵ��±�
 */
int Partition2(SqList *L, int low, int high) {
    int pivotkey; // �洢�ؼ���

    int mid = low + (high - low) / 2; // �����м�λ�õ��±�

    // ʹ������ȡ�з���ȡ���ʺϵĹؼ��֣���������ߡ��м䡢���ұ�λ�õ�ֵ��ȡ�м������
    if (L->value[low] > L->value[high]) {
        swap(L, low, high); // ��������ߺ����ұ�Ԫ�أ���֤��߽�С
    }
    if (L->value[mid] > L->value[high]) {
        swap(L, mid, high); // �����м�����ұ�Ԫ�أ���֤�м��С
    }
    if (L->value[mid] < L->value[low]) {
        swap(L, mid, low); // �����м�������Ԫ�أ���֤��߽�С
    }

    pivotkey = L->value[low]; // ���ùؼ���Ϊ�������е���Сֵ
    L->value[0] = pivotkey; // ���ݹؼ��ֵ�0�±�λ��

    while (low < high) { // ��λ�±�С�ڸ�λ�±�
        // ��λ�±�С�ڸ�λ�±꣬���Ҹ�λԪ�ص�ֵ���ڵ��ڹؼ���
        while (low < high && L->value[high] >= pivotkey) {
            high--; // ��λ�±���ǰ�ƶ�
        }
        L->value[low] = L->value[high]; // ���ȹؼ���С��Ԫ�ص�ֵ�ŵ�ǰ��low��λ��

        // ��λ�±�С�ڸ�λ�±꣬���ҵ�λԪ�ص�ֵС�ڵ��ڹؼ���
        while (low < high && L->value[low] <= pivotkey) {
            low++; // ��λ����ƶ�
        }
        L->value[high] = L->value[low]; // ���ȹؼ��ִ��Ԫ�ص�ֵ�ŵ�����high��λ��
    }

    L->value[low] = L->value[0]; // ���ؼ��ִ浽���±�λ��
    return low; // ���عؼ��ֵ��±�
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

/**
 * �������򣨸Ľ��棩
 * @param L ˳���
 * @param low ����±�
 * @param high �յ��±�
 */
void QSort2(SqList *L, int low, int high) {
    int pivot; //�洢�ؼ���

    // �ߵ�λ֮�����ָ��ֵ�����ÿ�������
    if ((high - low) > MAX_LENGTH_INSERT_SORT) {
        // ��λ�±�С�ڸ�λ�±�
        while (low < high) {
            // ��L->value[low..high]һ��Ϊ������ȡ�ؼ����±�
            pivot = Partition2(L, low, high);
            QSort2(L, low, pivot - 1); // ��ǰ�벿�ֽ��еݹ�����
//            QSort2(L, pivot + 1, high); // �Ժ�벿�ֽ��еݹ�����
            low = pivot + 1; // β�ݹ�
        }
    } else { // �ߵ�λԪ��֮���С�����ò�������
        InsertSort(L); // ��������
    }
}

/**
 * ���ÿ������򣨸Ľ��棩
 * @param L ˳���
 */
void QuickSort2(SqList *L) {
    QSort2(L, 1, L->length); // ������˳�����п�������
}

/************************************************/

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // ���ʼֵ������
    SqList L; // ˳���

    InitSqList(&L, d); // ��ʼ��˳���
    printf("�ڽ��г�ʼ��֮��");
    Print(L); // ����˳���

    QuickSort(&L); // ��˳�����п�������
    printf("��������(��ͨ)��");
    Print(L); // ����˳���

    InitSqList(&L, d); // ��ʼ��˳���
    QuickSort2(&L); // ��˳�����п�������
    printf("��������(�Ľ���)");
    Print(L); // ����˳���

    return 0;
}