// 队列（链队列）
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

typedef int Status; // 函数返回结果类型
typedef int ElemType; // 元素类型

// 队列节点
typedef struct QNode {
    ElemType data; // 元素值
    struct QNode *next; // 指向下一个节点的指针
} QNode, *QueuePtr;

// 链队列结构
typedef struct {
    QueuePtr front, rear; // 队头指针、队尾指针
} LinkQueue;

/**
 * 初始化队列
 * @param Q 队列
 * @return 执行状态
 */
Status InitQueue(LinkQueue *Q) {
    // 为队头和队尾指针分配内存
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));

    // 内存分配失败，结束程序
    if (!Q->front || !Q->rear) {
        exit(OVERFLOW);
    }

    Q->front->next = NULL; // 队头节点指向NULL
    return OK;
}

/**
 * 销毁队列
 * @param Q 队列
 * @return 执行状态
 */
Status DestroyQueue(LinkQueue *Q) {
    // 当队列中还有元素
    while (Q->front) {
        Q->rear = Q->front->next;// 队尾指针指向队头指针的下一个元素
        free(Q->front); // 释放队头指针所在节点
        Q->front = Q->rear; // 队头指针指向队尾指针（即原来的下一个元素）
    }
    return OK;
}

/**
 * 清空队列
 * @param Q 队列
 * @return 执行状态
 */
Status ClearQueue(LinkQueue *Q) {
    QueuePtr p, q; // p用来遍历队列节点，q用来指向被删除的节点

    Q->rear = Q->front; // 队尾指针指向队头指针
    p = Q->front->next; // p指向队头指针的下一个节点
    Q->front->next = NULL; // 队头指针的下一个节点指向NULL（表示删除之后的所有元素）

    // 当队列中还有元素，释放头节点之后的所有节点
    while (p) {
        q = p; // q节点指向被删除节点
        p = p->next; // p指向队列的下一个节点
        free(q); // 释放q节点
    }
    return OK;
}

/**
 * 判断队列是否为空
 * @param Q 队列
 * @return 队列是否为空
 */
Status QueueEmpty(LinkQueue Q) {
    // 头指针和尾指针位置相等，队列为空
    if (Q.front == Q.rear) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 获取队列长度
 * @param Q 队列
 * @return 队列长度
 */
int QueueLength(LinkQueue Q) {
    int i = 0; // 用于统计队列长度的计数器
    QueuePtr p; // 用于遍历队列的元素
    p = Q.front; // p指向队头节点

    // 当p没有移动到队尾指针位置
    while (p != Q.rear) {
        i++; // 计数器加1
        p = p->next; // p移动到队列的下一个节点
    }
    return i; // 返回队列长度
}

/**
 * 获取队列头元素
 * @param Q 队列
 * @param e 存储头元素值
 * @return 执行状态
 */
Status GetHead(LinkQueue Q, ElemType *e) {
    QueuePtr p;

    // 队列为空，获取失败
    if (Q.front == Q.rear) {
        return ERROR;
    }

    p = Q.front->next; // p指向队列的第一个元素
    *e = p->data; // 将队列头元素的值赋值给e元素
    return OK;
}

/**
 * 在队列的队尾处插入元素
 * @param Q 队列
 * @param e 插入元素值
 * @return 执行状态
 */
Status EnQueue(LinkQueue *Q, ElemType e) {
    // 给新节点分配空间
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));

    // 分配空间失败，结束程序
    if (!s) {
        exit(OVERFLOW);
    }

    s->data = e; // 将值赋值给新节点
    s->next = NULL; // 新节点指向NULL
    Q->rear->next = s; // 队尾指针的下一个元素指向新节点
    Q->rear = s; // 队尾指针指向新节点（新节点成为队尾指针的指向的节点）
    return OK;
}

/**
 * 删除队头元素
 * @param Q 队列
 * @param e 存储出队元素的值
 * @return 执行状态
 */
Status DeQueue(LinkQueue *Q, ElemType *e) {
    QueuePtr p; // 用于指向被删除节点

    // 队列为空，出队失败
    if (Q->front == Q->rear) {
        return ERROR;
    }

    p = Q->front->next; // p指向队列的第一个元素
    *e = p->data; // 将队列头节点的值赋值给元素e
    Q->front->next = p->next; // 头指针的下一个节点指向下下个节点（跳过头节点）

    // 如果被删除节点是队尾指针指向的节点（删除后队列为空）
    if (Q->rear == p) {
        Q->rear = Q->front; // 队尾指针指向队头指针
    }
    free(p); // 释放队头节点
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
 * 遍历队列中的元素
 * @param Q 队列
 * @return 执行状态
 */
Status QueueTravel(LinkQueue Q) {
    QueuePtr p; // 用于遍历队列中的节点

    p = Q.front->next; // p指向头节点

    printf("[ ");
    // 当队列中还有元素
    while (p) {
        visit(p->data); // 打印当前节点的值
        p = p->next; // p移动到队列下一个位置
    }
    printf("]\n");
    return OK;
}

int main() {
    Status status; // 执行状态
    int j; // j用来遍历
    ElemType e; // 元素值
    LinkQueue Q; // 队列

    /*** 初始化队列 ***/
    InitQueue(&Q); // 初始化队列
    printf("初始化队列后，队列是否为空？%s\n", QueueEmpty(Q) == TRUE ? "是" : "否");

    /*** 向队列中插入10个元素 ***/
    for (j = 1; j <=10; ++j) {
        EnQueue(&Q, j); // 将元素j插入队列
    }
    printf("插入10个元素后队列的值为：");
    QueueTravel(Q); // 遍历队列
    printf("队列的长度为：%d\n", QueueLength(Q)); // 获取队列长度
    printf("插入10个元素后，队列是否为空？%s\n", QueueEmpty(Q) == TRUE ? "是" : "否");

    /*** 删除队列中的五个元素，并打印对应的值 ***/
    printf("开始删除元素：\n");
    for (j = 0; j < 5; ++j) {
        DeQueue(&Q, &e); // 删除队头元素，将值存到e中
        printf("元素%d出队\n", e);
    }
    printf("5个元素出队后，队列中的值为：");
    QueueTravel(Q); // 遍历队列
    printf("队列的长度为：%d\n", QueueLength(Q));  // 获取队列长度

    /*** 获取队列头元素的值 ***/
    status = GetHead(Q, &e); // 获取队列头元素
    if (status) {
        printf("队列头元素为：%d\n", e);
    }

    /*** 清空队列元素 ***/
    ClearQueue(&Q); // 清空队列元素
    printf("清空队列后，队列是否为空：%s\n", QueueEmpty(Q) == TRUE ? "是" : "否");
    printf("队列中的元素为：");
    QueueTravel(Q); // 遍历元素
    return 0;
}