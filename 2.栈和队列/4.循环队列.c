// 队列（循环队列）
#include <stdio.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假
#define MAXSIZE 20 // 存储空间初始分配大小

typedef int Status; // 函数返回结果类型
typedef int ElemType; // 元素类型

// 循环队列的顺序存储结构
typedef struct {
    ElemType data[MAXSIZE]; // 存储队列元素
    int front; // 头指针
    int rear; // 尾指针
} SqQueue;

/**
 * 初始化队列
 * @param Q 队列
 * @return 执行状态
 */
Status InitQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

/**
 * 清空队列
 * @param Q 队列
 * @return 执行状态
 */
Status ClearQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

/**
 * 判断队列是否为空
 * @param Q 队列
 * @return 队列是否为空
 */
Status QueueEmpty(SqQueue Q) {
    // 头指针等于尾指针，队列为空
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
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/**
 * 获取队列头元素
 * @param Q 队列
 * @param e 存储头元素值
 * @return 执行状态
 */
Status GetHead(SqQueue Q, ElemType *e) {
    // 队列为空，获取失败
    if (Q.front == Q.rear) {
        return ERROR;
    }

    *e = Q.data[Q.front]; // 将队列头元素存储到元素e中
    return OK;
}

/**
 * 在队列的队尾处插入元素
 * @param Q 队列
 * @param e 插入元素值
 * @return 执行状态
 */
Status EnQueue(SqQueue *Q, ElemType e) {
    // 队列满时，插入失败
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return ERROR;
    }

    Q->data[Q->rear] = e; // 在队尾处插入元素e
    // 队尾指针向后移动，若到最后则转向数组头部
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

/**
 * 删除队头元素
 * @param Q 队列
 * @param e 存储出队元素的值
 * @return 执行状态
 */
Status DeQueue(SqQueue *Q, ElemType *e) {
    // 队满时，出队失败
    if (Q->front == Q->rear) {
        return ERROR;
    }

    *e = Q->data[Q->front]; // 将队列头元素存储到元素e中
    // 队头指针向后移动，若到最后则转向数组头部
    Q->front = (Q->front + 1) % MAXSIZE;
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
Status QueueTravel(SqQueue Q) {
    int i; // 用于遍历元素的下标
    i = Q.front; // 指向队头指针

    printf("[ ");
    // 当指针不等于队尾指针
    while (i != Q.rear) {
        visit(Q.data[i]); // 打印单个元素的值
        i = (i + 1) % MAXSIZE; // 获取下个元素的下标
    }
    printf("]\n");
    return OK;
}

int main() {
    Status status; // 执行状态
    int i = 0, j;
    ElemType e; // 元素值
    SqQueue Q; // 队列

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