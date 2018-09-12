// 两栈共享空间
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

// 两栈共享结构
typedef struct {
    ElemType data[MAXSIZE]; // 用于存储元素值
    int top1; // 用于指示栈1的栈顶指针
    int top2; // 用于指示栈2的栈顶指针
}SqStack;

/**
 * 初始化栈
 * @param S 栈
 * @return 执行状态
 */
Status InitStack(SqStack *S) {
    S->top1 = -1; // 栈1的栈顶指针指向-1，此时栈1为空
    S->top2 = MAXSIZE; // 栈2的栈顶指针指向MAXSIZE，此时栈2为空
    return OK;
}

/**
 * 清空栈中元素
 * @param S 栈
 * @return 执行状态
 */
Status ClearStack(SqStack *S) {
    S->top1 = -1; // 栈1的栈顶指针指向-1，此时栈1为空
    S->top2 = MAXSIZE; // 栈2的栈顶指针指向MAXSIZE，此时栈2为空
    return OK;
}

/**
 * 判断栈是否为空
 * @param S 栈
 * @return 执行状态
 */
Status StackEmpty(SqStack *S) {
    // 栈1和栈2都为空时，栈才为空
    if (S->top1 == -1 && S->top2 == MAXSIZE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 获取栈中元素个数（栈1和栈2的元素总数）
 * @param S 栈
 * @return 执行状态
 */
int StackLength(SqStack *S) {
    return (S->top1 + 1) + (MAXSIZE - S->top2);
}

/**
 * 获取栈顶元素的值，存到元素e中
 * @param S 栈
 * @param e 用于存储栈顶元素的值
 * @param stackNumber 栈号
 * @return 执行状态
 */
Status GetTop(SqStack *S, ElemType *e, int stackNumber) {
    // 获取栈1的栈顶元素值
    if (stackNumber == 1) {
        // 栈1为空时，获取栈顶元素失败
        if (S->top1 == -1) {
            return ERROR;
        }

        // 将栈1的栈顶元素的值赋值给e元素
        *e = S->data[S->top1];
    } else { // 获取栈2的栈顶元素值
        // 栈2为空，获取栈顶元素失败
        if (S->top2 == MAXSIZE) {
            return ERROR;
        }

        // 将栈2的栈顶元素的值赋值给e元素
        *e = S->data[S->top2];
    }

    return OK;
}

/**
 * 添加新元素e到栈顶
 * @param S 栈
 * @param e 新元素
 * @param stackNumber 栈号
 * @return 执行状态
 */
Status Push(SqStack *S, ElemType e, int stackNumber) {
    // 栈满时，添加失败
    if (S->top1 + 1 == S->top2) {
        return ERROR;
    }

    // 给栈1添加新元素
    if (stackNumber == 1) {
        S->data[++S->top1] = e; // 将新元素添加到栈1的栈顶
    } else { // 给栈2添加新元素
        S->data[--S->top2] = e; // 将新元素添加到栈2的栈顶
    }

    return OK;
}

/**
 * 弹出栈顶元素
 * @param S 栈
 * @param e 弹出元素
 * @param stackNumber 栈号
 * @return 执行状态
 */
Status Pop(SqStack *S, ElemType *e, int stackNumber) {
    // 栈1弹出元素
    if (stackNumber == 1) {
        // 栈为空时，弹出元素失败
        if (S->top1 == -1) {
            return ERROR;
        }
        *e = S->data[S->top1--]; // 将栈顶元素的值赋给e元素，栈1的栈顶指针减1
    } else { // 栈2弹出元素
        if (S->top2 == MAXSIZE) {
            return ERROR;
        }
        *e = S->data[S->top2++]; // 将栈顶元素的值赋给e元素，栈2的栈顶指针加1
    }

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

    printf("栈1中的元素为：[ ");
    // 指示器位置小于栈1的栈顶指针
    while (i <= S.top1) {
        visit(S.data[i++]); // 打印i位置元素，i向下一个元素移动
    }
    printf("]\n");

    i = MAXSIZE - 1;
    printf("栈2中的元素为：[ ");
    while (i >= S.top2) {
        visit(S.data[i--]);
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
        // 向栈1中插入5个元素
        for (j = 1; j <= 5; j++) {
            Push(&s, j, 1); // 向栈1的栈顶插入元素j
        }

        // 向栈2中插入5个元素
        for (j = MAXSIZE; j > MAXSIZE - 5; j--) {
            Push(&s, j, 2); // 向栈2的栈顶插入元素j
        }
    }

    printf("栈中的元素如下：\n");
    StackTraverse(s); // 遍历栈中元素

    Pop(&s, &e, 1); // 弹出栈1的栈顶元素
    printf("弹出的栈顶元素为：e = %d\n", e);
    printf("弹出一个元素之后，栈是否为空：%s\n", StackEmpty(&s) == TRUE ? "是" : "否");

    GetTop(&s, &e, 1); // 获取栈1的栈顶元素的值
    printf("栈1的栈顶元素的值为：e = %d\n", e);

    GetTop(&s, &e, 2); // 获取栈1的栈顶元素的值
    printf("栈2的栈顶元素的值为：e = %d\n", e);

    printf("栈的长度为：%d\n", StackLength(&s)); // 获取栈的长度

    ClearStack(&s); // 清空栈中元素
    printf("清空栈后，栈是否为空：%s\n", StackEmpty(&s) == TRUE ? "是" : "否");

    return 0;
}