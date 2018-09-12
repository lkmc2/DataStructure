// ����������
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��

typedef int Status; // ִ��״̬
typedef char ElemType; // Ԫ������
// ö�٣�Link����0��ʾָ�����Һ���ָ�룬Thread����1��ʾָ��ǰ�����̵�����
typedef enum {Link, Thread} PointerTag;

// �����������洢�ṹ
typedef struct BiThrNode {
    ElemType data; // �ڵ�����
    struct BiThrNode *lchild, *rchild; // ����ָ�룬�Һ���ָ��
    PointerTag LTag; // ���־
    PointerTag RTag; // �ұ�־
} BiThrNode, *BiThrTree;

ElemType Nil = '#'; // ��ʾ�ڵ�Ϊ��

/**
 * ���ɶ�������������ǰ��������룩
 * @param T ������
 * @return ִ��״̬
 */
Status CreateBiThrTree(BiThrTree *T) {
    ElemType h; // Ԫ��ֵ
    scanf("%c", &h); // �ӿ���̨��ȡԪ��ֵ

    if (h == Nil) { // Ԫ��ֵΪ��
        *T = NULL; // ������Ϊ��
    } else { // Ԫ��ֵ�ǿ�
        *T = (BiThrTree) malloc(sizeof(BiThrNode)); // Ϊ�������½ڵ�

        if (!*T) { // �����½ڵ�ʧ�ܣ���������
            exit(OVERFLOW);
        }

        (*T)->data = h; // ���ø��ڵ�����

        CreateBiThrTree(&(*T)->lchild); // �ݹ鹹��������

        if ((*T)->lchild) { // ������
            (*T)->LTag = Link; // ���ǩָ��Link��ʾ������
        }

        CreateBiThrTree(&(*T)->rchild); // �ݹ鹹��������

        if ((*T)->rchild) { // ���Һ���
            (*T)->RTag = Link; // �ұ�ǩָ��Link��ʾ���Һ���
        }
    }
    return OK;
}

BiThrTree pre; // ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľڵ�

/**
 * �Զ��������������������������
 * @param p ������
 */
void InThreading(BiThrTree p) {
    if (p) { // �ڵ�ǿ�
        InThreading(p->lchild); // �ݹ�������������

        if (!p->lchild) { // û������
            p->LTag = Thread; // �������ǩΪǰ������
            p->lchild = pre; // ����ָ��ָ��ǰ��Ԫ��
        }

        if (!pre->rchild) { // ǰ���ڵ�û���Һ���
            pre->RTag = Thread; // ����ǰ������ұ�ǩΪ�������
            pre->rchild = p; // ǰ���ڵ����ָ��ָ���̽ڵ㣨��ǰ�ڵ�p��
        }

        pre = p; // ��ǰ�ڵ�p��ɸոշ��ʹ��Ľڵ�

        InThreading(p->rchild); // // �ݹ�������������
    }
}

/**
 * ��������ת��������������
 * @param Thrt ����������
 * @param T ������
 * @return ִ��״̬
 */
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T) {
    *Thrt = (BiThrTree) malloc(sizeof(BiThrNode)); // Ϊ��������������洢�ռ�

    // ����洢�ռ�ʧ�ܣ���������
    if (!*Thrt) {
        exit(OVERFLOW);
    }

    /**
     * ��������������ͷ�ڵ�
     * ��ͷ�ڵ㲻��ֵ����ͷ�ڵ����ָ��ָ���������ͷ�ڵ㣬
     * �����������һ��Ԫ��ָ��������������ͷ�ڵ㣬
     * ����������������ͷ�ڵ���ԴӶ�������ͷ����ʼ������
     * Ҳ���ԴӶ�������β����ʼ������
     */
    (*Thrt)->LTag = Link; // ���ǩָ��������
    (*Thrt)->RTag = Thread; // �ұ�ǩָ����Ԫ��
    (*Thrt)->rchild = (*Thrt);  // ��ָ��ָ������������ͷ�ڵ�


    if (!T) { // ������TΪ��
        (*Thrt)->lchild = *Thrt; // ������������ָ��ָ������������ͷ�ڵ�
    } else { // ������T�ǿ�
        (*Thrt)->lchild = T; // ����������ͷ�ڵ���ָ��ָ��
        pre = (*Thrt); // ��¼���������ڵ�Ϊ�ոշ��ʹ��Ľڵ�
        InThreading(T); // ��������T��������������

        pre->rchild = *Thrt; // ������T�����һ���ڵ�ָ������������ͷ�ڵ�
        pre->RTag = Thread; // ������T�����һ���ڵ��ұ�ǩָ����Ԫ��

        (*Thrt)->rchild = pre; // ����������ͷ�ڵ���ָ��ָ����Ԫ�أ�Ҳ���Ƕ�����T�����һ��Ԫ�أ�
    }
    return OK;
}

/**
 * ��ӡ����Ԫ�ص�ֵ
 * @param e Ԫ��ֵ
 * @return ִ��״̬
 */
Status visit(ElemType e) {
    printf("%c ", e);
    return OK;
}

/**
 * �����������������
 * @param T ����������
 * @return ִ��״̬
 */
Status InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p; // ��������Ԫ�ص�ָ��
    p = T->lchild; // pָ�������T �����ӣ�ͷ�ڵ�û��Ԫ�أ����ĵ�һ��Ԫ�������ӣ�

    // ��pδ������ͷָ�루δ������������е�Ԫ�أ�
    while (p != T) {
        while (p->LTag == Link) { // ��p�����ǩָ������
            p = p->lchild; // p�������ƶ�
        }
        if (!visit(p->data)) { // �����ӡԪ��ʧ�ܣ���������
            return ERROR;
        }

        // ��p���ұ�ǩָ����Ԫ�أ�������ָ�벻ָ����ڵ�
        while (p->RTag == Thread && p->rchild != T) {
            p = p->rchild; // p���Һ����ƶ�
            visit(p->data); // ��ӡp�ڵ��ֵ
        }
        p = p->rchild; // p���Һ����ƶ�
    }
    return OK;
}

int main() {
    BiThrTree H, T; // ������������������
    printf("�밴ǰ�������������ABDH##I##EJ###CF##G##\n");
    CreateBiThrTree(&T); // ���ɶ�����T
    InOrderThreading(&H, T); // ʹ�ö�����T����������������H
    printf("�����������������H��\n");
    InOrderTraverse_Thr(H); // �����������������H
    printf("\n");

    return 0;
}