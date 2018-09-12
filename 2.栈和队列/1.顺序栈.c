// 顺序栈
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假
#define MAXSIZE 20 // 存储空间初始分配大小

typedef int Status; // 函数返回结果类型
typedef int ElemType; // 元素类型

// 顺序栈结构
typedef struct {
    ElemType data[MAXSIZE]; // 用于存储元素值
    int top; // 用于指示栈顶指针
}SqStack;

/**
 * 初始化栈
 * @param S 栈
 * @return 执行状态
 */
Status InitStack(SqStack *S) {
    S->top = -1; // 栈顶指针指向-1表示栈为空
    return OK;
}

/**
 * 清空栈中元素
 * @param S 栈
 * @return 执行状态
 */
Status ClearStack(SqStack *S) {
    S->top = -1; // 栈顶指针指向-1表示栈为空
    return OK;
}

/**
 * 判断栈是否为空
 * @param S 栈
 * @return 执行状态
 */
Status StackEmpty(SqStack *S) {
    if (S->top == -1) {
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
int StackLength(SqStack *S) {
    return S->top + 1;
}

/**
 * 获取栈顶元素的值，存到元素e中
 * @param S 栈
 * @param e 用于存储栈顶元素的值
 * @return 执行状态
 */
Status GetTop(SqStack *S, ElemType *e) {
    // 栈为空时，获取栈顶元素失败
    if (S->top == -1) {
        return ERROR;
    }

    // 将栈顶元素的值赋值给e元素
    *e = S->data[S->top];

    return OK;
}

/**
 * 添加新元素e到栈顶
 * @param S 栈
 * @param e 新元素
 * @return 执行状态
 */
Status Push(SqStack *S, ElemType e) {
    // 栈满时，添加失败
    if (S->top == MAXSIZE - 1) {
        return ERROR;
    }
    S->top++; // 栈顶指针加1
    S->data[S->top] = e; // 将新元素赋值给栈顶
    return OK;
}

/**
 * 弹出栈顶元素
 * @param S 栈
 * @param e 弹出元素
 * @return 执行状态
 */
Status Pop(SqStack *S, ElemType *e) {
    // 栈为空时，弹出元素失败
    if (S->top == -1) {
        return ERROR;
    }
    *e = S->data[S->top]; // 将栈顶元素的值赋给e元素
    S->top--; // 栈顶指针减1
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
 * 从栈底开始遍历栈中元素
 * @param S 栈
 * @return 执行状态
 */
Status StackTraverse(SqStack S) {
    int i = 0; // 指示器，用于指示栈顶指针的位置

    printf("[ ");
    // 指示器位置小于栈顶指针
    while (i <= S.top) {
        visit(S.data[i++]); // 打印i位置元素，i向下一个元素移动
    }
    printf("]\n");
    return OK;
}

int main() {
    int j; // 用于遍历
    SqStack s; // 栈
    ElemType e; // 元素

    // 如果初始化成功
    if (InitStack(&s) == OK) {
        // 向栈中插入10个元素
        for (j = 1; j <= 10; j++) {
            Push(&s, j); // 向栈顶插入元素j
        }
    }

    printf("栈中的元素为：");
    StackTraverse(s); // 遍历栈中元素

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