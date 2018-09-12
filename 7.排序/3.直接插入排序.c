// 直接插入排序
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
 * 直接插入排序
 * @param L 顺序表
 */
void InsertSort(SqList *L) {
    int i, j;

    for (i = 2; i <= L->length; i++) {
        // 后面的元素比前面元素小，需将L->value[i]插入有序子表
        if (L->value[i] < L->value[i - 1]) {
            L->value[0] = L->value[i]; // 设置哨兵

            // 将有序子表中，比哨兵位置元素大的元素都向后移动一个位置
            for (j = i - 1; L->value[j] > L->value[0]; j--) {
                L->value[j + 1] = L->value[j];
            }
            // 将哨兵位置的元素插入正确的位置
            L->value[j + 1] = L->value[0];
        }
    }
}

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // 存初始值的数组
    SqList L; // 顺序表

    InitSqList(&L, d); // 初始化顺序表
    printf("刚进行初始化后");
    Print(L); // 遍历顺序表

    InsertSort(&L); // 对顺序表进行直接插入排序
    printf("直接插入排序后");
    Print(L); // 遍历顺序表

    return 0;
}