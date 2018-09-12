// ��������˳��ṹʵ�֣�
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1   // ���Ϊ��
#define FALSE 0   // ���Ϊ��
#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��

#define MAX_TREE_SIZE 100 // ���������ڵ���

typedef int Status; // �������ؽ������
typedef int ElemType; // ���ڵ�����
typedef ElemType SqBiTree[MAX_TREE_SIZE]; // �������ṹ���±�Ϊ0��Ԫ��Ϊ���ڵ㣩

// λ�ýṹ
typedef struct {
    int level, order; // �ڵ�Ĳ�����������ţ��������������㣩
} Position;

ElemType Nil = 0; // ��ʾ�ýڵ�Ϊ��

/**
 * ��ʼ��������
 * @param T ������
 * @return ִ��״̬
 */
Status InitBiTree(SqBiTree T) {
    int i; // ���ڱ���Ԫ��

    // ���������нڵ��ÿ�
    for (i = 0; i < MAX_TREE_SIZE; i++) {
        T[i] = Nil;
    }
    return OK;
}

/**
 * ����ι���������
 * @param T ������
 * @return ִ��״̬
 */
Status CreateBiTree(SqBiTree T) {
    int i = 0; // ���ڱ���Ԫ��

    printf("�밴��������ڵ��ֵ(����)��0��ʾ�ս�㣬����999�������ڵ���<= %d\n", MAX_TREE_SIZE);
    // �����д洢1��10��ʮ������
    while (i < 10) {
        T[i] = i + 1; // Ϊ�ڵ㸳ֵ

        // ���з������ж�
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil) {
            printf("������˫�׵ķǸ��ڵ�%d\n", T[i]);
            exit(ERROR); // �����������
        }
        i++; // i��1
    }
    // �±�iΪ�����������ڵ�
    while (i < MAX_TREE_SIZE) {
        T[i] = Nil; // ��ʣ�µĽڵ㸳ֵΪ��
        i++;
    }
    return OK;
}

/***
 * ��ն����������ʼ��������һ����
 */
#define ClearBiTree InitBiTree

/**
 * �ж϶������Ƿ�Ϊ��
 * @param T ������
 * @return ���Ƿ�Ϊ��
 */
Status BiTreeEmpty(SqBiTree T) {
    // ���ĸ��ڵ�Ϊ��
    if (T[0] == Nil) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ��ȡ�������
 * @param T ������
 * @return ִ��״̬
 */
int BiTreeDepth(SqBiTree T) {
    int i, j = -1; // i�Ǽ����������һ��Ԫ�ص��±꣬j�Ǽ������Ĳ���
    // �ҵ��������һ��Ԫ��
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (T[i] != Nil) {
            break;
        }
    }
    i++; // ���Ľڵ�����1
    /*
     * ���� �ò�ڵ���
     *   1      1
     *   2      2
     *   3      4
     *   4      8
     *   ��i = 7����Ϊ4 < 7 < 8�����Ըýڵ��ڵ�4��
     */
    do {
        j++; // �������
    } while (i >= powl(2, j)); // 2��j�η�
    return j; // ���ؽڵ�Ĳ���
}

/**
 * ��ȡ���ڵ��ֵ
 * @param T ������
 * @param e ������ȡ���ڵ��ֵ
 * @return ִ��״̬
 */
Status Root(SqBiTree T, ElemType *e) {
    // ������Ϊ�գ���ȡʧ��
    if (BiTreeEmpty(T)) {
        return ERROR;
    } else {
        *e = T[0]; // �����ڵ��ֵ��ֵ��e
        return OK;
    }
}

/**
 * ���ض������и�λ�ö�Ӧ��ֵ
 * @param T ������
 * @param e λ��
 * @return ��λ�õ�ֵ
 */
ElemType Value(SqBiTree T, Position e) {
    return T[(int) powl(2, e.level - 1) + e.order - 2];
}

/**
 * ����������Ӧλ�õĽڵ����¸�ֵ
 * @param T ������
 * @param e ���¸�ֵ�Ľڵ�
 * @param value ��ֵ
 * @return ִ��״̬
 */
Status Assign(SqBiTree T, Position e, ElemType value) {
    // ��ȡ����ֵ�ڵ��������е��±�
    int i = (int)powl(2, e.level - 1) + e.order - 2;

    // ��Ҷ�Ӹ��ǿ�ֵ����˫�׽ڵ�Ϊ�գ���ֵʧ��
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil) {
        return ERROR;
    }
    // ��˫�׽ڵ㸳��ֵ����Ҷ�ӽڵ�ǿգ���ֵʧ��
    else if (value == Nil && (T[i * 2 + 1] != Nil || T[i * 2 + 2] != Nil)) {
        return ERROR;
    }
    T[i] = value; // ����Ӧ�ڵ㸳ֵΪvalue
    return OK;
}

/**
 * ��ȡֵΪe��Ԫ�ص�˫�׽ڵ㣨�޸ýڵ��򷵻�Nil��
 * @param T ������
 * @param e Ԫ��ֵ
 * @return ֵΪe��Ԫ�ص�˫�׽ڵ�
 */
