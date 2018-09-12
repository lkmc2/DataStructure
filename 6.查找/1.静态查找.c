// 静态查找
#include <stdio.h>

#define MAXSIZE 100 // 数组存储空间初始分配量

int F[100]; // 斐波那契数列

/**
 * 顺序查找
 * @param a 数组
 * @param n 数组个数
 * @param key 要查找的关键字
 * @return 关键字在数据中的下标（返回0表示未找到该元素）
 */
int Sequential_Search(int *a, int n, int key) {
    int i; // 用来遍历元素

    for (i = 1; i <= n; i++) {
        if (a[i] == key) { // 数组的某个元素等于关键字
            return i; // 返回该元素的下标
        }
    }
    return 0;
}

/**
 * 带哨兵的顺序查找
 * @param a 数组
 * @param n 数组个数
 * @param key 要查找的关键字
 * @return 关键字在数据中的下标（返回0表示未找到该元素）
 */
int Sequential_Search_With_Guard(int *a, int n, int key) {
    int i; // 用来遍历元素
    a[0] = key; // 将关键词设置的数组第0个元素（哨兵）

    i = n; // i的初始值设置为数组长度

    while (a[i] != key) { // 该位置的元素不等于关键字
        i--; // 数组下标向前移动
    }
    return i; // 返回关键字的下标
}

/**
 * 二分查找（折半查找）
 * @param a 数组
 * @param n 数组个数
 * @param key 要查找的关键字
 * @return 关键字在数据中的下标（返回0表示未找到该元素）
 */
int Binary_Search(int *a, int n, int key) {
    int low, high, mid; // 当前查找范围最小、最大、中间下标

    low = 1; // 设置查找范围最小下标为数组起点下标（不考虑0下标）
    high = n; // 设置查找范围最大下标为数组终点下标

    while (low <= high) {
        mid = (low + high) / 2; // 求中间下标

        if (key < a[mid]) { // 关键字小于中间位置下标的值
            high = mid - 1; // 最大下标设置为中间下标减1
        } else if (key > a[mid]) { // 关键字大于中间位置下标的值
            low = mid + 1;  // 最小下标设置为中间下标加1
        } else { // 关键字等于中间位置下标的值
            return mid; // 返回该位置下标
        }
    }
    return 0;
}

/**
 * 插值查找（在二分查找基础上将求mid的过程换成插值公式）
 * @param a 数组
 * @param n 数组个数
 * @param key 要查找的关键字
 * @return 关键字在数据中的下标（返回0表示未找到该元素）
 */
int Interpolation_Search(int *a, int n, int key) {
    int low, high, mid; // 当前查找范围最小、最大、中间下标

    low = 1; // 设置查找范围最小下标为数组起点下标（不考虑0下标）
    high = n; // 设置查找范围最大下标为数组终点下标

    while (low <= high) {
        // 插值公式求中间值下标
        mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]);

        if (key < a[mid]) { // 关键字小于中间位置下标的值
            high = mid - 1; // 最大下标设置为中间下标减1
        } else if (key > a[mid]) { // 关键字大于中间位置下标的值
            low = mid + 1;  // 最小下标设置为中间下标加1
        } else { // 关键字等于中间位置下标的值
            return mid; // 返回该位置下标
        }
    }
    return 0;
}

/**
 * 斐波那契查找（在二分查找基础上将求mid的过程换成利用斐波那契数组求值）
 * @param a 数组
 * @param n 数组个数
 * @param key 要查找的关键字
 * @return 关键字在数据中的下标（返回0表示未找到该元素）
 */
int Fibonacci_Search(int *a, int n, int key) {
    int low, high, mid; // 当前查找范围最小、最大、中间下标
    int i, k = 0; // i用来遍历元素，k用来定位在斐波那契数列的位置

    low = 1; // 设置查找范围最小下标为数组起点下标（不考虑0下标）
    high = n; // 设置查找范围最大下标为数组终点下标

    while (n > F[k] - 1) { // 计算n位于斐波那契数列的位置
        k++;
    }
    for (i = n; i < F[k] - 1; i++) { // 将不满的数值补全
        a[i] = a[n];
    }

    while (low <= high) {
        mid = low + F[k - 1] - 1; // 求中间值下标

        if (key < a[mid]) { // 关键字小于中间位置下标的值
            high = mid - 1; // 最大下标设置为中间下标减1
            k = k - 1;
        } else if (key > a[mid]) { // 关键字大于中间位置下标的值
            low = mid + 1;  // 最小下标设置为中间下标加1
            k = k - 2;
        } else { // 关键字等于中间位置下标的值
            if (mid <= n) {
                return mid;  // 若相等则说明mid为找到的位置
            } else {
                return n; // mid > n说明是补全数字，返回n
            }
        }
    }
    return 0;
}

int main() {
    int i, result;
    int arr[MAXSIZE] = {0, 1, 15, 27, 36, 49, 53, 61, 73, 84, 99};

    result = Sequential_Search(arr, 10, 73); // 顺序查找
    printf("顺序查找的结果为：%d\n", result);

    result = Sequential_Search_With_Guard(arr, 10, 73); // 带哨兵的顺序查找
    printf("带哨兵的顺序查找的结果为：%d\n", result);

    result = Binary_Search(arr, 10, 73); // 二分查找
    printf("二分查找结果为：%d\n", result);

    result = Interpolation_Search(arr, 10, 73); // 插值查找
    printf("插值查找结果为：%d\n", result);

    /********** 初始化斐波那契数组 **********/
    F[0] = 0;
    F[1] = 1;

    for (i = 2; i < MAXSIZE; i++) {
        F[i] = F[i - 1] + F[i - 2];
    }
    /***************************************/

    result = Fibonacci_Search(arr, 10, 73); // 斐波那契查找
    printf("斐波那契查找结果为：%d\n", result);

    return 0;
}