// ��ջ
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

typedef int Status; // �������ؽ������
typedef int ElemType; // Ԫ������

// ��ջ�ڵ�
typedef struct StackNode {
    ElemType data; // Ԫ��ֵ
    struct StackNode *next; // ָ����һ���ڵ��ָ��
}StackNode, *LinkStackPtr;

// ��ջ�ṹ
typedef struct {
    LinkStackPtr top; // ջ��ָ��
    int count; // ջ��Ԫ�ظ���
} LinkStack;

/**
 * ��ʼ��ջ
 * @param S ջ
 * @return ִ��״̬
 */
Status InitStack(LinkStack *S) {
    S->top = (LinkStackPtr) malloc(sizeof(StackNode)); // Ϊջ��ָ�����ռ�
    // ����ռ�ʧ�ܣ���ʼ������
    if (!S->top) {
        return ERROR;
    }

    S->top = NULL; // ջ��ָ���ÿ�
    S->count = 0; // ջ��Ԫ��Ϊ0
    return OK;
}

/**
 * ���ջ��Ԫ��
 * @param S ջ
 * @return ִ��״̬
 */
Status ClearStack(LinkStack *S) {
    LinkStackPtr p, q; // p����ָ����һ��Ԫ�أ�qָ��ɾ��Ԫ��

    p = S->top; // pָ��ջ��
    // ��ջ�л���Ԫ��ʱ
    while (p) {
        q = p; // qָ��ǰԪ��
        p = p->next; // pָ����һ��Ԫ��
        free(q); // ɾ��qԪ��
    }
    S->count = 0; // ����ջ��Ԫ�ظ���Ϊ0
    return OK;
}

/**
 * �ж�ջ�Ƿ�Ϊ��
 * @param S ջ
 * @return ִ��״̬
 */
Status StackEmpty(LinkStack *S) {
    // ջ��Ԫ�ظ���Ϊ0
    if (S->count == 0) {
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
Status StackLength(LinkStack *S) {
    return S->count; // ����ջ��Ԫ�ظ���
}

/**
 * ��ȡջ��Ԫ�ص�ֵ���浽Ԫ��e��
 * @param S ջ
 * @param e ���ڴ洢ջ��Ԫ�ص�ֵ
 * @return ִ��״̬
 */
Status GetTop(LinkStack *S, ElemType *e) {
    // ջ��Ԫ��Ϊ�գ���ȡʧ��
    if (S->count == 0) {
        return ERROR;
    }

    *e = S->top->data; // ��ջ��Ԫ�ص�ֵ�浽Ԫ��e��
    return OK;
}

/**
 * �����Ԫ��e��ջ��
 * @param S ջ
 * @param e ��Ԫ��
 * @return ִ��״̬
 */
Status Push(LinkStack *S, ElemType e) {
    // �����½ڵ�
    LinkStackPtr s = (LinkStackPtr) malloc(sizeof(StackNode));

    // �ڵ㴴��ʧ��
    if (!s) {
        return ERROR;
    }

    s->data = e; // ����Ԫ��ֵ��ֵ���½ڵ�
    s->next = S->top; // �����½ڵ����һ��Ԫ��ָ��ջ��Ԫ��
    S->top = s; // ����ջ��ָ��ָ���½ڵ�
    S->count++; // ջ��Ԫ�ظ�����1
    return OK;
}

/**
 * ����ջ��Ԫ��
 * @param S ջ
 * @param e ����Ԫ��
 * @return ִ��״̬
 */
Status Pop(LinkStack *S, ElemType *e) {
    LinkStackPtr p; // ָ��ɾ��Ԫ�ص�ָ��

    // ջ��Ԫ��Ϊ�գ�ɾ��ʧ��
    if (S->count == 0) {
        return ERROR;
    }

    *e = S->top->data; // ��ջ��Ԫ�ص�ֵ��ֵ��Ԫ��e
    p = S->top; // pָ��ɾ���ڵ�
    S->top = S->top->next; // �����µ�ջ��Ԫ��Ϊ��ɾ���ڵ����һ��Ԫ��
    free(p); // ɾ��ջ���ڵ�
    S->count--; // ջ��Ԫ�ظ�����1

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
 * ��ջ����ʼ����ջ��Ԫ��
 * @param S ջ
 * @return ִ��״̬
 */
Status StackTravel(LinkStack *S) {
    LinkStackPtr p; // ���ڱ���ջ��Ԫ�ص�ָ��

    p = S->top; // pָ��ջ��
    printf("[ ");
    // ��ջ�л���Ԫ��
    while (p) {
        visit(p->data); // ��ӡ��Ԫ�ص�ֵ
        p = p->next; // pָ����һ���ڵ�
    }
    printf("]\n");
    return OK;
}

int main() {
    int j; // ���ڱ���
    LinkStack s; // ջ
    ElemType e; // Ԫ��

    // �����ʼ���ɹ�
    if (InitStack(&s) == OK) {
        // ��ջ�в���10��Ԫ��
        for (j = 1; j <= 10; j++) {
            Push(&s, j); // ��ջ������Ԫ��j
        }
    }

    printf("ջ�е�Ԫ��Ϊ��");
    StackTravel(&s); // ����ջ��Ԫ��

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