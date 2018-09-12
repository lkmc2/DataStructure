// 归并排序
#include <stdio.h>
#include <malloc.h>

#define N 10 // 数组最大值

// 顺序表结构
typedef struct {
    int value[N + 1]; // 顺序表中的值
    int length; // 顺序表长度
} SqList;

/**
 * 初始化顺序表
 * @param L 顺序表
 * @param d 存初始值的数组
 */
void InitSqList(SqList *L, int *d) {
    int i;

    for (i = 0; i < N; ++i) {
        L->value[i + 1] = d[i];
    }
    L->length = N;
}

/**
 * 遍历顺序表中元素的值
 * @param L 顺序表元素
 */
void Print(SqList L) {
    int i;

    printf("顺序表中的值为：");
    for (i = 1; i < L.length; i++) {
        printf("%d, ", L.value[i]);
    }
    printf("%d", L.value[i]);
    printf("\n");
}

/**
 * 将有序的SR[i..m]和SR[m+1 .. n]归并为有序的TR[i..n]
 * @param SR 需要进行归并的顺序表
 * @param TR 归并后存值的顺序表
 * @param i 起点下标
 * @param m 中间点下标
 * @param n 终点下标
 */
void Merge(int SR[], int TR[], int i, int m, int n) {
    int j, k, t;

    // 依次比较SR中前半部分和后半部分对应下标的值，存入TR中
    for (j = m + 1, k = i; i <= m && j <= n; k++) {
        // 前半部分的对应位置的值小于后半部分
        if (SR[i] < SR[j]) {
            TR[k] = SR[i++]; // 将前半部分的对应位置的值存入TR
        } else { // 后半部分的对应位置的值小于前半部分
            TR[k] = SR[j++]; // 将后半部分的对应位置的值存入TR
        }
    }

    // 将剩余的SR[i..m]复制到TR
    if (i <= m) {
        for (t = 0; t <= m - i; t++) {
            TR[k + t] = SR[i + t];
        }
    }

    // 将剩余的SR[j..n]复制到TR
    if (j <= n) {
        for (t = 0; t <= n - j; t++) {
            TR[k + t] = SR[j + t];
        }
    }
}

/************** 归并排序（递归版）**************/

/**
 * 归并排序
 * @param SR 需要归并的顺序表
 * @param TR1 存储归并后的值的顺序表
 * @param s 起点下标
 * @param t 终点下标
 */
void MSort(int SR[], int TR1[], int s, int t) {
    int m;
    int TR2[N + 1]; // 存储顺序表中的临时数组

    // 如果只剩一个元素
    if (s == t) {
        TR1[s] = SR[s]; // 将SR的s下标的值赋值给TR1
    } else {
        m = (s + t) / 2; // 求出中间点下标
        MSort(SR, TR2, s, m); // 对顺序表的前半部分递归排序
        MSort(SR, TR2, m + 1, t); // 对顺序表的后半部分递归排序
        Merge(TR2, TR1, s, m, t); // 合并前半部分和后半部分的值并排序到TR1中
    }
}

/**
 * 调用归并排序
 * @param L 顺序表
 */
void MergeSort(SqList *L) {
    MSort(L->value, L->value, 1, L->length); // 对整个顺序表进行归并排序
}

/***********************************************/

/************** 归并排序（非递归版）**************/

/**
 * 归并排序（非递归）
 * @param SR 需要归并的顺序表
 * @param TR1 存储归并后的值的顺序表
 * @param s 起点下标
 * @param t 终点下标
 */
void MergePass(int SR[], int TR[], int s, int n) {
    int i = 1;
    int j;

    while (i <= n - 2 * s + 1) {
        // 将子序列两两归并
        Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
        i = i + 2 * s; // 子序列长度加倍
    }

    if (i < n - s + 1) {
        // 归并最后两个子序列
        Merge(SR, TR, i, i + s - 1, n);
    } else {
        // 若最后只剩下单个子序列，直接将值赋值给TR
        for (j = i; j <= n; j++) {
            TR[j] = SR[j];
        }
    }
}

/**
 * 调用归并排序（非递归）
 * @param L 顺序表
 */
void MergeSort2(SqList *L) {
    int k = 1; // 用来记录子序列长度
    int *TR = (int *) malloc(L->length * sizeof(int)); // 申请存储空间

    while (k < L->length) {
        // 将L->value的值归并到TR中
        MergePass(L->value, TR, k, L->length);
        k = 2 * k; // 子序列长度加倍

        // 将TR的值归并回L->value中
        MergePass(TR, L->value, k, L->length);
        k = 2 * k; // 子序列长度加倍
    }
}

/***********************************************/

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // 存初始值的数组
    SqList L; // 顺序表

    InitSqList(&L, d); // 初始化顺序表
    printf("在进行初始化之后");
    Print(L); // 遍历顺序表

    MergeSort(&L); // 对顺序表进行归并排序
    printf("归并排序(递归)后");
    Print(L); // 遍历顺序表

    InitSqList(&L, d); // 初始化顺序表
    MergeSort2(&L); // 对顺序表进行归并排序
    printf("归并排序(非递归)");
    Print(L); // 遍历顺序表

    return 0;
}