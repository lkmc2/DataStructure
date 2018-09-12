// ���Ա�˳��洢�ṹ��
#include <stdio.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

#define MAXSIZE 20 // ��ʼ����洢�ռ�

typedef int Status; // �������ؽ������
typedef int ElemType; // Ԫ������

// ���Ա�ṹ
typedef struct {
    ElemType data[MAXSIZE]; // ������Ա�Ԫ�ص�����
    int length; // ���Ա���
} SqList;

/**
 * ��ʼ�����Ա�
 * @param L ���Ա�
 * @return ִ��״̬
 */
Status InitList(SqList *L) {
    L->length = 0;
    return OK;
}

/**
 * �ж����Ա��Ƿ�Ϊ��
 * @param L ���Ա�
 * @return ִ��״̬
 */
Status ListEmpty(SqList L) {
    if (L.length == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ������Ա�
 * @param L ���Ա�
 * @return ִ��״̬
 */
Status ClearList(SqList *L) {
    // �������Ա���Ϊ0
    L->length = 0;
    return OK;
}

/**
 * ��ȡ���Ա���
 * @param L ���Ա�
 * @return ���Ա���
 */
int ListLength(SqList L) {
    return L.length;
}

/**
 * ��ȡ���Ա���ָ��λ�õ�Ԫ��ֵ
 * @param L ���Ա�
 * @param i ��ȡԪ��λ���±�
 * @param e ��ȡԪ��ֵ
 * @return ִ��״̬
 */
Status GetElem(SqList L, int i, ElemType *e) {
    // ���鳤��Ϊ�գ����±겻�����鷶Χ��
    if (L.length == 0 || i < 1 || i > L.length) {
        return ERROR;
    }
    // ��ȡ��Ӧ�±�Ԫ�ص�ֵ����ֵ��e
    *e = L.data[i - 1];
    return OK;
}

/**
 * ��λԪ��e�����Ա��е�λ��
 * �ҵ��ĸ�Ԫ�ط���Ԫ���±꣬δ�ҵ���Ԫ�ط���0
 * @param L ���Ա�
 * @param e Ԫ��
 * @return Ԫ�������Ա��е��±�
 */
int LocateElem(SqList L, ElemType e) {
    int i; // Ԫ���±�
    // ���Ա���Ϊ��
    if (L.length == 0) {
        return 0;
    }

    // �������Ա�Ѱ��Ԫ��e
    for (i = 0; i < L.length; i++) {
        // �ҵ�Ԫ��e���˳�ѭ��
        if (L.data[i] == e) {
            break;
        }
    }

    // �±�������Ա��ȣ�δ�ҵ���Ԫ��
    if (i >= L.length) {
        return 0;
    }

    // ����Ԫ�������Ա��е��±�
    return i + 1;
}

/**
 * �����Ա���ָ��λ�ò�����Ԫ��
 * @param L ���Ա�
 * @param i ����λ��
 * @param e �����ֵ
 * @return ִ��״̬
 */
Status ListInsert(SqList *L, int i, ElemType e) {
    int k; // ���ڱ���Ԫ�ص��±�

    // ���Ա�����������ʧ��
    if (L->length == MAXSIZE) {
        return ERROR;
    }

    // ����λ�ò������Ա�Χ�ڣ�����ʧ��
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }

    // �����λ�������Ա�Χ��
    if (i <= L->length) {
        // �ӵ����ڶ���Ԫ�ؿ�ʼ������λ�õ�Ԫ�أ�ȫ������ƶ�һ��λ��
        for (k = L->length - 1; k >= i - 1; k--) {
            L->data[k + 1] = L->data[k];
        }
    }

    L->data[i - 1] = e; // ����Ԫ�ز���
    L->length++; // ���Ա��ȼ�1
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
Status ListDelete(SqList *L, int i, ElemType *e) {
    int k; // ���ڱ���Ԫ�ص��±�

    // ���Ա���Ϊ�գ�ɾ��ʧ��
    if (L->length == 0) {
        return ERROR;
    }

    // ɾ��λ�ò������Ա�Χ�ڣ�ɾ��ʧ��
    if (i < 1 || i > L->length) {
        return ERROR;
    }

    // ��ɾ��λ��Ԫ�ص�ֵ��ֵ��e
    *e = L->data[i - 1];

    // ɾ��λ�������Ա�Χ��
    if (i < L->length) {
        // ��ɾ��λ�õ���һ��Ԫ�ص����Ա����һ��Ԫ�أ�ȫ����ǰ�ƶ�һ��λ��
        for (k = i; k < L->length; k++) {
            L->data[k - 1] = L->data[k];
        }
    }
    // ���Ա��ȼ�1
    L->length--;
    return OK;
}

/**
 * ��ӡ����Ԫ��
 * @param c Ԫ��ֵ
 * @return ִ��״̬
 */
Status visit(ElemType c) {
    printf("%d ", c);
    return OK;
}

/**
 * ����������Ա�������Ԫ��
 * @param L ���Ա�
 * @return
 */
Status ListTravel(SqList L) {
    int i; // ���ڱ���Ԫ�ص��±�

    printf("[ ");
    // �������Ա�����Ԫ��
    for (i = 0; i < L.length; i++) {
        visit(L.data[i]); // ��ӡ����Ԫ��
    }
    printf("]\n");
    return OK;
}

/**
 * �ϲ��������Ա��ֵ��La��
 * @param La ���Ա�1
 * @param Lb ���Ա�2
 */
void unionL(SqList *La, SqList Lb) {
    int i; // ���ڱ���Ԫ�ص��±�
    int La_len, Lb_len; // ���Ա�La��Lb�ĳ���
    ElemType e; // ���ڴ��Lb��Ԫ�ص�ֵ

    // ��ȡ���Ա�La��Lb�ĳ���
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);

    // �������Ա�Lb�е�Ԫ��
    for (i = 1; i <= Lb_len; i++) {
        // ��ȡLb��iλ��Ԫ�ص�ֵ��Ԫ��e��
        GetElem(Lb, i, &e);
        // Ԫ��e�е�ֵ��La�в�����
        if (!LocateElem(*La, e)) {
            // ��Ԫ��e����La�����
            ListInsert(La, ++La_len, e);
        }
    }
}

int main() {
    SqList L; // ���Ա�
    SqList Lb;
    Status status; // ִ��״̬
    ElemType e; // ���Ա�Ԫ��
    int result; // ���н��
    int j, k; // ���ڱ���Ԫ�ص��±�

    InitList(&L); // ��ʼ�����Ա�
    printf("��ʼ�����Ա�L��L�ĳ���Ϊ��%d\n", L.length);

    result = ListEmpty(L); // ��ȡ���Ա��Ƿ�Ϊ��
    printf("L�Ƿ�Ϊ�գ�%s\n", result == TRUE ? "��" : "��");

    /*** ��L�ı�ͷ����5��Ԫ�� ***/
    for (j = 1; j <= 5; j++) {
        status = ListInsert(&L, 1, j); // �����Ա��ͷ����ֵ
    }
    printf("��L��ͷ���β���1~5��L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    printf("����5��Ԫ�غ�L�ĳ���Ϊ��%d\n", L.length);

    result = ListEmpty(L); // ��ȡ���Ա��Ƿ�Ϊ��
    printf("L�Ƿ�Ϊ�գ�%s\n", result == TRUE ? "��" : "��");

    /*** ���L�е�Ԫ�� ***/
    status = ClearList(&L); // ������Ա�
    printf("������Ա�L��L�ĳ���Ϊ��%d\n", L.length);

    result = ListEmpty(L); // ��ȡ���Ա��Ƿ�Ϊ��
    printf("L�Ƿ�Ϊ�գ�%s\n", result == TRUE ? "��" : "��");

    /*** ��L�ı�β����10��Ԫ�� ***/
    for (j = 1; j <= 10; j++) {
        ListInsert(&L, j, j); // �����Ա��β����ֵ
    }
    printf("��L��β���β���1~10��L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    printf("����10��Ԫ�غ�L�ĳ���Ϊ��%d\n", L.length);

    /*** ��L�ı�ͷ����һ��Ԫ�� ***/
    ListInsert(&L, 1, 33); // �����Ա��ͷ����Ԫ��33

    printf("��L��ͷ����Ԫ��33��L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    printf("����Ԫ��33��L�ĳ���Ϊ��%d\n", L.length);

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

    /*** ��ʼ�����Ա�Lb����Lb�ı�ͷ����10��Ԫ�� ***/
    status = InitList(&Lb); // ��ʼ�����Ա�Lb
    for (j = 6; j <= 15; j++) {
        status = ListInsert(&Lb, 1, j); // ��Lb��ͷ����10��Ԫ��
    }
    printf("����10��Ԫ�غ�Lb�е�ֵΪ��");
    ListTravel(Lb);

    /*** �ϲ�L��Lb��ֵ��L�� ***/
    unionL(&L, Lb); // �ϲ��������Ա��ֵ��L��

    printf("�ϲ�L��Lb��L��L�е�ֵΪ��");
    ListTravel(L); // �������Ա�

    return 0;
}