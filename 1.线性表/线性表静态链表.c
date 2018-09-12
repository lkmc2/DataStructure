// ���Ա���̬����
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��

#define MAXSIZE 100 // ��ʼ����洢�ռ�

typedef int Status; // �������ؽ������
typedef char ElemType; // Ԫ������

/**
 * ��̬����ṹ
 * 1. �������һ��Ԫ�ص�cur������ŵ�һ������Ԫ�ص��±꣬
 *    �൱��ͷ�ڵ㣬ָ��0ʱ��ʾ����Ϊ��
 * 2. ����0�±�Ԫ�ص�cur���������һ�����ô洢λ�õ��±꣬
 *    ����һ������ڵ��λ��
 */
typedef struct {
    ElemType data; // ���Ԫ��ֵ
    int cur; // ָ����һ���ڵ���±꣬Ϊ0��ʾ��ָ�򣬼���������ĩβ
} Component, StaticLinkList[MAXSIZE];

/**
 * ��ʼ����̬����
 * ��һά����L�ķ������ӳ�һ����������L[0].curΪͷָ�룬0��ʾ��ָ��
 * @param L ��̬����
 * @return ִ��״̬
 */
Status InitList(StaticLinkList L) {
    int i; // ���ڱ�����Ԫ��

    for (i = 0; i < MAXSIZE - 1; i++) {
        L[i].cur = i + 1; // ����ÿ��λ�õ�ָ��ָ����һ��Ԫ�ص�λ��
    }
    // ���������һ��Ԫ��ָ��0����ʾ��ǰ��һ������Ľڵ��±�Ϊ0����ʱ����Ϊ�գ�
    L[MAXSIZE - 1].cur = 0;
    return OK;
}

/**
 * ��ȡ��һ�����ô洢λ�õ��±�
 * @param L ��̬����
 * @return ��һ�����ô洢λ�õ��±꣬�޿��ô洢λ��ʱ����0
 */
int Malloc_SSL(StaticLinkList L) {
    int i = L[0].cur; // L��0λ��cur���ֵ������һ�����ô洢λ�õ��±�

    // ��ǰ��̬����δ��
    if (L[0].cur) {
        L[0].cur = L[i].cur; // ��ȡ��һ�����ô洢λ�õ��±�
    }
    return i; // ������һ�����ô洢λ�õ��±�
}

/**
 * �ͷ��±�Ϊk��Ԫ�ص���������
 * �����±�Ϊk��Ԫ�س�Ϊ��һ���ɲ���ڵ�
 * @param L ��̬����
 * @param k Ԫ���±�
 */
void Free_SSL(StaticLinkList L, int k) {
    L[k].cur = L[0].cur; // ��k�±�Ԫ�ص���һ��Ԫ��ָ��ԭ������һ���ɲ���ڵ�
    L[0].cur = k; // ��k�±��Ԫ�س�Ϊ��һ���ɲ���ڵ�
}

/**
 * ��ȡ����������
 * @param L ��������
 * @return ����������
 */
int ListLength(StaticLinkList L) {
    int j = 0; // ����ͳ��Ԫ�ظ���
    int i = L[MAXSIZE - 1].cur; // ��ȡ��һ��Ԫ�ص��±�

    // ��������Ԫ��
    while (i) {
        i = L[i].cur; // ��ȡ��һ��Ԫ�ص��±�
        j++; //ͳ�Ƹ�����1
    }
    return j; // ����������
}

/**
 * ������������ָ��λ�ò�����Ԫ��
 * @param L ��������
 * @param i ����λ��
 * @param e �����ֵ
 * @return ִ��״̬
 */
