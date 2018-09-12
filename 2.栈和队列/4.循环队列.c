// ���У�ѭ�����У�
#include <stdio.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��
#define MAXSIZE 20 // �洢�ռ��ʼ�����С

typedef int Status; // �������ؽ������
typedef int ElemType; // Ԫ������

// ѭ�����е�˳��洢�ṹ
typedef struct {
    ElemType data[MAXSIZE]; // �洢����Ԫ��
    int front; // ͷָ��
    int rear; // βָ��
} SqQueue;

/**
 * ��ʼ������
 * @param Q ����
 * @return ִ��״̬
 */
Status InitQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

/**
 * ��ն���
 * @param Q ����
 * @return ִ��״̬
 */
Status ClearQueue(SqQueue *Q) {
    Q->front = Q->rear = 0;
    return OK;
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ����
 * @return �����Ƿ�Ϊ��
 */
Status QueueEmpty(SqQueue Q) {
    // ͷָ�����βָ�룬����Ϊ��
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
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/**
 * ��ȡ����ͷԪ��
 * @param Q ����
 * @param e �洢ͷԪ��ֵ
 * @return ִ��״̬
 */
Status GetHead(SqQueue Q, ElemType *e) {
    // ����Ϊ�գ���ȡʧ��
    if (Q.front == Q.rear) {
        return ERROR;
    }

    *e = Q.data[Q.front]; // ������ͷԪ�ش洢��Ԫ��e��
    return OK;
}

/**
 * �ڶ��еĶ�β������Ԫ��
 * @param Q ����
 * @param e ����Ԫ��ֵ
 * @return ִ��״̬
 */
Status EnQueue(SqQueue *Q, ElemType e) {
    // ������ʱ������ʧ��
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return ERROR;
    }

    Q->data[Q->rear] = e; // �ڶ�β������Ԫ��e
    // ��βָ������ƶ������������ת������ͷ��
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

/**
 * ɾ����ͷԪ��
 * @param Q ����
 * @param e �洢����Ԫ�ص�ֵ
 * @return ִ��״̬
 */
Status DeQueue(SqQueue *Q, ElemType *e) {
    // ����ʱ������ʧ��
    if (Q->front == Q->rear) {
        return ERROR;
    }

    *e = Q->data[Q->front]; // ������ͷԪ�ش洢��Ԫ��e��
    // ��ͷָ������ƶ������������ת������ͷ��
    Q->front = (Q->front + 1) % MAXSIZE;
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
Status QueueTravel(SqQueue Q) {
    int i; // ���ڱ���Ԫ�ص��±�
    i = Q.front; // ָ���ͷָ��

    printf("[ ");
    // ��ָ�벻���ڶ�βָ��
    while (i != Q.rear) {
        visit(Q.data[i]); // ��ӡ����Ԫ�ص�ֵ
        i = (i + 1) % MAXSIZE; // ��ȡ�¸�Ԫ�ص��±�
    }
    printf("]\n");
    return OK;
}

int main() {
    Status status; // ִ��״̬
    int i = 0, j;
    ElemType e; // Ԫ��ֵ
    SqQueue Q; // ����

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