ElemType Parent(SqBiTree T, ElemType e) {
    int i; // ��������Ԫ��

    // ���ڵ�Ϊ�գ���˫�׽ڵ�
    if (T[0] == Nil) {
        return Nil;
    }

    // �����ĵڶ��������Ԫ��
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++) {
        // �ҵ�ֵΪe�Ľڵ�
        if (T[i] == e) {
            // ����ֵΪe�ڵ��˫�׽ڵ�
            return T[(i + 1) / 2 - 1];
        }
    }
    return Nil; // δ�ҵ�ֵΪeԪ�ص�˫�׽ڵ�
}

/**
 * ��ȡֵΪe��Ԫ�ص�����
 * @param T ������
 * @param e Ԫ��e
 * @return ֵΪe��Ԫ�ص�����
 */
ElemType LeftChild(SqBiTree T, ElemType e) {
    int i; // ��������Ԫ��

    // ���ڵ�Ϊ�գ���˫�׽ڵ�
    if (T[0] == Nil) {
        return Nil;
    }

    // �Ӹ��ڵ㿪ʼ�������Ľڵ�
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++) {
        // �ҵ�ֵΪe�Ľڵ�
        if (T[i] == e) {
            // ����ֵΪe�ڵ������
            return T[i * 2 + 1];
        }
    }
    return Nil; // δ�ҵ�ֵΪeԪ�ص�����
}

/**
 * ��ȡֵΪe��Ԫ�ص��Һ���
 * @param T ������
 * @param e Ԫ��e
 * @return ֵΪe��Ԫ�ص��Һ���
 */
ElemType RightChild(SqBiTree T, ElemType e) {
    int i; // ��������Ԫ��

    // ���ڵ�Ϊ�գ���˫�׽ڵ�
    if (T[0] == Nil) {
        return Nil;
    }

    // �Ӹ��ڵ㿪ʼ�������Ľڵ�
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++) {
        // �ҵ�ֵΪe�Ľڵ�
        if (T[i] == e) {
            // ����ֵΪe�ڵ���Һ���
            return T[i * 2 + 2];
        }
    }
    return Nil; // δ�ҵ�ֵΪeԪ�ص��Һ���
}

/**
 * ��ȡֵΪe��Ԫ�ص����ֵ�
 * @param T ������
 * @param e Ԫ��e
 * @return ֵΪe��Ԫ�ص����ֵ�
 */
ElemType LeftSibling(SqBiTree T, ElemType e) {
    int i; // ��������Ԫ��

    // ���ڵ�Ϊ�գ���˫�׽ڵ�
    if (T[0] == Nil) {
        return Nil;
    }

    // �ӵڶ��㿪ʼ�������Ľڵ�
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++) {
        // �ҵ�ֵΪe�Ľڵ㣬�������Ϊż��(���Һ���)
        if (T[i] == e && i % 2 == 0) {
            // ����ֵΪe�ڵ�����ֵ�
            return T[i - 1];
        }
    }
    return Nil; // δ�ҵ�ֵΪeԪ�ص����ֵ�
}

/**
 * ��ȡֵΪe��Ԫ�ص����ֵ�
 * @param T ������
 * @param e Ԫ��e
 * @return ֵΪe��Ԫ�ص����ֵ�
 */
ElemType RightSibling(SqBiTree T, ElemType e) {
    int i; // ��������Ԫ��

    // ���ڵ�Ϊ�գ���˫�׽ڵ�
    if (T[0] == Nil) {
        return Nil;
    }

    // �ӵڶ��㿪ʼ�������Ľڵ�
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++) {
        // �ҵ�ֵΪe�Ľڵ㣬�������Ϊż��(���Һ���)
        if (T[i] == e && i % 2 == 1) {
            // ����ֵΪe�ڵ�����ֵ�
            return T[i + 1];
        }
    }
    return Nil; // δ�ҵ�ֵΪeԪ�ص����ֵ�
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
 * �������������
 * @param T ������
 * @param i Ԫ���±�
 */
void PreTraverse(SqBiTree T, int i) {
    visit(T[i]); // ��ӡ��Ԫ�ص�ֵ

    // ����������
    if (T[2 * i + 1] != Nil) {
        PreTraverse(T, 2 * i + 1); // ����������
    }

    // ����������
    if (T[2 * i + 2] != Nil) {
        PreTraverse(T, 2 * i + 2); // ����������
    }
}

/**
 * ���������������
 * @param T ������
 * @return ִ��״̬
 */
Status PreOrderTraverse(SqBiTree T) {
    // �������ǿ�
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0); // �������������
    }
    printf("\n");
    return OK;
}

/**
 * �������������
 * @param T ������
 * @param i Ԫ���±�
 */
void InTraverse(SqBiTree T, int i) {

    // ����������
    if (T[2 * i + 1] != Nil) {
        InTraverse(T, 2 * i + 1); // ����������
    }

    visit(T[i]); // ��ӡ��Ԫ�ص�ֵ

    // ����������
    if (T[2 * i + 2] != Nil) {
        InTraverse(T, 2 * i + 2); // ����������
    }
}

/**
 * ���������������
 * @param T ������
 * @return ִ��״̬
 */
