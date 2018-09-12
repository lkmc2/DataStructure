// ��̬����
#include <stdio.h>

#define MAXSIZE 100 // ����洢�ռ��ʼ������

int F[100]; // 쳲���������

/**
 * ˳�����
 * @param a ����
 * @param n �������
 * @param key Ҫ���ҵĹؼ���
 * @return �ؼ����������е��±꣨����0��ʾδ�ҵ���Ԫ�أ�
 */
int Sequential_Search(int *a, int n, int key) {
    int i; // ��������Ԫ��

    for (i = 1; i <= n; i++) {
        if (a[i] == key) { // �����ĳ��Ԫ�ص��ڹؼ���
            return i; // ���ظ�Ԫ�ص��±�
        }
    }
    return 0;
}

/**
 * ���ڱ���˳�����
 * @param a ����
 * @param n �������
 * @param key Ҫ���ҵĹؼ���
 * @return �ؼ����������е��±꣨����0��ʾδ�ҵ���Ԫ�أ�
 */
int Sequential_Search_With_Guard(int *a, int n, int key) {
    int i; // ��������Ԫ��
    a[0] = key; // ���ؼ������õ������0��Ԫ�أ��ڱ���

    i = n; // i�ĳ�ʼֵ����Ϊ���鳤��

    while (a[i] != key) { // ��λ�õ�Ԫ�ز����ڹؼ���
        i--; // �����±���ǰ�ƶ�
    }
    return i; // ���عؼ��ֵ��±�
}

/**
 * ���ֲ��ң��۰���ң�
 * @param a ����
 * @param n �������
 * @param key Ҫ���ҵĹؼ���
 * @return �ؼ����������е��±꣨����0��ʾδ�ҵ���Ԫ�أ�
 */
int Binary_Search(int *a, int n, int key) {
    int low, high, mid; // ��ǰ���ҷ�Χ��С������м��±�

    low = 1; // ���ò��ҷ�Χ��С�±�Ϊ��������±꣨������0�±꣩
    high = n; // ���ò��ҷ�Χ����±�Ϊ�����յ��±�

    while (low <= high) {
        mid = (low + high) / 2; // ���м��±�

        if (key < a[mid]) { // �ؼ���С���м�λ���±��ֵ
            high = mid - 1; // ����±�����Ϊ�м��±��1
        } else if (key > a[mid]) { // �ؼ��ִ����м�λ���±��ֵ
            low = mid + 1;  // ��С�±�����Ϊ�м��±��1
        } else { // �ؼ��ֵ����м�λ���±��ֵ
            return mid; // ���ظ�λ���±�
        }
    }
    return 0;
}

/**
 * ��ֵ���ң��ڶ��ֲ��һ����Ͻ���mid�Ĺ��̻��ɲ�ֵ��ʽ��
 * @param a ����
 * @param n �������
 * @param key Ҫ���ҵĹؼ���
 * @return �ؼ����������е��±꣨����0��ʾδ�ҵ���Ԫ�أ�
 */
int Interpolation_Search(int *a, int n, int key) {
    int low, high, mid; // ��ǰ���ҷ�Χ��С������м��±�

    low = 1; // ���ò��ҷ�Χ��С�±�Ϊ��������±꣨������0�±꣩
    high = n; // ���ò��ҷ�Χ����±�Ϊ�����յ��±�

    while (low <= high) {
        // ��ֵ��ʽ���м�ֵ�±�
        mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]);

        if (key < a[mid]) { // �ؼ���С���м�λ���±��ֵ
            high = mid - 1; // ����±�����Ϊ�м��±��1
        } else if (key > a[mid]) { // �ؼ��ִ����м�λ���±��ֵ
            low = mid + 1;  // ��С�±�����Ϊ�м��±��1
        } else { // �ؼ��ֵ����м�λ���±��ֵ
            return mid; // ���ظ�λ���±�
        }
    }
    return 0;
}

/**
 * 쳲��������ң��ڶ��ֲ��һ����Ͻ���mid�Ĺ��̻�������쳲�����������ֵ��
 * @param a ����
 * @param n �������
 * @param key Ҫ���ҵĹؼ���
 * @return �ؼ����������е��±꣨����0��ʾδ�ҵ���Ԫ�أ�
 */
int Fibonacci_Search(int *a, int n, int key) {
    int low, high, mid; // ��ǰ���ҷ�Χ��С������м��±�
    int i, k = 0; // i��������Ԫ�أ�k������λ��쳲��������е�λ��

    low = 1; // ���ò��ҷ�Χ��С�±�Ϊ��������±꣨������0�±꣩
    high = n; // ���ò��ҷ�Χ����±�Ϊ�����յ��±�

    while (n > F[k] - 1) { // ����nλ��쳲��������е�λ��
        k++;
    }
    for (i = n; i < F[k] - 1; i++) { // ����������ֵ��ȫ
        a[i] = a[n];
    }

    while (low <= high) {
        mid = low + F[k - 1] - 1; // ���м�ֵ�±�

        if (key < a[mid]) { // �ؼ���С���м�λ���±��ֵ
            high = mid - 1; // ����±�����Ϊ�м��±��1
            k = k - 1;
        } else if (key > a[mid]) { // �ؼ��ִ����м�λ���±��ֵ
            low = mid + 1;  // ��С�±�����Ϊ�м��±��1
            k = k - 2;
        } else { // �ؼ��ֵ����м�λ���±��ֵ
            if (mid <= n) {
                return mid;  // �������˵��midΪ�ҵ���λ��
            } else {
                return n; // mid > n˵���ǲ�ȫ���֣�����n
            }
        }
    }
    return 0;
}

int main() {
    int i, result;
    int arr[MAXSIZE] = {0, 1, 15, 27, 36, 49, 53, 61, 73, 84, 99};

    result = Sequential_Search(arr, 10, 73); // ˳�����
    printf("˳����ҵĽ��Ϊ��%d\n", result);

    result = Sequential_Search_With_Guard(arr, 10, 73); // ���ڱ���˳�����
    printf("���ڱ���˳����ҵĽ��Ϊ��%d\n", result);

    result = Binary_Search(arr, 10, 73); // ���ֲ���
    printf("���ֲ��ҽ��Ϊ��%d\n", result);

    result = Interpolation_Search(arr, 10, 73); // ��ֵ����
    printf("��ֵ���ҽ��Ϊ��%d\n", result);

    /********** ��ʼ��쳲��������� **********/
    F[0] = 0;
    F[1] = 1;

    for (i = 2; i < MAXSIZE; i++) {
        F[i] = F[i - 1] + F[i - 2];
    }
    /***************************************/

    result = Fibonacci_Search(arr, 10, 73); // 쳲���������
    printf("쳲��������ҽ��Ϊ��%d\n", result);

    return 0;
}