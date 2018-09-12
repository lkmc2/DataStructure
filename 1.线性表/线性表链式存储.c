// 线性表（链式存储结构）
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

typedef int Status; // 函数返回结果类型
typedef int ElemType; // 元素类型

// 链表节点
typedef struct Node {
    ElemType data; // 存放链表元素
    struct Node *next; // 指向下一个节点的指针
} Node;

typedef struct Node *LinkList; // 线性表链表结构

/**
 * 初始化线性表
 * @param L 线性表
 * @return 执行状态
 */
Status InitList(LinkList *L) {
    *L = (LinkList) malloc(sizeof(Node)); // 为链表分配存储空间
    // 存储空间分配失败
    if (!(*L)) {
        return ERROR;
    }

    (*L)->next = NULL; // 让头节点指向为空
    return OK;
}

/**
 * 判断线性表是否为空
 * @param L 线性表
 * @return 执行状态
 */
Status ListEmpty(LinkList L) {
    // 链表中含有元素，不为空
    if (L->next) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * 清空线性表
 * @param L 线性表
 * @return 执行状态
 */
Status ClearList(LinkList *L) {
    LinkList p, q; // p、q用于遍历并删除L中的所有节点

    p = (*L)->next; // p指向L的第一个节点

    // 链表L中如果还有元素
    while (p) {
        q = p->next; // q指向p的下一个节点
        free(p); // 释放p节点
        p = q; // 让p指向q节点（即相对原来位置向后移动一个位置）
    }
    (*L)->next = NULL; // 头节点指针域置空
    return OK;
}

/**
 * 获取线性表长度
 * @param L 线性表
 * @return 线性表长度
 */
int ListLength(LinkList L) {
    int i = 0; // 用于统计元素个数

    LinkList p = L->next; // p指向L的第一个节点

    // 链表L中如果还有元素
    while (p) {
        i++; // 统计数加1
        p = p->next; // 节点向后移动
    }
    return i; // 返回链表中元素个数
}

/**
 * 获取线性表中指定位置的元素值
 * @param L 线性表
 * @param i 获取元素位置下标
 * @param e 获取元素值
 * @return 执行状态
 */
Status GetElem(LinkList L, int i, ElemType *e) {
    int j; // 计数器
    LinkList p; // 用于遍历链表元素
    j = 1; // 初始下标为1
    p = L->next; // p指向L的第一个元素

    // 当链表L中如果还有元素，并且未到达i位置
    while (p && j < i) {
        p = p->next; // p指向下一个节点
        j++; // 计数器加1
    }

    // p无下一个节点或计数器j超过i位置（即第i个元素不存在）
    if (!p || j > i) {
        return ERROR;
    }
    // 将i节点的数据赋值给e元素
    *e = p->data;
    return OK;
}

/**
 * 定位元素e在线性表中的位置
 * 找到的该元素返回元素下标，未找到该元素返回0
 * @param L 线性表
 * @param e 元素
 * @return 元素在线性表中的下标
 */
int LocateElem(LinkList L, ElemType e) {
    int i = 0; // 记录元素的下标
    LinkList p = L->next; // p指向L的第一个元素

    // 链表L中如果还有元素
    while (p->next) {
        i++; // 下标加1
        // p节点元素的值等于e
        if (p->data == e) {
            return i; // 返回e元素对应的下标
        }
        p = p->next; // p指向下一个元素
    }
    return 0;
}

/**
 * 在线性表中指定位置插入新元素
 * @param L 线性表
 * @param i 插入位置
 * @param e 插入的值
 * @return 执行状态
 */
Status ListInsert(LinkList *L, int i, ElemType e) {
    int j; // 下标计数器
    LinkList p, s; // p用来遍历L的节点，s用来生成新节点

    j = 1; // 计数器起始值为1
    p = *L; // p指向链表头节点

    // 链表L中如果还有元素，并且下标未移动到i位置
    while (p && j < i) {
        p = p->next; // p向后移动
        j++; // 下标计数器加1
    }

    // p节点未空，或下标计数器超出范围（即第i个元素不存在，插入失败）
    if (!p || j > i) {
        return ERROR;
    }

    s = (LinkList) malloc(sizeof(Node)); // 生成新节点
    s->data = e; // 给新节点赋值为e的值
    s->next = p->next; // 新节点s的指针指向插入位置的下一个节点
    p->next = s; // 插入位置的下一个节点指向新节点s
    return OK;
}

/**
 * 删除线性表中指定位置的元素
 * 删除位置的值，将存到元素e中
 * @param L 线性表
 * @param i 删除位置的下标
 * @param e 删除位置的值
 * @return 执行状态
 */
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int j; // 下标计数器
    LinkList p, q; // p用来遍历L的节点，s用来指向将删除的节点

    j = 1; // 计数器起始值为1
    p = *L; // p指向链表头节点

    // 链表L中如果还有元素，并且下标未移动到i位置
    while (p->next && j < i) {
        p = p->next; // p向后移动
        j++; // 下标计数器加1
    }

    // p节点未空，或下标计数器超出范围（即第i个元素不存在，删除失败）
    if (!(p->next) || j > i) {
        return ERROR;
    }

    q = p->next; // q指向被删除节点
    p->next = q->next; // p指向被删除节点的后一个节点
    *e = q->data; // 将被删除节点的值赋值给e元素
    free(q); // 释放被删除节点的空间
    return OK;
}

