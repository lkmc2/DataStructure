// 简单选择排序
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
 * 简单选择排序
 * @param L 顺序表
 */
void SelectSort(SqList *L) {
    int i, j;
    int min; // 用来记录每轮循环获取的最小值的下标

    for (i = 1; i < L->length; i++) {
        min = i; // 设置本轮最小值元素的下标

        for (j = i + 1; j < L->length; j++) {
            if (L->value[min] > L->value[j]) { // 如果当前元素的值小于最小值元素
                min = j; // 记录当前元素的下标
            }
        }

        // 本轮最小值元素的下标不等于初始值，代表有比初始值更小的元素
        if (i != min) {
            swap(L, i, min); // 将本轮的最小值交换的对应位置
        }
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // 存初始值的数组
    SqList L; // 顺序表

    InitSqList(&L, d); // 初始化顺序表
    printf("刚进行初始化后");
    Print(L); // 遍历顺序表

    SelectSort(&L); // 对顺序表进行简单选择排序
    printf("简单选择排序后");
    Print(L); // 遍历顺序表

    return 0;
}