Status ListInsert(StaticLinkList L, int i, ElemType e) {
    int j, t; // j����һ���ɲ���λ�õ��±꣬t���ڱ���forѭ��

    int k = MAXSIZE - 1; // ���һ��Ԫ�ص��±�

    // ����λ���±�Խ�磬����ʧ��
    if (i < 1 || i > ListLength(L) + 1) {
        return ERROR;
    }

    j = Malloc_SSL(L); // ��ȡ��һ���ɲ���λ�õ��±�

    // ��������δ����j��Ϊ0��
    if (j) {
        L[j].data = e; // ��e��ֵ����һ���ɲ���ڵ��ֵ��j�±��Ԫ�ر�ʾ�½ڵ㣩

        // �������������ҵ�����λ�õ���һ���ڵ�
        for (t = 1; t <= i - 1; t++) {
            k = L[k].cur; // ��ȡ��һ��Ԫ�ص�����
        }

        L[j].cur = L[k].cur; // �½ڵ��ָ�����λ��ǰһ��Ԫ�ص���һ��Ԫ�أ���ԭ��iλ�õĽڵ㣩
        L[k].cur = j; // ����λ�õ���һ���ڵ�ָ���½ڵ�
        return OK;
    }
    return ERROR;
}

/**
 * ɾ�������Ա���ָ��λ�õ�Ԫ��
 * @param L ��������
 * @param i ɾ��λ�õ��±�
 * @return ִ��״̬
 */
Status ListDelete(StaticLinkList L, int i) {
    int j; // ���ڱ���Ԫ��

    int k = MAXSIZE - 1; // ���һ��Ԫ�ص��±�

    // ����λ���±�Խ�磬����ʧ��
    if (i < 1 || i > ListLength(L) + 1) {
        return ERROR;
    }

    // �������������ҵ�ɾ��λ�õ���һ���ڵ�
    for (j = 1; j <= i - 1; j++) {
        k = L[k].cur; // ��ȡ��һ��Ԫ�ص��±�
    }

    j = L[k].cur; // ��ȡ��ɾ��Ԫ�ص��±�
    L[k].cur = L[j].cur; // ����ɾ���ڵ����һ���ڵ㡿ָ�򡾱�ɾ���ڵ����һ���ڵ㡿����������ɾ���ڵ㣩
    Free_SSL(L, j); // �ͷű�ɾ���ڵ�
    return OK;
}

/**
 * ��ӡ����Ԫ��
 * @param e Ԫ��ֵ
 * @return ִ��״̬
 */
Status visit(ElemType e) {
    printf("%c ", e);
    return OK;
}

/**
 * ���������������������Ԫ��
 * @param L ��������
 * @return ִ��״̬
 */
Status ListTravel(StaticLinkList L) {
    int i = L[MAXSIZE - 1].cur; // ��ȡ�����һ��Ԫ�ص��±�

    printf("[ ");
    // ��������������Ԫ��
    while (i) {
        visit(L[i].data); // ��ӡ�����ڵ��ֵ
        i = L[i].cur; // ��ȡ��һ���ڵ���±�
    }
    printf("]\n");
    return OK;
}

int main() {
    StaticLinkList L; // ��������
    Status status; // ִ��״̬

    status = InitList(L); // ��ʼ����������

    printf("��ʼ����L�ĳ���Ϊ��%d\n", ListLength(L));

    status = ListInsert(L, 1, 'F');
    status = ListInsert(L, 1, 'E');
    status = ListInsert(L, 1, 'D');
    status = ListInsert(L, 1, 'B');
    status = ListInsert(L, 1, 'A');

    printf("��L�ı�ͷ�ֱ�������Ԫ�غ�L�е�ֵΪ��");
    ListTravel(L); // ��������Ԫ��
    printf("L�ĳ���Ϊ��%d\n", ListLength(L));

    status = ListInsert(L, 3, 'C'); // �ڵ�����λ�ò���CԪ��
    printf("�ڵ�����λ�ò���һ��Ԫ��C��L�е�ֵΪ��");
    ListTravel(L); // ��������Ԫ��
    printf("L�ĳ���Ϊ��%d\n", ListLength(L));

    status = ListDelete(L, 4); // ɾ�����ĸ�λ�õ�Ԫ��
    printf("ɾ�����ĸ�λ�õ�Ԫ��D������L�е�ֵΪ��");
    ListTravel(L); // ��������Ԫ��
    printf("L�ĳ���Ϊ��%d\n", ListLength(L));

    return 0;
}

