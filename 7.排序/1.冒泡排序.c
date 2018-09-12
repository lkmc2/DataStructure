// 冒泡排序
#include <stdio.h>

#define TRUE 1 // 真
#define FALSE 0 // 假

#define N 10 // 数组最大值
typedef int Status; // 函数返回结果类型

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
 * 冒泡排序（初级版）
 * 从顺序表最前面两个开始向后比较，每一轮排序都将确定第N小元素的位置
 * @param L 顺序表
 */
void BubbleSort0(SqList *L) {
    int i, j;

    for (i = 1; i < L->length; i++) {
        for (j = i + 1; j < L->length; j++) {
            if (L->value[i] > L->value[j]) { // 如果表中前面的元素比后面的元素大
                swap(L, i, j); // 交互这两个元素的位置
            }
        }
    }
}

/**
 * 冒泡排序（正式版）
 * 从顺序表最后面两个开始向前比较，每一轮排序都将确定第N小元素的位置
 * @param L 顺序表
 */
void BubbleSort(SqList *L) {
    int i, j;

    for (i = 1; i < L->length; i++) {
        for (j = L->length - 1; j >= i; j--) {
            if (L->value[j] > L->value[j + 1]) { // 如果表中前面的元素比后面的元素大
                swap(L, j, j + 1); // 交互这两个元素的位置
            }
        }
    }
}

/**
 * 冒泡排序（改进算法）
 * 从顺序表最后面两个开始向前比较，每一轮排序都将确定第N小元素的位置
 * 如果某轮排序没有交换，代表排序结束，效率比冒泡排序高
 * @param L
 */
void BubbleSort2(SqList *L) {
    int i, j;
    Status flag = TRUE; // 指示每一循环是否有交换的标记

    for (i = 1; i < L->length && flag; i++) {
        flag = FALSE; // 设置本轮循环未产生交换

        for (j = L->length - 1; j >= i; j--) {
            if (L->value[j] > L->value[j + 1]) { // 如果表中前面的元素比后面的元素大
                swap(L, j, j + 1); // 交互这两个元素的位置
                flag = TRUE; // 设置本轮进行了数据交换
            }
        }
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // 存初始值的数组
    SqList L; // 顺序表

    InitSqList(&L, d); // 初始化顺序表
    printf("刚进行初始化后");
    Print(L); // 遍历顺序表

    BubbleSort0(&L); // 对顺序表进行初级冒泡排序
    printf("初级冒泡排序后");
    Print(L); // 遍历顺序表

    InitSqList(&L, d); // 初始化顺序表
    BubbleSort(&L); // 对顺序表进行正式冒泡排序
    printf("正式冒泡排序后");
    Print(L); // 遍历顺序表

    InitSqList(&L, d); // 初始化顺序表
    BubbleSort2(&L); // 对顺序表进行改进冒泡排序
    printf("改进冒泡排序后");
    Print(L); // 遍历顺序表
}