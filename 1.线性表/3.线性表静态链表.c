// 线性表（静态链表）
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败

#define MAXSIZE 100 // 初始分配存储空间

typedef int Status; // 函数返回结果类型
typedef char ElemType; // 元素类型

/**
 * 静态链表结构
 * 1. 数组最后一个元素的cur用来存放第一个插入元素的下标，
 *    相当于头节点，指向0时表示链表为空
 * 2. 数组0下标元素的cur用来存放下一个可用存储位置的下标，
 *    即下一个插入节点的位置
 */
typedef struct {
    ElemType data; // 存放元素值
    int cur; // 指向下一个节点的下标，为0表示无指向，即到达链表末尾
} Component, StaticLinkList[MAXSIZE];

/**
 * 初始化静态链表
 * 将一维数组L的分量链接成一个备用链表，L[0].cur为头指针，0表示空指针
 * @param L 静态链表
 * @return 执行状态
 */
Status InitList(StaticLinkList L) {
    int i; // 用于遍历表元素

    for (i = 0; i < MAXSIZE - 1; i++) {
        L[i].cur = i + 1; // 设置每个位置的指针指向下一个元素的位置
    }
    // 链表中最后一个元素指向0（表示当前第一个插入的节点下标为0，此时链表为空）
    L[MAXSIZE - 1].cur = 0;
    return OK;
}

/**
 * 获取下一个可用存储位置的下标
 * @param L 静态链表
 * @return 下一个可用存储位置的下标，无可用存储位置时返回0
 */
int Malloc_SSL(StaticLinkList L) {
    int i = L[0].cur; // L中0位置cur存的值就是下一个可用存储位置的下标

    // 当前静态链表未满
    if (L[0].cur) {
        L[0].cur = L[i].cur; // 获取下一个可用存储位置的下标
    }
    return i; // 返回下一个可用存储位置的下标
}

/**
 * 释放下标为k的元素到备用链表
 * 即让下标为k的元素成为下一个可插入节点
 * @param L 静态链表
 * @param k 元素下标
 */
void Free_SSL(StaticLinkList L, int k) {
    L[k].cur = L[0].cur; // 让k下标元素的下一个元素指向原本的下一个可插入节点
    L[0].cur = k; // 让k下标的元素成为下一个可插入节点
}

/**
 * 获取线性链表长度
 * @param L 线性链表
 * @return 线性链表长度
 */
int ListLength(StaticLinkList L) {
    int j = 0; // 用于统计元素个数
    int i = L[MAXSIZE - 1].cur; // 获取第一个元素的下标

    // 遍历链表元素
    while (i) {
        i = L[i].cur; // 获取下一个元素的下标
        j++; //统计个数加1
    }
    return j; // 返回链表长度
}

/**
 * 在线性链表中指定位置插入新元素
 * @param L 线性链表
 * @param i 插入位置
 * @param e 插入的值
 * @return 执行状态
 */
Status ListInsert(StaticLinkList L, int i, ElemType e) {
    int j, t; // j是下一个可插入位置的下标，t用于遍历for循环

    int k = MAXSIZE - 1; // 最后一个元素的下标

    // 插入位置下标越界，插入失败
    if (i < 1 || i > ListLength(L) + 1) {
        return ERROR;
    }

    j = Malloc_SSL(L); // 获取下一个可插入位置的下标

    // 线性链表未满（j不为0）
    if (j) {
        L[j].data = e; // 将e赋值给下一个可插入节点的值（j下标的元素表示新节点）

        // 遍历线性链表，找到插入位置的上一个节点
        for (t = 1; t <= i - 1; t++) {
            k = L[k].cur; // 获取下一个元素的坐标
        }

        L[j].cur = L[k].cur; // 新节点的指向插入位置前一个元素的下一个元素（即原本i位置的节点）
        L[k].cur = j; // 插入位置的上一个节点指向新节点
        return OK;
    }
    return ERROR;
}

/**
 * 删除线链性表中指定位置的元素
 * @param L 线性链表
 * @param i 删除位置的下标
 * @return 执行状态
 */
Status ListDelete(StaticLinkList L, int i) {
    int j; // 用于遍历元素

    int k = MAXSIZE - 1; // 最后一个元素的下标

    // 插入位置下标越界，插入失败
    if (i < 1 || i > ListLength(L) + 1) {
        return ERROR;
    }

    // 遍历线性链表，找到删除位置的上一个节点
    for (j = 1; j <= i - 1; j++) {
        k = L[k].cur; // 获取下一个元素的下标
    }

    j = L[k].cur; // 获取被删除元素的下标
    L[k].cur = L[j].cur; // 【被删除节点的上一个节点】指向【被删除节点的下一个节点】（即跳过被删除节点）
    Free_SSL(L, j); // 释放被删除节点
    return OK;
}

/**
 * 打印单个元素
 * @param e 元素值
 * @return 执行状态
 */
Status visit(ElemType e) {
    printf("%c ", e);
    return OK;
}

/**
 * 遍历输出线性链表中所有元素
 * @param L 线性链表
 * @return 执行状态
 */
Status ListTravel(StaticLinkList L) {
    int i = L[MAXSIZE - 1].cur; // 获取链表第一个元素的下标

    printf("[ ");
    // 遍历链表中所有元素
    while (i) {
        visit(L[i].data); // 打印单个节点的值
        i = L[i].cur; // 获取下一个节点的下标
    }
    printf("]\n");
    return OK;
}

int main() {
    StaticLinkList L; // 线性链表
    Status status; // 执行状态

    status = InitList(L); // 初始化线性链表

    printf("初始化后，L的长度为：%d\n", ListLength(L));

    status = ListInsert(L, 1, 'F');
    status = ListInsert(L, 1, 'E');
    status = ListInsert(L, 1, 'D');
    status = ListInsert(L, 1, 'B');
    status = ListInsert(L, 1, 'A');

    printf("在L的表头分别插入五个元素后，L中的值为：");
    ListTravel(L); // 遍历链表元素
    printf("L的长度为：%d\n", ListLength(L));

    status = ListInsert(L, 3, 'C'); // 在第三个位置插入C元素
    printf("在第三个位置插入一个元素C后，L中的值为：");
    ListTravel(L); // 遍历链表元素
    printf("L的长度为：%d\n", ListLength(L));

    status = ListDelete(L, 4); // 删除第四个位置的元素
    printf("删除第四个位置的元素D后，链表L中的值为：");
    ListTravel(L); // 遍历链表元素
    printf("L的长度为：%d\n", ListLength(L));

    return 0;
}

