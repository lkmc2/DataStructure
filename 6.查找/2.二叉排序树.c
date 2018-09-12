// ����������
#include <stdio.h>
#include <malloc.h>

#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

typedef int Status; // �������ؽ������

// �����������ṹ
typedef struct BiTNode {
    int data; // �ڵ�����
    struct BiTNode *lchild, *rchild; // ���Һ���ָ��
} BiTNode, *BiTree;

/**
 * �ݹ���Ҷ���������T���Ƿ����key
 * @param T ����������
 * @param key �ؼ���
 * @param f ָ��f��ָ��T��˫�ף���ʼ����ֵΪNULL��
 * @param p ָ��p�����ҳɹ�ָ����ҳɹ���Ԫ�ؽڵ㣬����ʧ�ܷ����ϴη��ʵ����һ���ڵ�
 * @return ִ��״̬
 */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) {
    if (!T) { // ��TΪ�գ�����ʧ��
        *p = f; // pָ��T��˫�׽ڵ�
        return FALSE;
    } else if (key == T->data) { // �ɹ����ҵ�ֵΪkey��Ԫ��
        *p = T; //ָ��pָ����ҳɹ��Ľڵ�
        return TRUE;
    } else if (key < T->data) { // keyԪ�ص�ֵ�ȵ�ǰ�ڵ�С
        return SearchBST(T->lchild, key, T, p); // ���������м�������
    } else {  // keyԪ�ص�ֵ�ȵ�ǰ�ڵ��
        return SearchBST(T->rchild, key, T, p); // ����������������
    }
}

/**
 * �����������������ڹؼ���Ϊkey��Ԫ��ʱ������ֵΪkey��Ԫ��
 * @param T ����������
 * @param key �ؼ���
 * @return ִ��״̬
 */
Status InsertBST(BiTree *T, int key) {
    BiTree p, s; // p��ȡ������ʱ�ϴη��ʵ����һ���ڵ㣬s���������½ڵ�

    // �������нڵ㣬��������ֵΪkey�Ľڵ�
    if (!SearchBST(*T, key, NULL, &p)) {
        s = (BiTree) malloc(sizeof(BiTNode)); // ���������½ڵ�
        s->data = key; // ���ýڵ��ֵΪkey
        s->lchild = s->rchild = NULL; // �����½ڵ����������Ϊ��

        if (!p) { // ������ʱ���ʵ����һ���ڵ�Ϊ�գ�����Ϊ�գ�
            *T = s; // ����sΪ�µĸ��ڵ�
        } else if (key < p->data) { // key��ֵС�ڸ��ڵ�
            p->lchild = s; // ����sΪ����
        } else { // key��ֵ���ڸ��ڵ�
            p->rchild = s; // ����sΪ�Һ���
        }
        return TRUE;
    } else { // �������йؼ�����ͬ�Ľڵ㣬����ʧ��
        return FALSE;
    }
}

/**
 * �Ӷ�����������ɾ���ڵ�p�����ؽ��������������
 * @param p ���Ľڵ�
 * @return ִ��״̬
 */
Status Delete(BiTree *p) {
    BiTree q, s; // ���ڱ����ڵ�

    // ������Ϊ��ʱֻ���ؽ���������������ɾ���ڵ���Ҷ�ӽڵ�ʱҲ�ߴ˷�֧��
    if ((*p)->rchild == NULL) {
        q = *p; // qָ��ɾ���ڵ�
        *p = (*p)->lchild; // pָ�������ӣ�������ɾ���ڵ㣩
        free(q); // �ͷű�ɾ���ڵ�
    } else if ((*p)->lchild == NULL) { // ������Ϊ�գ�ֻ���ؽ�����������
        q = *p;  // qָ��ɾ���ڵ�
        *p = (*p)->rchild; // pָ�����Һ��ӣ�������ɾ���ڵ㣩
        free(q); // �ͷű�ɾ���ڵ�
    } else { // ������������Ϊ��
        q = *p; // qָ��ɾ���ڵ�

        // ת��Ȼ�����ҵ���ͷ���ҵ���ɾ���ڵ��ǰ���ڵ㣬��ӽ���С�ڴ�ɾ���ڵ�Ľڵ㣩
        s = (*p)->lchild; // sָ��ɾ���ڵ������

        while (s->rchild) {
            q = s; // qָ��s�ڵ�
            s = s->rchild; // s�ڵ�ָ���Һ���
        }

        (*p)->data = s->data; // ��ǰ������ֵ��ֵ����ɾ���ڵ�

        if (q != *p) { // s�ڵ����Һ���
            q->rchild = s->lchild; // �ؽ�q��������
        } else { // s�ڵ�û���Һ��ӣ���sΪǰ����㣩
            q->lchild = s->lchild; // �ؽ�q��������
        }
        free(s); // �ͷ�s�ڵ�
    }
    return TRUE;
}

/**
 * ɾ�������������ֵΪkey�Ľڵ�
 * @param T ���������
 * @param key �ؼ���
 * @return ִ��״̬
 */
Status DeleteBST(BiTree *T, int key) {
    if (!*T) { // ��Ϊ�գ�ɾ��ʧ��
        return FALSE;
    } else {
        if (key == (*T)->data) { // �ҵ�ֵΪkey�Ľڵ�
            return Delete(T); // ɾ���ýڵ㣬���ؽ��������������
        } else if (key < (*T)->data) { // �ýڵ��ֵС��key
            return DeleteBST(&(*T)->lchild, key); // ���������в���ֵΪkey�Ľڵ㲢ɾ��
        } else {
            return DeleteBST(&(*T)->rchild, key); // ���������в���ֵΪkey�Ľڵ㲢ɾ��
        }
    }
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

    printf("%d ", T->data); // ��ӡ�ڵ��ֵ
    PreOrderTraverse(T->lchild); // �������������
    PreOrderTraverse(T->rchild); // �������������
}

int main() {
    int i; // ���ڱ���Ԫ��
    BiTree T = NULL; // ����������
    // ���ڲ������е�����ֵ
    int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};

    // �������е�����Ԫ�ز��������������
    for (i = 0; i < 10; i++) {
        InsertBST(&T, a[i]); // ��Ԫ�ز�������
    }

    printf("����10Ԫ�غ�ǰ�������������ֵΪ��");
    PreOrderTraverse(T); // ǰ�����

    DeleteBST(&T, 93); // ɾ������ֵΪ93��

    printf("\nɾ��Ԫ��93��ǰ�������������ֵΪ��");
    PreOrderTraverse(T); // ǰ�����

    DeleteBST(&T, 47); // ɾ������ֵΪ93��

    printf("\nɾ��Ԫ��47��ǰ�������������ֵΪ��");
    PreOrderTraverse(T); // ǰ�����
}