Status InOrderTraverse(SqBiTree T) {
    // �������ǿ�
    if (!BiTreeEmpty(T)) {
        InTraverse(T, 0); // �������������
    }
    printf("\n");
    return OK;
}

/**
 * �������������
 * @param T ������
 * @param i Ԫ���±�
 */
void PostTraverse(SqBiTree T, int i) {

    // ����������
    if (T[2 * i + 1] != Nil) {
        PostTraverse(T, 2 * i + 1); // ����������
    }

    // ����������
    if (T[2 * i + 2] != Nil) {
        PostTraverse(T, 2 * i + 2); // ����������
    }

    visit(T[i]); // ��ӡ��Ԫ�ص�ֵ
}

/**
 * ���������������
 * @param T ������
 * @return ִ��״̬
 */
Status PostOrderTraverse(SqBiTree T) {
    // �������ǿ�
    if (!BiTreeEmpty(T)) {
        PostTraverse(T, 0); // �������������
    }
    printf("\n");
    return OK;
}

/**
 * �������������
 * @param T ������
 */
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1, j; // i����������������һ���ڵ��λ�ã�j��������Ԫ��

    // �ҵ����������һ��Ԫ�ص��±�
    while (T[i] == Nil) {
        i--;
    }

    // �Ӹ��ڵ������������ֵ
    for (j = 0; j <= i; j++) {
        if (T[j] != Nil) {
            visit(T[j]);
        }
    }
    printf("\n");
}

/**
 * ���������������нڵ�
 * @param T ������
 */
void Print(SqBiTree T) {
    int j, k; // j������ʾ������k������ʾԪ���Ǹò�ĵڼ���Ԫ��

    Position p; // λ�ýṹ
    ElemType e; // �ڵ�Ԫ��ֵ

    // �ӵ�һ�㿪ʼ����������������һ��
    for (j = 1; j <= BiTreeDepth(T); j++) {
        printf("��%d�㣺\n", j);
        // powl(2, j-1)�ɼ���ò��ж��ٸ��ڵ�
        for (k = 1; k <= powl(2, j - 1); k++) {
            p.level = j; // ���ñ������
            p.order = k; // ���ñ������
            e = Value(T, p); // ��ȡ���и�λ�õ�ֵ
            if (e != Nil) { // Ԫ�ز�Ϊ�սڵ�
                printf("%d:%d ", k, e);
            }
            printf("\n");
        }
    }
}

int main() {
    Status status; // ִ��״̬
    ElemType e; // ������ȡ�������ڵ��ֵ
    Position p; // ���ýڵ��λ��
    SqBiTree T; // ������

    /*** �������ĳ�ʼ�� ***/
    InitBiTree(T); // ��ʼ��������
    CreateBiTree(T); // ����ι���������
    printf("���������������Ƿ�Ϊ�գ�%s���������Ϊ��%d\n", BiTreeEmpty(T) == TRUE ? "��" : "��", BiTreeDepth(T));

    /*** ��ȡ����������ֵ ***/
    status = Root(T, &e); // ��ȡ������ֵe

    printf("status=%d\n", status);
    if (status == OK) { // ���ڵ���ֵ
        printf("����������ֵΪ��%d\n", e);
    } else {
        printf("������Ϊ��\n");
    }

    /*** ǰ����������� ***/
    printf("ǰ�������������\n");
    PreOrderTraverse(T);

    /*** ������������� ***/
    printf("���������������\n");
    InOrderTraverse(T);

    /*** ������������� ***/
    printf("���������������\n");
    PostOrderTraverse(T);

    /*** ������������� ***/
    printf("���������������\n");
    LevelOrderTraverse(T);

    /*** ��ȡָ���ڵ��ֵ ***/
    // ���ýڵ�pΪ������ڶ���Ԫ��
    p.level = 3;
    p.order = 2;

    e = Value(T, p); // ��ȡ����p�ڵ��ֵ
    printf("���е�����ڶ���Ԫ�ص�ֵΪ��%d\n", e);

    /*** �޸�ָ���ڵ��ֵ ***/
    e = 50;
    Assign(T, p, e); // �޸ĵ�����ڶ���Ԫ�ص�ֵΪ50
    printf("�޸Ľڵ�󣬲��������������\n");
    LevelOrderTraverse(T); // �������

    /*** ��ȡָ���ڵ��˫�ף����ӣ��Һ��ӣ����ֵܣ����ֵ� ***/
    printf("�ڵ�50��˫��Ϊ��%d������Ϊ��%d���Һ���Ϊ��%d\n", Parent(T, e), LeftChild(T, e), RightChild(T, e));
    printf("�ڵ�50�����ֵ�Ϊ��%d�����ֵ�Ϊ��%d\n", LeftSibling(T, e), RightSibling(T, e));

    /*** ��ն����� ***/
    ClearBiTree(T); // ��ն�����
    printf("��ն������󣬶������Ƿ�Ϊ�գ�%s���������Ϊ��%d\n", BiTreeEmpty(T) == TRUE ? "��" : "��", BiTreeDepth(T));

//    Print(T); // ����������
}