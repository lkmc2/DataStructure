// 线性表（顺序存储结构）
#include <stdio.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

#define MAXSIZE 20 // 初始分配存储空间

typedef int Status; // 函数返回结果类型
typedef int ElemType; // 元素类型

// 线性表结构
typedef struct {
    ElemType data[MAXSIZE]; // 存放线性表元素的数组
    int length; // 线性表长度
} SqList;

/**
 * 初始化线性表
 * @param L 线性表
 * @return 执行状态
 */
Status InitList(SqList *L) {
    L->length = 0;
    return OK;
}

/**
 * 判断线性表是否为空
 * @param L 线性表
 * @return 执行状态
 */
Status ListEmpty(SqList L) {
    if (L.length == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 清空线性表
 * @param L 线性表
 * @return 执行状态
 */
Status ClearList(SqList *L) {
    // 设置线性表长度为0
    L->length = 0;
    return OK;
}

/**
 * 获取线性表长度
 * @param L 线性表
 * @return 线性表长度
 */
int ListLength(SqList L) {
    return L.length;
}

/**
 * 获取线性表中指定位置的元素值
 * @param L 线性表
 * @param i 获取元素位置下标
 * @param e 获取元素值
 * @return 执行状态
 */
Status GetElem(SqList L, int i, ElemType *e) {
    // 数组长度为空，或下标不在数组范围内
    if (L.length == 0 || i < 1 || i > L.length) {
        return ERROR;
    }
    // 获取对应下标元素的值，赋值给e
    *e = L.data[i - 1];
    return OK;
}

/**
 * 定位元素e在线性表中的位置
 * 找到的该元素返回元素下标，未找到该元素返回0
 * @param L 线性表
 * @param e 元素
 * @return 元素在线性表中的下标
 */
int LocateElem(SqList L, ElemType e) {
    int i; // 元素下标
    // 线性表长度为空
    if (L.length == 0) {
        return 0;
    }

    // 遍历线性表，寻找元素e
    for (i = 0; i < L.length; i++) {
        // 找到元素e，退出循环
        if (L.data[i] == e) {
            break;
        }
    }

    // 下标大于线性表长度，未找到该元素
    if (i >= L.length) {
        return 0;
    }

    // 返回元素在线性表中的下标
    return i + 1;
}

/**
 * 在线性表中指定位置插入新元素
 * @param L 线性表
 * @param i 插入位置
 * @param e 插入的值
 * @return 执行状态
 */
Status ListInsert(SqList *L, int i, ElemType e) {
    int k; // 用于遍历元素的下标

    // 线性表已满，插入失败
    if (L->length == MAXSIZE) {
        return ERROR;
    }

    // 插入位置不在线性表范围内，插入失败
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }

    // 插入的位置在线性表范围内
    if (i <= L->length) {
        // 从倒数第二个元素开始到插入位置的元素，全都向后移动一个位置
        for (k = L->length - 1; k >= i - 1; k--) {
            L->data[k + 1] = L->data[k];
        }
    }

    L->data[i - 1] = e; // 将新元素插入
    L->length++; // 线性表长度加1
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
Status ListDelete(SqList *L, int i, ElemType *e) {
    int k; // 用于遍历元素的下标

    // 线性表长度为空，删除失败
    if (L->length == 0) {
        return ERROR;
    }

    // 删除位置不在线性表范围内，删除失败
    if (i < 1 || i > L->length) {
        return ERROR;
    }

    // 将删除位置元素的值赋值给e
    *e = L->data[i - 1];

    // 删除位置在线性表范围内
    if (i < L->length) {
        // 从删除位置的下一个元素到线性表最后一个元素，全都向前移动一个位置
        for (k = i; k < L->length; k++) {
            L->data[k - 1] = L->data[k];
        }
    }
    // 线性表长度减1
    L->length--;
    return OK;
}

/**
 * 打印单个元素
 * @param c 元素值
 * @return 执行状态
 */
Status visit(ElemType c) {
    printf("%d ", c);
    return OK;
}

/**
 * 遍历输出线性表中所有元素
 * @param L 线性表
 * @return
 */
Status ListTravel(SqList L) {
    int i; // 用于遍历元素的下标

    printf("[ ");
    // 遍历线性表所有元素
    for (i = 0; i < L.length; i++) {
        visit(L.data[i]); // 打印单个元素
    }
    printf("]\n");
    return OK;
}

/**
 * 合并两个线性表的值到La中
 * @param La 线性表1
 * @param Lb 线性表2
 */
void unionL(SqList *La, SqList Lb) {
    int i; // 用于遍历元素的下标
    int La_len, Lb_len; // 线性表La、Lb的长度
    ElemType e; // 用于存放Lb中元素的值

    // 获取线性表La和Lb的长度
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);

    // 遍历线性表Lb中的元素
    for (i = 1; i <= Lb_len; i++) {
        // 获取Lb中i位置元素的值到元素e中
        GetElem(Lb, i, &e);
        // 元素e中的值在La中不存在
        if (!LocateElem(*La, e)) {
            // 将元素e插入La的最后
            ListInsert(La, ++La_len, e);
        }
    }
}

int main() {
    SqList L; // 线性表
    SqList Lb;
    Status status; // 执行状态
    ElemType e; // 线性表元素
    int result; // 运行结果
    int j, k; // 用于遍历元素的下标

    InitList(&L); // 初始化线性表
    printf("初始化线性表L后，L的长度为：%d\n", L.length);

    result = ListEmpty(L); // 获取线性表是否为空
    printf("L是否为空：%s\n", result == TRUE ? "是" : "否");

    /*** 给L的表头插入5个元素 ***/
    for (j = 1; j <= 5; j++) {
        status = ListInsert(&L, 1, j); // 向线性表表头插入值
    }
    printf("在L表头依次插入1~5后，L中的值为：");
    ListTravel(L); // 遍历线性表

    printf("插入5个元素后，L的长度为：%d\n", L.length);

    result = ListEmpty(L); // 获取线性表是否为空
    printf("L是否为空：%s\n", result == TRUE ? "是" : "否");

    /*** 清空L中的元素 ***/
    status = ClearList(&L); // 清空线性表
    printf("清空线性表L后，L的长度为：%d\n", L.length);

    result = ListEmpty(L); // 获取线性表是否为空
    printf("L是否为空：%s\n", result == TRUE ? "是" : "否");

    /*** 给L的表尾插入10个元素 ***/
    for (j = 1; j <= 10; j++) {
        ListInsert(&L, j, j); // 向线性表表尾插入值
    }
    printf("在L表尾依次插入1~10后，L中的值为：");
    ListTravel(L); // 遍历线性表

    printf("插入10个元素后，L的长度为：%d\n", L.length);

    /*** 给L的表头插入一个元素 ***/
    ListInsert(&L, 1, 33); // 向线性表表头插入元素33

    printf("在L表头插入元素33后，L中的值为：");
    ListTravel(L); // 遍历线性表

    printf("插入元素33后，L的长度为：%d\n", L.length);

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

    /*** 初始化线性表Lb，给Lb的表头插入10个元素 ***/
    status = InitList(&Lb); // 初始化线性表Lb
    for (j = 6; j <= 15; j++) {
        status = ListInsert(&Lb, 1, j); // 向Lb表头插入10个元素
    }
    printf("插入10个元素后，Lb中的值为：");
    ListTravel(Lb);

    /*** 合并L和Lb的值到L中 ***/
    unionL(&L, Lb); // 合并两个线性表的值到L中

    printf("合并L和Lb到L后，L中的值为：");
    ListTravel(L); // 遍历线性表

    return 0;
}