/**
 * 打印单个元素
 * @param e 元素值
 * @return 执行状态
 */
Status visit(ElemType e) {
    printf("%d ", e);
    return OK;
}

/**
 * 遍历输出线性表中所有元素
 * @param L 线性表
 * @return 执行状态
 */
Status ListTravel(LinkList L) {
    LinkList p = L->next; // p指向L的第一个节点

    printf("[ ");
    // 链表L中如果还有元素
    while (p) {
        visit(p->data); // 打印单个元素
        p = p->next; // p向后移动
    }
    printf("]\n");
    return OK;
}

/**
 * 随机产生n个元素，创建带表头结点的单链线性表（头插法）
 * @param L 线性表
 * @param n 插入元素个数
 */
void CreateListHead(LinkList *L, int n) {
    LinkList p; // 用来创建新节点
    int i; // 用于遍历下标

    srand(time(0)); // 设置随机数种子
    *L = (LinkList) malloc(sizeof(Node)); // 创建带表头节点的单链表
    (*L)->next = NULL; // 将链表指针置空

            // 给线性表L插入n个100以内的随机数
    for (i = 0; i < n; i++) {
        p = (LinkList) malloc(sizeof(Node)); // 生成新节点
        p->data = rand() % 100 + 1; // 生成100以内的随机数，赋值给新节点
        p->next = (*L)->next; // 新元素指向头节点的下一个元素
        (*L)->next = p; // 头节点指向新元素
    }
}

/**
 * 随机产生n个元素，创建带表头结点的单链线性表（尾插法）
 * @param L 线性表
 * @param n 插入元素个数
 */
void CreateListTail(LinkList *L, int n) {
    LinkList p, r; // p用来创建新节点，r用来指向L的表尾
    int i; // 用于遍历下标

    srand(time(0)); // 设置随机数种子
    *L = (LinkList) malloc(sizeof(Node)); // 创建带表头节点的单链表
    r = *L; // r指向L的表尾

    // 给线性表L插入n个100以内的随机数
    for (i = 0; i < n; i++) {
        p = (LinkList) malloc(sizeof(Node)); // 生成新节点
        p->data = rand() % 100 + 1; // 生成100以内的随机数，赋值给新节点
        r->next = p; // 表尾指向新节点
        r = p; // 新节点成为表尾
    }
    r->next = NULL; // 设置表尾指向置空
}

