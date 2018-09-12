// ��ջ����ռ�
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��
#define MAXSIZE 20 // �洢�ռ��ʼ�����С

typedef int Status; // �������ؽ������
typedef int ElemType; // Ԫ������

// ��ջ����ṹ
typedef struct {
    ElemType data[MAXSIZE]; // ���ڴ洢Ԫ��ֵ
    int top1; // ����ָʾջ1��ջ��ָ��
    int top2; // ����ָʾջ2��ջ��ָ��
}SqStack;

/**
 * ��ʼ��ջ
 * @param S ջ
 * @return ִ��״̬
 */
Status InitStack(SqStack *S) {
    S->top1 = -1; // ջ1��ջ��ָ��ָ��-1����ʱջ1Ϊ��
    S->top2 = MAXSIZE; // ջ2��ջ��ָ��ָ��MAXSIZE����ʱջ2Ϊ��
    return OK;
}

/**
 * ���ջ��Ԫ��
 * @param S ջ
 * @return ִ��״̬
 */
Status ClearStack(SqStack *S) {
    S->top1 = -1; // ջ1��ջ��ָ��ָ��-1����ʱջ1Ϊ��
    S->top2 = MAXSIZE; // ջ2��ջ��ָ��ָ��MAXSIZE����ʱջ2Ϊ��
    return OK;
}

/**
 * �ж�ջ�Ƿ�Ϊ��
 * @param S ջ
 * @return ִ��״̬
 */
Status StackEmpty(SqStack *S) {
    // ջ1��ջ2��Ϊ��ʱ��ջ��Ϊ��
    if (S->top1 == -1 && S->top2 == MAXSIZE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��ȡջ��Ԫ�ظ�����ջ1��ջ2��Ԫ��������
 * @param S ջ
 * @return ִ��״̬
 */
int StackLength(SqStack *S) {
    return (S->top1 + 1) + (MAXSIZE - S->top2);
}

/**
 * ��ȡջ��Ԫ�ص�ֵ���浽Ԫ��e��
 * @param S ջ
 * @param e ���ڴ洢ջ��Ԫ�ص�ֵ
 * @param stackNumber ջ��
 * @return ִ��״̬
 */
Status GetTop(SqStack *S, ElemType *e, int stackNumber) {
    // ��ȡջ1��ջ��Ԫ��ֵ
    if (stackNumber == 1) {
        // ջ1Ϊ��ʱ����ȡջ��Ԫ��ʧ��
        if (S->top1 == -1) {
            return ERROR;
        }

        // ��ջ1��ջ��Ԫ�ص�ֵ��ֵ��eԪ��
        *e = S->data[S->top1];
    } else { // ��ȡջ2��ջ��Ԫ��ֵ
        // ջ2Ϊ�գ���ȡջ��Ԫ��ʧ��
        if (S->top2 == MAXSIZE) {
            return ERROR;
        }

        // ��ջ2��ջ��Ԫ�ص�ֵ��ֵ��eԪ��
        *e = S->data[S->top2];
    }

    return OK;
}

/**
 * �����Ԫ��e��ջ��
 * @param S ջ
 * @param e ��Ԫ��
 * @param stackNumber ջ��
 * @return ִ��״̬
 */
Status Push(SqStack *S, ElemType e, int stackNumber) {
    // ջ��ʱ�����ʧ��
    if (S->top1 + 1 == S->top2) {
        return ERROR;
    }

    // ��ջ1�����Ԫ��
    if (stackNumber == 1) {
        S->data[++S->top1] = e; // ����Ԫ����ӵ�ջ1��ջ��
    } else { // ��ջ2�����Ԫ��
        S->data[--S->top2] = e; // ����Ԫ����ӵ�ջ2��ջ��
    }

    return OK;
}

/**
 * ����ջ��Ԫ��
 * @param S ջ
 * @param e ����Ԫ��
 * @param stackNumber ջ��
 * @return ִ��״̬
 */
Status Pop(SqStack *S, ElemType *e, int stackNumber) {
    // ջ1����Ԫ��
    if (stackNumber == 1) {
        // ջΪ��ʱ������Ԫ��ʧ��
        if (S->top1 == -1) {
            return ERROR;
        }
        *e = S->data[S->top1--]; // ��ջ��Ԫ�ص�ֵ����eԪ�أ�ջ1��ջ��ָ���1
    } else { // ջ2����Ԫ��
        if (S->top2 == MAXSIZE) {
            return ERROR;
        }
        *e = S->data[S->top2++]; // ��ջ��Ԫ�ص�ֵ����eԪ�أ�ջ2��ջ��ָ���1
    }

    return OK;
}

/**
 * ��ӡ����Ԫ�ص�ֵ
 * @param e Ԫ��
 * @return ִ��״̬
 */
Status visit(ElemType e) {
    printf("%d ", e);
    return OK;
}

/**
 * ��ջ�׿�ʼ����ջ��Ԫ��
 * @param S ջ
 * @return ִ��״̬
 */
Status StackTraverse(SqStack S) {
    int i = 0; // ָʾ��������ָʾջ��ָ���λ��

    printf("ջ1�е�Ԫ��Ϊ��[ ");
    // ָʾ��λ��С��ջ1��ջ��ָ��
    while (i <= S.top1) {
        visit(S.data[i++]); // ��ӡiλ��Ԫ�أ�i����һ��Ԫ���ƶ�
    }
    printf("]\n");

    i = MAXSIZE - 1;
    printf("ջ2�е�Ԫ��Ϊ��[ ");
    while (i >= S.top2) {
        visit(S.data[i--]);
    }
    printf("]\n");
    return OK;
}

int main() {
    int j; // ���ڱ���
    SqStack s; // ջ
    ElemType e; // Ԫ��

    // �����ʼ���ɹ�
    if (InitStack(&s) == OK) {
        // ��ջ1�в���5��Ԫ��
        for (j = 1; j <= 5; j++) {
            Push(&s, j, 1); // ��ջ1��ջ������Ԫ��j
        }

        // ��ջ2�в���5��Ԫ��
        for (j = MAXSIZE; j > MAXSIZE - 5; j--) {
            Push(&s, j, 2); // ��ջ2��ջ������Ԫ��j
        }
    }

    printf("ջ�е�Ԫ�����£�\n");
    StackTraverse(s); // ����ջ��Ԫ��

    Pop(&s, &e, 1); // ����ջ1��ջ��Ԫ��
    printf("������ջ��Ԫ��Ϊ��e = %d\n", e);
    printf("����һ��Ԫ��֮��ջ�Ƿ�Ϊ�գ�%s\n", StackEmpty(&s) == TRUE ? "��" : "��");

    GetTop(&s, &e, 1); // ��ȡջ1��ջ��Ԫ�ص�ֵ
    printf("ջ1��ջ��Ԫ�ص�ֵΪ��e = %d\n", e);

    GetTop(&s, &e, 2); // ��ȡջ1��ջ��Ԫ�ص�ֵ
    printf("ջ2��ջ��Ԫ�ص�ֵΪ��e = %d\n", e);

    printf("ջ�ĳ���Ϊ��%d\n", StackLength(&s)); // ��ȡջ�ĳ���

    ClearStack(&s); // ���ջ��Ԫ��
    printf("���ջ��ջ�Ƿ�Ϊ�գ�%s\n", StackEmpty(&s) == TRUE ? "��" : "��");

    return 0;
}