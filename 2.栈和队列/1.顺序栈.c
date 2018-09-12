// ˳��ջ
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

// ˳��ջ�ṹ
typedef struct {
    ElemType data[MAXSIZE]; // ���ڴ洢Ԫ��ֵ
    int top; // ����ָʾջ��ָ��
}SqStack;

/**
 * ��ʼ��ջ
 * @param S ջ
 * @return ִ��״̬
 */
Status InitStack(SqStack *S) {
    S->top = -1; // ջ��ָ��ָ��-1��ʾջΪ��
    return OK;
}

/**
 * ���ջ��Ԫ��
 * @param S ջ
 * @return ִ��״̬
 */
Status ClearStack(SqStack *S) {
    S->top = -1; // ջ��ָ��ָ��-1��ʾջΪ��
    return OK;
}

/**
 * �ж�ջ�Ƿ�Ϊ��
 * @param S ջ
 * @return ִ��״̬
 */
Status StackEmpty(SqStack *S) {
    if (S->top == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��ȡջ��Ԫ�ظ���
 * @param S ջ
 * @return ִ��״̬
 */
int StackLength(SqStack *S) {
    return S->top + 1;
}

/**
 * ��ȡջ��Ԫ�ص�ֵ���浽Ԫ��e��
 * @param S ջ
 * @param e ���ڴ洢ջ��Ԫ�ص�ֵ
 * @return ִ��״̬
 */
Status GetTop(SqStack *S, ElemType *e) {
    // ջΪ��ʱ����ȡջ��Ԫ��ʧ��
    if (S->top == -1) {
        return ERROR;
    }

    // ��ջ��Ԫ�ص�ֵ��ֵ��eԪ��
    *e = S->data[S->top];

    return OK;
}

/**
 * �����Ԫ��e��ջ��
 * @param S ջ
 * @param e ��Ԫ��
 * @return ִ��״̬
 */
Status Push(SqStack *S, ElemType e) {
    // ջ��ʱ�����ʧ��
    if (S->top == MAXSIZE - 1) {
        return ERROR;
    }
    S->top++; // ջ��ָ���1
    S->data[S->top] = e; // ����Ԫ�ظ�ֵ��ջ��
    return OK;
}

/**
 * ����ջ��Ԫ��
 * @param S ջ
 * @param e ����Ԫ��
 * @return ִ��״̬
 */
Status Pop(SqStack *S, ElemType *e) {
    // ջΪ��ʱ������Ԫ��ʧ��
    if (S->top == -1) {
        return ERROR;
    }
    *e = S->data[S->top]; // ��ջ��Ԫ�ص�ֵ����eԪ��
    S->top--; // ջ��ָ���1
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

    printf("[ ");
    // ָʾ��λ��С��ջ��ָ��
    while (i <= S.top) {
        visit(S.data[i++]); // ��ӡiλ��Ԫ�أ�i����һ��Ԫ���ƶ�
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
        // ��ջ�в���10��Ԫ��
        for (j = 1; j <= 10; j++) {
            Push(&s, j); // ��ջ������Ԫ��j
        }
    }

    printf("ջ�е�Ԫ��Ϊ��");
    StackTraverse(s); // ����ջ��Ԫ��

    Pop(&s, &e); // ����ջ��Ԫ��
    printf("������ջ��Ԫ��Ϊ��e = %d\n", e);
    printf("����һ��Ԫ��֮��ջ�Ƿ�Ϊ�գ�%s\n", StackEmpty(&s) == TRUE ? "��" : "��");

    GetTop(&s, &e); // ��ȡջ��Ԫ�ص�ֵ
    printf("ջ��Ԫ�ص�ֵΪ��e = %d\n", e);

    printf("ջ�ĳ���Ϊ��%d\n", StackLength(&s)); // ��ȡջ�ĳ���

    ClearStack(&s); // ���ջ��Ԫ��
    printf("���ջ��ջ�Ƿ�Ϊ�գ�%s\n", StackEmpty(&s) == TRUE ? "��" : "��");

    return 0;
}