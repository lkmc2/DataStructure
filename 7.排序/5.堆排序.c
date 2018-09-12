// 堆排序
#include <stdio.h>

#define N 10 // 数组最大值

// 顺序表结构
typedef struct {
    int value[N + 1]; // 顺序表中的值
    int length; // 顺序表长度
} SqList;

/**
 * 交换顺序表L中i和j元素的值
 * @param L 顺序表
 * @param i 元素值
 * @param j 元素值
 */
void swap(SqList *L, int i, int j) {
    int temp = L->value[i];
    L->value[i] = L->value[j];
    L->value[j] = temp;
}

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
 * @param L 顺序表
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
 * 已知L->[s..m]中的记录除L->value[s]以外均满足堆的定义
 * 调整L->value[s]的关键字，使L->value[s..m]成为一个大顶堆
 * @param L 顺序表
 * @param s 需要调整的元素下标
 * @param m 范围结束下标
 */
void HeapAdjust(SqList *L, int s, int m) {
    int temp, j;
    temp = L->value[s]; // 存储需要调整的元素的值

    // 沿s下标位置的孩子节点向下筛选
    for (j = 2 * s; j <= m; j *= 2) {
        // 左孩子小于右孩子的值
        if (j < m && L->value[j] < L->value[j + 1]) {
            j++; // 记录右孩子的下标（记录较大值的下标）
        }

        // 当树中较大值节点小于或等于temp元素的值，此时找到插入位置
        if (L->value[j] <= temp) {
            break;
        }

        // 元素向上移动，父节点等于左孩子或右孩子的值
        L->value[s] = L->value[j];
        s = j; // 记录下次循环时的父节点下标
    }
    L->value[s] = temp; // 将要调整元素的值插入堆中对应位置
}

/**
 * 堆排序
 * @param L 顺序表
 */
void HeapSort(SqList *L) {
    int i;

    // 将顺序表中的r构建成大顶堆
    for (i = L->length / 2; i > 0; i--) {
        HeapAdjust(L, i, L->length);
    }

    for (i = L->length; i > 1; i--) {
        swap(L, 1, i); // 将堆顶元素和未经子序列排序的最后一个元素交换
        HeapAdjust(L, 1, i - 1); // 将L->r[1..i-1]重新调整为大顶堆
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // 存初始值的数组
    SqList L; // 顺序表

    InitSqList(&L, d); // 初始化顺序表
    printf("进行初始化后");
    Print(L); // 遍历顺序表

    HeapSort(&L); // 对顺序表进行堆排序排序
    printf("堆排序排序后");
    Print(L); // 遍历顺序表

    return 0;
}