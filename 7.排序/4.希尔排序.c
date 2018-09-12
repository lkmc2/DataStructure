// 希尔排序
#include <stdio.h>

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
 * 希尔排序
 * @param L 顺序表
 */
void ShellSort(SqList *L) {
    int i, j;
    int k = 0; // 统计遍历次数
    int increment = L->length; // 序列增量

    do {
        increment = increment / 3 + 1; // 设置序列增量为原来的三分之一（假设等于4）

        for (i = increment + 1; i <= L->length; i++) {
            // 比较第5个和第(5 - 4) = 1个元素，若第5个元素比第1个元素的值小
            if (L->value[i] < L->value[i - increment]) {
                L->value[0] = L->value[i]; // 将5位置的值暂存在0位置

                // j = 5 - 4 = 1，若0元素的值小于1元素（此时条件不成立）
                for (j = i - increment; j > 0 && L->value[0] < L->value[j]; j -= increment) {
                    // 将5元素的值赋值为1元素的值（记录后移，找到合适0元素插入的位置）
                    L->value[j + increment] = L->value[j];
                }

                // 将0元素的值插入到合适的位置（5元素）
                L->value[j + increment] = L->value[0];
            }
        }
        printf("第%d趟排序之后,", ++k);
        Print(*L); // 遍历顺序表
    } while (increment > 1);
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // 存初始值的数组
    SqList L; // 顺序表

    InitSqList(&L, d); // 初始化顺序表
    printf("刚进行初始化后");
    Print(L); // 遍历顺序表

    ShellSort(&L); // 对顺序表进行希尔排序
    printf("希尔排序排序后");
    Print(L); // 遍历顺序表

    return 0;
}