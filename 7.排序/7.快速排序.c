// 快速排序
#include <stdio.h>
#include <malloc.h>

#define N 10 // 数组最大值
#define MAX_LENGTH_INSERT_SORT 7 // 用于快速排序时判断是否选用插入排序阙值

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

/************** 快速排序 **************/

/**
 * 对顺序表进行分割，使在关键字前面的元素都大于它，后面的元素都小于它
 * @param L 顺序表
 * @param low 起点下标
 * @param high 终点下标
 * @return 分割成两部分后，关键字的下标
 */
int Partition(SqList *L, int low, int high) {
    int pivotkey; // 存储关键字

    pivotkey = L->value[low]; // 设置关键字为最小值

    while (low < high) { // 低位下标小于高位下标
        // 低位下标小于高位下标，并且高位元素的值大于等于关键字
        while (low < high && L->value[high] >= pivotkey) {
            high--; // 高位下标向前移动
        }
        swap(L, low, high); // 将比关键字小的元素的值放到前面low的位置

        // 低位下标小于高位下标，并且低位元素的值小于等于关键字
        while (low < high && L->value[low] <= pivotkey) {
            low++; // 低位向后移动
        }
        swap(L, low, high); // 将比关键字大的元素的值放到后面high的位置
    }
    return low; // 返回关键字的下标
}

/**
 * 快速排序
 * @param L 顺序表
 * @param low 起点下标
 * @param high 终点下标
 */
void QSort(SqList *L, int low, int high) {
    int pivot; // 存储分割关键字下标

    // 低位小于高位
    if (low < high) {
        pivot = Partition(L, low, high); // 将L->value[low..high]一分为二，获取关键字下标
        QSort(L, low, pivot - 1); // 对前半部分递归排序
        QSort(L, pivot + 1, high); // 对后半部分递归排序
    }
}

/**
 * 调用快速排序
 * @param L 顺序表
 */
void QuickSort(SqList *L) {
    QSort(L, 1, L->length); // 对整个顺序表进行快速排序
}

/**************************************/

/************** 快速排序（改进版） **************/

/**
 * 对顺序表进行分割，使在关键字前面的元素都大于它，后面的元素都小于它
 * @param L 顺序表
 * @param low 起点下标
 * @param high 终点下标
 * @return 分割成两部分后，关键字的下标
 */
int Partition2(SqList *L, int low, int high) {
    int pivotkey; // 存储关键字

    int mid = low + (high - low) / 2; // 计算中间位置的下标

    // 使用三数取中法获取更适合的关键字（排序最左边、中间、最右边位置的值，取中间的数）
    if (L->value[low] > L->value[high]) {
        swap(L, low, high); // 交换最左边和最右边元素，保证左边较小
    }
    if (L->value[mid] > L->value[high]) {
        swap(L, mid, high); // 交换中间和最右边元素，保证中间较小
    }
    if (L->value[mid] < L->value[low]) {
        swap(L, mid, low); // 交换中间和最左边元素，保证左边较小
    }

    pivotkey = L->value[low]; // 设置关键字为三个数中的最小值
    L->value[0] = pivotkey; // 备份关键字到0下标位置

    while (low < high) { // 低位下标小于高位下标
        // 低位下标小于高位下标，并且高位元素的值大于等于关键字
        while (low < high && L->value[high] >= pivotkey) {
            high--; // 高位下标向前移动
        }
        L->value[low] = L->value[high]; // 将比关键字小的元素的值放到前面low的位置

        // 低位下标小于高位下标，并且低位元素的值小于等于关键字
        while (low < high && L->value[low] <= pivotkey) {
            low++; // 低位向后移动
        }
        L->value[high] = L->value[low]; // 将比关键字大的元素的值放到后面high的位置
    }

    L->value[low] = L->value[0]; // 将关键字存到低下标位置
    return low; // 返回关键字的下标
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

/**
 * 快速排序（改进版）
 * @param L 顺序表
 * @param low 起点下标
 * @param high 终点下标
 */
void QSort2(SqList *L, int low, int high) {
    int pivot; //存储关键字

    // 高低位之差大于指定值，调用快速排序
    if ((high - low) > MAX_LENGTH_INSERT_SORT) {
        // 低位下标小于高位下标
        while (low < high) {
            // 将L->value[low..high]一分为二，获取关键字下标
            pivot = Partition2(L, low, high);
            QSort2(L, low, pivot - 1); // 对前半部分进行递归排序
//            QSort2(L, pivot + 1, high); // 对后半部分进行递归排序
            low = pivot + 1; // 尾递归
        }
    } else { // 高低位元素之差过小，调用插入排序
        InsertSort(L); // 插入排序
    }
}

/**
 * 调用快速排序（改进版）
 * @param L 顺序表
 */
void QuickSort2(SqList *L) {
    QSort2(L, 1, L->length); // 对整个顺序表进行快速排序
}

/************************************************/

int main() {
    int d[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 102}; // 存初始值的数组
    SqList L; // 顺序表

    InitSqList(&L, d); // 初始化顺序表
    printf("在进行初始化之后");
    Print(L); // 遍历顺序表

    QuickSort(&L); // 对顺序表进行快速排序
    printf("快速排序(普通)后");
    Print(L); // 遍历顺序表

    InitSqList(&L, d); // 初始化顺序表
    QuickSort2(&L); // 对顺序表进行快速排序
    printf("快速排序(改进版)");
    Print(L); // 遍历顺序表

    return 0;
}