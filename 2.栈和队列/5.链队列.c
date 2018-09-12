// ���У������У�
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

typedef int Status; // �������ؽ������
typedef int ElemType; // Ԫ������

// ���нڵ�
typedef struct QNode {
    ElemType data; // Ԫ��ֵ
    struct QNode *next; // ָ����һ���ڵ��ָ��
} QNode, *QueuePtr;

// �����нṹ
typedef struct {
    QueuePtr front, rear; // ��ͷָ�롢��βָ��
} LinkQueue;

/**
 * ��ʼ������
 * @param Q ����
 * @return ִ��״̬
 */
Status InitQueue(LinkQueue *Q) {
    // Ϊ��ͷ�Ͷ�βָ������ڴ�
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));

    // �ڴ����ʧ�ܣ���������
    if (!Q->front || !Q->rear) {
        exit(OVERFLOW);
    }

    Q->front->next = NULL; // ��ͷ�ڵ�ָ��NULL
    return OK;
}

/**
 * ���ٶ���
 * @param Q ����
 * @return ִ��״̬
 */
Status DestroyQueue(LinkQueue *Q) {
    // �������л���Ԫ��
    while (Q->front) {
        Q->rear = Q->front->next;// ��βָ��ָ���ͷָ�����һ��Ԫ��
        free(Q->front); // �ͷŶ�ͷָ�����ڽڵ�
        Q->front = Q->rear; // ��ͷָ��ָ���βָ�루��ԭ������һ��Ԫ�أ�
    }
    return OK;
}

/**
 * ��ն���
 * @param Q ����
 * @return ִ��״̬
 */
Status ClearQueue(LinkQueue *Q) {
    QueuePtr p, q; // p�����������нڵ㣬q����ָ��ɾ���Ľڵ�

    Q->rear = Q->front; // ��βָ��ָ���ͷָ��
    p = Q->front->next; // pָ���ͷָ�����һ���ڵ�
    Q->front->next = NULL; // ��ͷָ�����һ���ڵ�ָ��NULL����ʾɾ��֮�������Ԫ�أ�

    // �������л���Ԫ�أ��ͷ�ͷ�ڵ�֮������нڵ�
    while (p) {
        q = p; // q�ڵ�ָ��ɾ���ڵ�
        p = p->next; // pָ����е���һ���ڵ�
        free(q); // �ͷ�q�ڵ�
    }
    return OK;
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ����
 * @return �����Ƿ�Ϊ��
 */
Status QueueEmpty(LinkQueue Q) {
    // ͷָ���βָ��λ����ȣ�����Ϊ��
    if (Q.front == Q.rear) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��ȡ���г���
 * @param Q ����
 * @return ���г���
 */
int QueueLength(LinkQueue Q) {
    int i = 0; // ����ͳ�ƶ��г��ȵļ�����
    QueuePtr p; // ���ڱ������е�Ԫ��
    p = Q.front; // pָ���ͷ�ڵ�

    // ��pû���ƶ�����βָ��λ��
    while (p != Q.rear) {
        i++; // ��������1
        p = p->next; // p�ƶ������е���һ���ڵ�
    }
    return i; // ���ض��г���
}

/**
 * ��ȡ����ͷԪ��
 * @param Q ����
 * @param e �洢ͷԪ��ֵ
 * @return ִ��״̬
 */
Status GetHead(LinkQueue Q, ElemType *e) {
    QueuePtr p;

    // ����Ϊ�գ���ȡʧ��
    if (Q.front == Q.rear) {
        return ERROR;
    }

    p = Q.front->next; // pָ����еĵ�һ��Ԫ��
    *e = p->data; // ������ͷԪ�ص�ֵ��ֵ��eԪ��
    return OK;
}

/**
 * �ڶ��еĶ�β������Ԫ��
 * @param Q ����
 * @param e ����Ԫ��ֵ
 * @return ִ��״̬
 */
Status EnQueue(LinkQueue *Q, ElemType e) {
    // ���½ڵ����ռ�
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));

    // ����ռ�ʧ�ܣ���������
    if (!s) {
        exit(OVERFLOW);
    }

    s->data = e; // ��ֵ��ֵ���½ڵ�
    s->next = NULL; // �½ڵ�ָ��NULL
    Q->rear->next = s; // ��βָ�����һ��Ԫ��ָ���½ڵ�
    Q->rear = s; // ��βָ��ָ���½ڵ㣨�½ڵ��Ϊ��βָ���ָ��Ľڵ㣩
    return OK;
}

