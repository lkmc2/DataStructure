// ���Ա���ʽ�洢�ṹ��
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

typedef int Status; // �������ؽ������
typedef int ElemType; // Ԫ������

// ����ڵ�
typedef struct Node {
    ElemType data; // �������Ԫ��
    struct Node *next; // ָ����һ���ڵ��ָ��
} Node;

typedef struct Node *LinkList; // ���Ա�����ṹ

/**
 * ��ʼ�����Ա�
 * @param L ���Ա�
 * @return ִ��״̬
 */
Status InitList(LinkList *L) {
    *L = (LinkList) malloc(sizeof(Node)); // Ϊ�������洢�ռ�
    // �洢�ռ����ʧ��
    if (!(*L)) {
        return ERROR;
    }

    (*L)->next = NULL; // ��ͷ�ڵ�ָ��Ϊ��
    return OK;
}

/**
 * �ж����Ա��Ƿ�Ϊ��
 * @param L ���Ա�
 * @return ִ��״̬
 */
Status ListEmpty(LinkList L) {
    // �����к���Ԫ�أ���Ϊ��
    if (L->next) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * ������Ա�
 * @param L ���Ա�
 * @return ִ��״̬
 */
Status ClearList(LinkList *L) {
    LinkList p, q; // p��q���ڱ�����ɾ��L�е����нڵ�

    p = (*L)->next; // pָ��L�ĵ�һ���ڵ�

    // ����L���������Ԫ��
    while (p) {
        q = p->next; // qָ��p����һ���ڵ�
        free(p); // �ͷ�p�ڵ�
        p = q; // ��pָ��q�ڵ㣨�����ԭ��λ������ƶ�һ��λ�ã�
    }
    (*L)->next = NULL; // ͷ�ڵ�ָ�����ÿ�
    return OK;
}

/**
 * ��ȡ���Ա���
 * @param L ���Ա�
 * @return ���Ա���
 */
int ListLength(LinkList L) {
    int i = 0; // ����ͳ��Ԫ�ظ���

    LinkList p = L->next; // pָ��L�ĵ�һ���ڵ�

    // ����L���������Ԫ��
    while (p) {
        i++; // ͳ������1
        p = p->next; // �ڵ�����ƶ�
    }
    return i; // ����������Ԫ�ظ���
}

/**
 * ��ȡ���Ա���ָ��λ�õ�Ԫ��ֵ
 * @param L ���Ա�
 * @param i ��ȡԪ��λ���±�
 * @param e ��ȡԪ��ֵ
 * @return ִ��״̬
 */
Status GetElem(LinkList L, int i, ElemType *e) {
    int j; // ������
    LinkList p; // ���ڱ�������Ԫ��
    j = 1; // ��ʼ�±�Ϊ1
    p = L->next; // pָ��L�ĵ�һ��Ԫ��

    // ������L���������Ԫ�أ�����δ����iλ��
    while (p && j < i) {
        p = p->next; // pָ����һ���ڵ�
        j++; // ��������1
    }

    // p����һ���ڵ�������j����iλ�ã�����i��Ԫ�ز����ڣ�
    if (!p || j > i) {
        return ERROR;
    }
    // ��i�ڵ�����ݸ�ֵ��eԪ��
    *e = p->data;
    return OK;
}

/**
 * ��λԪ��e�����Ա��е�λ��
 * �ҵ��ĸ�Ԫ�ط���Ԫ���±꣬δ�ҵ���Ԫ�ط���0
 * @param L ���Ա�
 * @param e Ԫ��
 * @return Ԫ�������Ա��е��±�
 */
int LocateElem(LinkList L, ElemType e) {
    int i = 0; // ��¼Ԫ�ص��±�
    LinkList p = L->next; // pָ��L�ĵ�һ��Ԫ��

    // ����L���������Ԫ��
    while (p->next) {
        i++; // �±��1
        // p�ڵ�Ԫ�ص�ֵ����e
        if (p->data == e) {
            return i; // ����eԪ�ض�Ӧ���±�
        }
        p = p->next; // pָ����һ��Ԫ��
    }
    return 0;
}

/**
 * �����Ա���ָ��λ�ò�����Ԫ��
 * @param L ���Ա�
 * @param i ����λ��
 * @param e �����ֵ
 * @return ִ��״̬
 */
Status ListInsert(LinkList *L, int i, ElemType e) {
    int j; // �±������
    LinkList p, s; // p��������L�Ľڵ㣬s���������½ڵ�

    j = 1; // ��������ʼֵΪ1
    p = *L; // pָ������ͷ�ڵ�

    // ����L���������Ԫ�أ������±�δ�ƶ���iλ��
    while (p && j < i) {
        p = p->next; // p����ƶ�
        j++; // �±��������1
    }

    // p�ڵ�δ�գ����±������������Χ������i��Ԫ�ز����ڣ�����ʧ�ܣ�
    if (!p || j > i) {
        return ERROR;
    }

    s = (LinkList) malloc(sizeof(Node)); // �����½ڵ�
    s->data = e; // ���½ڵ㸳ֵΪe��ֵ
    s->next = p->next; // �½ڵ�s��ָ��ָ�����λ�õ���һ���ڵ�
    p->next = s; // ����λ�õ���һ���ڵ�ָ���½ڵ�s
    return OK;
}

/**
 * ɾ�����Ա���ָ��λ�õ�Ԫ��
 * ɾ��λ�õ�ֵ�����浽Ԫ��e��
 * @param L ���Ա�
 * @param i ɾ��λ�õ��±�
 * @param e ɾ��λ�õ�ֵ
 * @return ִ��״̬
 */
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int j; // �±������
    LinkList p, q; // p��������L�Ľڵ㣬s����ָ��ɾ���Ľڵ�

    j = 1; // ��������ʼֵΪ1
    p = *L; // pָ������ͷ�ڵ�

    // ����L���������Ԫ�أ������±�δ�ƶ���iλ��
    while (p->next && j < i) {
        p = p->next; // p����ƶ�
        j++; // �±��������1
    }

    // p�ڵ�δ�գ����±������������Χ������i��Ԫ�ز����ڣ�ɾ��ʧ�ܣ�
    if (!(p->next) || j > i) {
        return ERROR;
    }

    q = p->next; // qָ��ɾ���ڵ�
    p->next = q->next; // pָ��ɾ���ڵ�ĺ�һ���ڵ�
    *e = q->data; // ����ɾ���ڵ��ֵ��ֵ��eԪ��
    free(q); // �ͷű�ɾ���ڵ�Ŀռ�
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
 * ����������Ա�������Ԫ��
 * @param L ���Ա�
 * @return ִ��״̬
 */
Status ListTravel(LinkList L) {
    LinkList p = L->next; // pָ��L�ĵ�һ���ڵ�

    printf("[ ");
    // ����L���������Ԫ��
    while (p) {
        visit(p->data); // ��ӡ����Ԫ��
        p = p->next; // p����ƶ�
    }
    printf("]\n");
    return OK;
}

/**
 * �������n��Ԫ�أ���������ͷ���ĵ������Ա�ͷ�巨��
 * @param L ���Ա�
 * @param n ����Ԫ�ظ���
 */
void CreateListHead(LinkList *L, int n) {
    LinkList p; // ���������½ڵ�
    int i; // ���ڱ����±�

    srand(time(0)); // �������������
    *L = (LinkList) malloc(sizeof(Node)); // ��������ͷ�ڵ�ĵ�����
    (*L)->next = NULL; // ������ָ���ÿ�

            // �����Ա�L����n��100���ڵ������
    for (i = 0; i < n; i++) {
        p = (LinkList) malloc(sizeof(Node)); // �����½ڵ�
        p->data = rand() % 100 + 1; // ����100���ڵ����������ֵ���½ڵ�
        p->next = (*L)->next; // ��Ԫ��ָ��ͷ�ڵ����һ��Ԫ��
        (*L)->next = p; // ͷ�ڵ�ָ����Ԫ��
    }
}

/**
 * �������n��Ԫ�أ���������ͷ���ĵ������Ա�β�巨��
 * @param L ���Ա�
 * @param n ����Ԫ�ظ���
 */
void CreateListTail(LinkList *L, int n) {
    LinkList p, r; // p���������½ڵ㣬r����ָ��L�ı�β
    int i; // ���ڱ����±�

    srand(time(0)); // �������������
    *L = (LinkList) malloc(sizeof(Node)); // ��������ͷ�ڵ�ĵ�����
    r = *L; // rָ��L�ı�β

    // �����Ա�L����n��100���ڵ������
    for (i = 0; i < n; i++) {
        p = (LinkList) malloc(sizeof(Node)); // �����½ڵ�
        p->data = rand() % 100 + 1; // ����100���ڵ����������ֵ���½ڵ�
        r->next = p; // ��βָ���½ڵ�
        r = p; // �½ڵ��Ϊ��β
    }
    r->next = NULL; // ���ñ�βָ���ÿ�
}

int main() {
    LinkList L; // ���Ա�

    Status status; // ִ��״̬
    ElemType e; // ���Ա�Ԫ��
    int result; // ���н��
    int j, k; // ���ڱ���Ԫ�ص��±�

    status = InitList(&L); // ��ʼ�����Ա�
    printf("��ʼ�����Ա�L��L�ĳ���Ϊ��%d\n", ListLength(L));

    result = ListEmpty(L); // ��ȡ���Ա��Ƿ�Ϊ��
    printf("L�Ƿ�Ϊ�գ�%s\n", result == TRUE ? "��" : "��");

    /*** ��L�ı�ͷ����5��Ԫ�� ***/
    for (j = 1; j <= 5; j++) {
        status = ListInsert(&L, 1, j); // �����Ա��ͷ����ֵ
    }
    printf("��L��ͷ���β���1~5��L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    printf("����5��Ԫ�غ�L�ĳ���Ϊ��%d\n", ListLength(L));

    result = ListEmpty(L); // ��ȡ���Ա��Ƿ�Ϊ��
    printf("L�Ƿ�Ϊ�գ�%s\n", result == TRUE ? "��" : "��");

    /*** ���L�е�Ԫ�� ***/
    status = ClearList(&L); // ������Ա�
    printf("������Ա�L��L�ĳ���Ϊ��%d\n", ListLength(L));

    result = ListEmpty(L); // ��ȡ���Ա��Ƿ�Ϊ��
    printf("L�Ƿ�Ϊ�գ�%s\n", result == TRUE ? "��" : "��");

    /*** ��L�ı�β����10��Ԫ�� ***/
    for (j = 1; j <= 10; j++) {
        ListInsert(&L, j, j); // �����Ա��β����ֵ
    }
    printf("��L��β���β���1~10��L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    printf("����10��Ԫ�غ�L�ĳ���Ϊ��%d\n", ListLength(L));

    /*** ��L�ı�ͷ����һ��Ԫ�� ***/
    ListInsert(&L, 1, 33); // �����Ա��ͷ����Ԫ��33

    printf("��L��ͷ����Ԫ��33��L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    printf("����Ԫ��33��L�ĳ���Ϊ��%d\n", ListLength(L));

    /*** ��ȡ��5��Ԫ�ص�ֵ ***/
    GetElem(L, 5, &e); // ��ȡL���±�Ϊ5��Ԫ�ص�e��
    printf("L�е�5��Ԫ�ص�ֵΪ��%d\n", e);

    /*** ��ȡ�±�Ϊ3��4Ԫ�ص�ֵ ***/
    for (j = 3; j <= 4; j++) {
        k = LocateElem(L, j); // ��ȡL���±�Ϊj��Ԫ�ص�ֵ
        if (k) {
            printf("��%d��Ԫ�ص�ֵΪ��%d\n", k, j);
        } else {
            printf("û��ֵΪ%d��Ԫ��\n", j);
        }
    }

    /*** ɾ�����ж��Ԫ�� ***/
    k = ListLength(L); // kΪ��
    for (j = k + 1; j >= k; j--) {
        status = ListDelete(&L, j, &e); // ɾ��L�е�j��Ԫ�أ�����ɾ��Ԫ�ص�ֵ��ֵ��e
        if (status == ERROR) {
            printf("ɾ����%d��Ԫ��ʧ��\n", j);
        } else {
            printf("ɾ����%d��Ԫ�ص�ֵΪ��%d\n", j, e);
        }
    }
    printf("ɾ������Ԫ�غ�L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    /*** ɾ��L�е�5��Ԫ�� ***/
    j = 5;
    ListDelete(&L, j, &e); // ɾ��L�е�j��Ԫ�أ�����ɾ��Ԫ�ص�ֵ��ֵ��e
    printf("ɾ����%d��Ԫ�ص�ֵΪ��%d\n", j, e);

    printf("ɾ����%d��Ԫ�غ�L�е�ֵΪ��",j);
    ListTravel(L); // �������Ա�

    /*** ���L��Ԫ��,��ʹ��ͷ�巨����20��Ԫ�� ***/
    status = ClearList(&L); // ��ձ���Ԫ��
    printf("���L��Ԫ�غ�L�ĳ���Ϊ��%d\n", ListLength(L));

    CreateListHead(&L, 20); // ʹ��ͷ�巨����20�����Ԫ��
    printf("ʹ��ͷ�巨����20�����Ԫ�غ�L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    /*** ���L��Ԫ��,��ʹ��β�巨����20��Ԫ�� ***/
    status = ClearList(&L); // ��ձ���Ԫ��
    printf("���L��Ԫ�غ�L�ĳ���Ϊ��%d\n", ListLength(L));

    CreateListTail(&L, 20); // ʹ��β�巨����20�����Ԫ��
    printf("ʹ��β�巨����20�����Ԫ�غ�L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    return 0;
}