int main() {
    LinkList L; // 线性表

    Status status; // 执行状态
    ElemType e; // 线性表元素
    int result; // 运行结果
    int j, k; // 用于遍历元素的下标

    status = InitList(&L); // 初始化线性表
    printf("初始化线性表L后，L的长度为：%d\n", ListLength(L));

    result = ListEmpty(L); // 获取线性表是否为空
    printf("L是否为空：%s\n", result == TRUE ? "是" : "否");

    /*** 给L的表头插入5个元素 ***/
    for (j = 1; j <= 5; j++) {
        status = ListInsert(&L, 1, j); // 向线性表表头插入值
    }
    printf("在L表头依次插入1~5后，L中的值为：");
    ListTravel(L); // 遍历线性表

    printf("插入5个元素后，L的长度为：%d\n", ListLength(L));

    result = ListEmpty(L); // 获取线性表是否为空
    printf("L是否为空：%s\n", result == TRUE ? "是" : "否");

    /*** 清空L中的元素 ***/
    status = ClearList(&L); // 清空线性表
    printf("清空线性表L后，L的长度为：%d\n", ListLength(L));

    result = ListEmpty(L); // 获取线性表是否为空
    printf("L是否为空：%s\n", result == TRUE ? "是" : "否");

    /*** 给L的表尾插入10个元素 ***/
    for (j = 1; j <= 10; j++) {
        ListInsert(&L, j, j); // 向线性表表尾插入值
    }
    printf("在L表尾依次插入1~10后，L中的值为：");
    ListTravel(L); // 遍历线性表

    printf("插入10个元素后，L的长度为：%d\n", ListLength(L));

    /*** 给L的表头插入一个元素 ***/
    ListInsert(&L, 1, 33); // 向线性表表头插入元素33

    printf("在L表头插入元素33后，L中的值为：");
    ListTravel(L); // 遍历线性表

    printf("插入元素33后，L的长度为：%d\n", ListLength(L));

    /*** 获取第5个元素的值 ***/
    GetElem(L, 5, &e); // 获取L中下标为5的元素到e中
    printf("L中第5个元素的值为：%d\n", e);

    /*** 获取下标为3、4元素的值 ***/
    for (j = 3; j <= 4; j++) {
        k = LocateElem(L, j); // 获取L中下标为j的元素的值
        if (k) {
            printf("第%d个元素的值为：%d\n", k, j);
        } else {
            printf("没有值为%d的元素\n", j);
        }
    }

    /*** 删除表中多个元素 ***/
    k = ListLength(L); // k为表长
    for (j = k + 1; j >= k; j--) {
        status = ListDelete(&L, j, &e); // 删除L中第j个元素，并把删除元素的值赋值给e
        if (status == ERROR) {
            printf("删除第%d个元素失败\n", j);
        } else {
            printf("删除第%d个元素的值为：%d\n", j, e);
        }
    }
    printf("删除表中元素后，L中的值为：");
    ListTravel(L); // 遍历线性表

    /*** 删除L中第5个元素 ***/
    j = 5;
    ListDelete(&L, j, &e); // 删除L中第j个元素，并把删除元素的值赋值给e
    printf("删除第%d个元素的值为：%d\n", j, e);

    printf("删除第%d个元素后，L中的值为：",j);
    ListTravel(L); // 遍历线性表

    /*** 清空L中元素,并使用头插法插入20个元素 ***/
    status = ClearList(&L); // 清空表中元素
    printf("清空L中元素后，L的长度为：%d\n", ListLength(L));

    CreateListHead(&L, 20); // 使用头插法插入20个随机元素
    printf("使用头插法插入20个随机元素后，L中的值为：");
    ListTravel(L); // 遍历线性表

    /*** 清空L中元素,并使用尾插法插入20个元素 ***/
    status = ClearList(&L); // 清空表中元素
    printf("清空L中元素后，L的长度为：%d\n", ListLength(L));

    CreateListTail(&L, 20); // 使用尾插法插入20个随机元素
    printf("使用尾插法插入20个随机元素后，L中的值为：");
    ListTravel(L); // 遍历线性表

    return 0;
}