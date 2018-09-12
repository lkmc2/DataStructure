// ����������ʽ�ṹʵ�֣�
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1   // ���Ϊ��
#define FALSE 0   // ���Ϊ��

#define MAXSIZE 100 // �洢�ռ��ʼ�����С

typedef int Status; // ִ��״̬

/*********** ���ڹ����������Ĵ� **************/
int index = 1;
typedef char String[24]; // 0�±�λ�ô�Ŵ��ĳ���
String str;

/**
 * ������ֵ
 * @param T ��
 * @param chars �ַ���
 * @return ִ��״̬
 */
Status StrAssign(String T, char *chars) {
    int i; // ���ڱ���Ԫ��

    // �ַ������ȳ�����󳤶ȣ���ֵʧ��
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    } else {
        T[0] = strlen(chars); // ��0�洢���ĳ���

        // Ϊ��Ԫ�ظ�ֵ
        for (i = 1; i <= T[0]; i++) {
            T[i] = *(chars + i - 1);
        }
        return OK;
    }
}
/********************************************/

typedef char ElemType; // ����Ԫ������
ElemType Nil = ' '; // ��ʾ�ýڵ�Ԫ��Ϊ��

// �������ṹ
typedef struct BiTNode{
    ElemType data; // �ڵ�����
    struct BiNode *lchild, *rchild; // ����ָ�룬 �Һ���ָ��
} BiTNode, *BiTree;

/**
 * ��ʼ��������
 * @param T ������
 * @return ִ��״̬
 */
Status InitBiTree(BiTree *T) {
    *T = NULL; // ��������ָ�븳ֵΪNULL
    return OK;
}

/**
 * ���ٶ�����
 * @param T ������
 */
void DestroyBiTree(BiTree *T) {
    if(*T) { // ����Ϊ��
        if ((*T)->lchild) { // ������
            DestroyBiTree(&(*T)->lchild); // ������������
        }
        if ((*T)->rchild) { // ���Һ���
            DestroyBiTree(&(*T)->rchild); // �����Һ�������
        }
        free(*T); // �ͷŸ��ڵ�
        *T = NULL; // ���ڵ�ָ��NULL
    }
}

/**
 * ��ն�����
 */
#define ClearBiTree DestroyBiTree // �÷��������ٶ���һ��

/**
 * ����������
 * @param T ������
 */
void CreateBiTree(BiTree *T) {
    ElemType ch;
    ch = str[index++]; // ��ȡ���ж�Ӧ�±��ֵ

    // �ж��ַ�#��ʾҶ�ӽڵ�
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BiTree) malloc(sizeof(BiTNode)); // Ϊ���ڵ����洢�ռ�
        // ����ռ�ʧ�ܣ���������
        if (!*T) {
            exit(OVERFLOW);
        }
        (*T)->data = ch; // Ϊ�ڵ㸳ֵ
        CreateBiTree(&(*T)->lchild); // ����������
        CreateBiTree(&(*T)->rchild); // ����������
    }
}

/**
 * �ж϶������Ƿ�Ϊ��
 * @param T ������
 * @return ���Ƿ�Ϊ��
 */
Status BiTreeEmpty(BiTree T) {
    if (T) {  // ���ڵ���Ԫ��
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * ��������������
 * @param T ������
 * @return �������
 */
int BiTreeDepth(BiTree T) {
    int i, j; // i����������������ȣ�j�����������������

    if (!T) { // ���ڵ�û��Ԫ��
        return 0; // �������Ϊ0
    }

    if (T->lchild) { // ������
        i = BiTreeDepth(T->lchild); // ���������������
    } else {
        i = 0; // �����������Ϊ0
    }

    if (T->rchild) { // ���Һ���
        j = BiTreeDepth(T->rchild); // ���Һ������������
    } else {
        j = 0; // �����Һ������Ϊ0
    }

    // i����j��ʾ�ڼ�������������ȣ������Ǽ��������������
    return (i > j) ? (i + 1) : (j + 1);
}

/**
 * ��ȡ���ĸ�Ԫ�ص�ֵ����Ϊ��ʱ����Nil��
 * @param T ������
 * @return ���ĸ�Ԫ�ص�ֵ
 */
ElemType Root(BiTree T) {
    // ������Ϊ��
    if (BiTreeEmpty(T)) {
        return Nil;
    } else { // �������ǿ�
        return T->data; // ���ظ�Ԫ�ص�ֵ
    }
}

/**
 * ���ض������ڵ��ֵ
 * @param T �������ڵ�
 * @return �ڵ��ֵ
 */
ElemType Value(BiTree p) {
    return p->data;
}

/**
 * Ϊ�������ڵ�p��ֵΪvalue
 * @param p �������ڵ�
 * @param value Ԫ��ֵ
 */
void Assign(BiTree p, ElemType value) {
    p->data = value;
}

/**
 * �������������
 * @param T ������
 */
void PreOrderTraverse(BiTree T) {
    // ��Ϊ�գ���������
    if (T == NULL) {
        return;
    }

    printf("%c", T->data); // ��ӡ�ڵ��ֵ
    PreOrderTraverse(T->lchild); // �������������
    PreOrderTraverse(T->rchild); // �������������
}

/**
 * �������������
 * @param T ������
 */
void InOrderTraverse(BiTree T) {
    // ��Ϊ�գ���������
    if (T == NULL) {
        return;
    }

    InOrderTraverse(T->lchild); // �������������
    printf("%c", T->data); // ��ӡ�ڵ��ֵ
    InOrderTraverse(T->rchild); // �������������
}

/**
 * �������������
 * @param T ������
 */
void PostOrderTraverse(BiTree T) {
    // ��Ϊ�գ���������
    if (T == NULL) {
        return;
    }

    PostOrderTraverse(T->lchild); // �������������
    PostOrderTraverse(T->rchild); // �������������
    printf("%c", T->data); // ��ӡ�ڵ��ֵ
}

int main() {
    int i;
    BiTree T; // ������
    ElemType e; // Ԫ��ֵ

    /*** ��ʼ�������� ***/
    InitBiTree(&T); // ��ʼ��������

    StrAssign(str, "ABDH#K###E##CFI###G#J##"); // Ϊ��str��ȫ�ֱ��������и�ֵ

    CreateBiTree(&T); // ʹ�ô�����������

    printf("��ʼ�������������Ƿ�Ϊ�գ�%s���������Ϊ��%d\n", BiTreeEmpty(T) == TRUE ? "��" : "��", BiTreeDepth(T));

    /*** ��ȡ��������Ԫ�ص�ֵ ***/
    e = Root(T); //��ȡ��Ԫ�ص�ֵe
    printf("�������ĸ���ֵΪ��%c\n", e);

    /*** ǰ����������� ***/
    printf("ǰ�������������");
    PreOrderTraverse(T);

    /*** ������������� ***/
    printf("\n���������������");
    InOrderTraverse(T);

    /*** ������������� ***/
    printf("\n���������������");
    PostOrderTraverse(T);

    /*** ��ն����� ***/
    ClearBiTree(&T); // ��ն�����

    printf("\n��ն����������Ƿ�Ϊ�գ�%s���������Ϊ��%d\n", BiTreeEmpty(T) == TRUE ? "��" : "��", BiTreeDepth(T));
}