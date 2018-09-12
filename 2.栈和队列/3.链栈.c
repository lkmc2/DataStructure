// 链栈
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

typedef int Status; // 函数返回结果类型
typedef int ElemType; // 元素类型

// 链栈节点
typedef struct StackNode {
    ElemType data; // 元素值
    struct StackNode *next; // 指向下一个节点的指针
}StackNode, *LinkStackPtr;

// 链栈结构
typedef struct {
    LinkStackPtr top; // 栈顶指针
    int count; // 栈中元素个数
} LinkStack;

/**
 * 初始化栈
 * @param S 栈
 * @return 执行状态
 */
Status InitStack(LinkStack *S) {
    S->top = (LinkStackPtr) malloc(sizeof(StackNode)); // 为栈顶指针分配空间
    // 分配空间失败，初始化错误
    if (!S->top) {
        return ERROR;
    }

    S->top = NULL; // 栈顶指针置空
    S->count = 0; // 栈中元素为0
    return OK;
}

/**
 * 清空栈中元素
 * @param S 栈
 * @return 执行状态
 */
Status ClearStack(LinkStack *S) {
    LinkStackPtr p, q; // p用于指向下一个元素，q指向被删除元素

    p = S->top; // p指向栈顶
    // 当栈中还有元素时
    while (p) {
        q = p; // q指向当前元素
        p = p->next; // p指向下一个元素
        free(q); // 删除q元素
    }
    S->count = 0; // 设置栈中元素个数为0
    return OK;
}

/**
 * 判断栈是否为空
 * @param S 栈
 * @return 执行状态
 */
Status StackEmpty(LinkStack *S) {
    // 栈中元素个数为0
    if (S->count == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 获取栈中元素个数
 * @param S 栈
 * @return 执行状态
 */
Status StackLength(LinkStack *S) {
    return S->count; // 返回栈中元素个数
}

/**
 * 获取栈顶元素的值，存到元素e中
 * @param S 栈
 * @param e 用于存储栈顶元素的值
 * @return 执行状态
 */
Status GetTop(LinkStack *S, ElemType *e) {
    // 栈空元素为空，获取失败
    if (S->count == 0) {
        return ERROR;
    }

    *e = S->top->data; // 将栈顶元素的值存到元素e中
    return OK;
}

/**
 * 添加新元素e到栈顶
 * @param S 栈
 * @param e 新元素
 * @return 执行状态
 */
Status Push(LinkStack *S, ElemType e) {
    // 创建新节点
    LinkStackPtr s = (LinkStackPtr) malloc(sizeof(StackNode));

    // 节点创建失败
    if (!s) {
        return ERROR;
    }

    s->data = e; // 将新元素值赋值给新节点
    s->next = S->top; // 设置新节点的下一个元素指向栈顶元素
    S->top = s; // 设置栈顶指针指向新节点
    S->count++; // 栈中元素个数加1
    return OK;
}

/**
 * 弹出栈顶元素
 * @param S 栈
 * @param e 弹出元素
 * @return 执行状态
 */
Status Pop(LinkStack *S, ElemType *e) {
    LinkStackPtr p; // 指向被删除元素的指针

    // 栈中元素为空，删除失败
    if (S->count == 0) {
        return ERROR;
    }

    *e = S->top->data; // 将栈顶元素的值赋值给元素e
    p = S->top; // p指向被删除节点
    S->top = S->top->next; // 设置新的栈顶元素为被删除节点的下一个元素
    free(p); // 删除栈顶节点
    S->count--; // 栈中元素个数减1

    return OK;
}

/**
 * 打印单个元素的值
 * @param e 元素
 * @return 执行状态
 */
Status visit(ElemType e) {
    printf("%d ", e);
    return OK;
}

/**
 * 从栈顶开始遍历栈中元素
 * @param S 栈
 * @return 执行状态
 */
Status StackTravel(LinkStack *S) {
    LinkStackPtr p; // 用于遍历栈中元素的指针

    p = S->top; // p指向栈顶
    printf("[ ");
    // 当栈中还有元素
    while (p) {
        visit(p->data); // 打印该元素的值
        p = p->next; // p指向下一个节点
    }
    printf("]\n");
    return OK;
}

int main() {
    int j; // 用于遍历
    LinkStack s; // 栈
    ElemType e; // 元素

    // 如果初始化成功
    if (InitStack(&s) == OK) {
        // 向栈中插入10个元素
        for (j = 1; j <= 10; j++) {
            Push(&s, j); // 向栈顶插入元素j
        }
    }

    printf("栈中的元素为：");
    StackTravel(&s); // 遍历栈中元素

    Pop(&s, &e); // 弹出栈顶元素
    printf("弹出的栈顶元素为：e = %d\n", e);
    printf("弹出一个元素之后，栈是否为空：%s\n", StackEmpty(&s) == TRUE ? "是" : "否");

    GetTop(&s, &e); // 获取栈顶元素的值
    printf("栈顶元素的值为：e = %d\n", e);

    printf("栈的长度为：%d\n", StackLength(&s)); // 获取栈的长度

    ClearStack(&s); // 清空栈中元素
    printf("清空栈后，栈是否为空：%s\n", StackEmpty(&s) == TRUE ? "是" : "否");

    return 0;
}