/**
 * ɾ����ͷԪ��
 * @param Q ����
 * @param e �洢����Ԫ�ص�ֵ
 * @return ִ��״̬
 */
Status DeQueue(LinkQueue *Q, ElemType *e) {
    QueuePtr p; // ����ָ��ɾ���ڵ�

    // ����Ϊ�գ�����ʧ��
    if (Q->front == Q->rear) {
        return ERROR;
    }

    p = Q->front->next; // pָ����еĵ�һ��Ԫ��
    *e = p->data; // ������ͷ�ڵ��ֵ��ֵ��Ԫ��e
    Q->front->next = p->next; // ͷָ�����һ���ڵ�ָ�����¸��ڵ㣨����ͷ�ڵ㣩

    // �����ɾ���ڵ��Ƕ�βָ��ָ��Ľڵ㣨ɾ�������Ϊ�գ�
    if (Q->rear == p) {
        Q->rear = Q->front; // ��βָ��ָ���ͷָ��
    }
    free(p); // �ͷŶ�ͷ�ڵ�
    return OK;
}

/**
 * ��ӡ����Ԫ��
 * @param e Ԫ��ֵ
 * @return ִ��״̬
 */
Status visit(ElemType e) {
    printf("%d ", e);
    return OK;
}

/**
 * ���������е�Ԫ��
 * @param Q ����
 * @return ִ��״̬
 */
Status QueueTravel(LinkQueue Q) {
    QueuePtr p; // ���ڱ��������еĽڵ�

    p = Q.front->next; // pָ��ͷ�ڵ�

    printf("[ ");
    // �������л���Ԫ��
    while (p) {
        visit(p->data); // ��ӡ��ǰ�ڵ��ֵ
        p = p->next; // p�ƶ���������һ��λ��
    }
    printf("]\n");
    return OK;
}

int main() {
    Status status; // ִ��״̬
    int j; // j��������
    ElemType e; // Ԫ��ֵ
    LinkQueue Q; // ����

    /*** ��ʼ������ ***/
    InitQueue(&Q); // ��ʼ������
    printf("��ʼ�����к󣬶����Ƿ�Ϊ�գ�%s\n", QueueEmpty(Q) == TRUE ? "��" : "��");

    /*** ������в���10��Ԫ�� ***/
    for (j = 1; j <=10; ++j) {
        EnQueue(&Q, j); // ��Ԫ��j�������
    }
    printf("����10��Ԫ�غ���е�ֵΪ��");
    QueueTravel(Q); // ��������
    printf("���еĳ���Ϊ��%d\n", QueueLength(Q)); // ��ȡ���г���
    printf("����10��Ԫ�غ󣬶����Ƿ�Ϊ�գ�%s\n", QueueEmpty(Q) == TRUE ? "��" : "��");

    /*** ɾ�������е����Ԫ�أ�����ӡ��Ӧ��ֵ ***/
    printf("��ʼɾ��Ԫ�أ�\n");
    for (j = 0; j < 5; ++j) {
        DeQueue(&Q, &e); // ɾ����ͷԪ�أ���ֵ�浽e��
        printf("Ԫ��%d����\n", e);
    }
    printf("5��Ԫ�س��Ӻ󣬶����е�ֵΪ��");
    QueueTravel(Q); // ��������
    printf("���еĳ���Ϊ��%d\n", QueueLength(Q));  // ��ȡ���г���

    /*** ��ȡ����ͷԪ�ص�ֵ ***/
    status = GetHead(Q, &e); // ��ȡ����ͷԪ��
    if (status) {
        printf("����ͷԪ��Ϊ��%d\n", e);
    }

    /*** ��ն���Ԫ�� ***/
    ClearQueue(&Q); // ��ն���Ԫ��
    printf("��ն��к󣬶����Ƿ�Ϊ�գ�%s\n", QueueEmpty(Q) == TRUE ? "��" : "��");
    printf("�����е�Ԫ��Ϊ��");
    QueueTravel(Q); // ����Ԫ��
    return 0;
}