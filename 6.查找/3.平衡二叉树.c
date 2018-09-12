// ƽ�������
#include <stdio.h>
#include <malloc.h>

#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

#define LH +1 // ��߽ڵ�ϸ�
#define EH 0 // ���߽ڵ�ȸ�
#define RH -1 // �ұ߽ڵ�ϸ�

typedef int Status; // �������ؽ������



// �������ṹ
typedef struct BiTNode {
    int data; // �ڵ�����
    int bf; // �ڵ��ƽ������
    struct BiTNode *lchild, *rchild; // ���Һ���ָ��
} BiTNode, *BiTree;

/**
 * ����PΪ���Ķ�������������������
 * ����֮��ԭ���ĸ��ڵ�Pָ���µ������ڵ�L������ת����֮ǰ���������ĸ��ڵ㣩
 * @param P ����������
 */
void R_Rotate(BiTree *P) {
    BiTree L; // ����ָ�����γɵ����ĸ��ڵ�

    L = (*P)->lchild; // Lָ��ԭ����P����ڵ�
    (*P)->lchild = L->rchild; // ԭ�����ڵ�P����ָ��ָ��L���µĸ��ڵ㣩���ҽڵ�
    L->rchild = (*P);  // �ɵĸ��ڵ�P��Ϊ�µĸ��ڵ�L���Һ���
    *P = L; // Pָ��L��L��Ϊ�µĸ��ڵ�
}

/**
 * ����PΪ���Ķ�������������������
 * ����֮��ԭ���ĸ��ڵ�Pָ���µ������ڵ�R������ת����֮ǰ���������ĸ��ڵ㣩
 * @param P ����������
 */
void L_Rotate(BiTree *P) {
    BiTree R; // ����ָ�����γɵ����ĸ��ڵ�

    R = (*P)->rchild; // Rָ��ԭ����P���ҽڵ�
    (*P)->rchild = R->lchild; // ԭ�����ڵ�P����ָ��ָ��R���µĸ��ڵ㣩����ڵ�
    R->lchild = (*P);  // �ɵĸ��ڵ�P��Ϊ�µĸ��ڵ�R������
    *P = R; // Pָ��R��R��Ϊ�µĸ��ڵ�
}

/**
 * ����ָ��T��ָ�ڵ�δΪ���Ķ���������ƽ�⴦��
 * ���㷨����ʱ��ָ��Tָ���µĸ��ڵ�
 * @param T ����������
 */
void LeftBalance(BiTree *T) {
    BiTree L, Lr; // Lָ��T���������ĸ��ڵ㣬Lrָ��L���ҽڵ�

    L = (*T)->lchild; // Lָ��T���������ĸ��ڵ�

    // �����������ڵ��ƽ�������ж�
    switch (L->bf) {
        case LH: // �½ڵ������T�����ӵ��������ϣ�Ҫ������������
            (*T)->bf = L->bf = EH; // ���ø��ڵ�T�������ӵ�ƽ��������ȣ�Ϊ0��
            R_Rotate(T); // �Ը��ڵ��������
            break;
        case RH: // �½ڵ������T�����ӵ��������ϣ�Ҫ��˫������
            Lr = L->rchild; // Lrָ��T�����ӵ���������
            switch (Lr->bf) {
                case LH: // �������ϸ�
                    (*T)->bf = RH; // ����T��ƽ������Ϊ�Ҹ�
                    L->bf = EH; // ����L��ƽ������Ϊ�ȸ�
                    break;
                case EH: // ���������ȸ�
                    (*T)->bf = L->bf = EH; // ����T��L��ƽ�����ӵȸ�
                    break;
                case RH: // �������ϸ�
                    (*T)->bf = EH; // ����T��ƽ�����ӵȸ�
                    L->bf = LH; // ����L��ƽ���������
                    break;
            }
            Lr->bf = EH; // ����Lr��ƽ�����ӵȸ�
            L_Rotate(&(*T)->lchild); // ��T��������������ƽ�⴦��
            R_Rotate(T); // ��T������ƽ�⴦��
    }
}

/**
 * ����ָ��T��ָ�ڵ�δΪ���Ķ���������ƽ�⴦��
 * ���㷨����ʱ��ָ��Tָ���µĸ��ڵ�
 * @param T ����������
 */
void RightBalance(BiTree *T) {
    BiTree R, RL; // Rָ��T���������ĸ��ڵ㣬Lrָ��R���ҽڵ�

    R = (*T)->rchild; // Lָ��T���������ĸ��ڵ�

    // �����������ڵ��ƽ�������ж�
    switch (R->bf) {
        case RH: // �½ڵ������T���Һ��ӵ��������ϣ�Ҫ������������
            (*T)->bf = R->bf = EH; // ���ø��ڵ�T�����Һ��ӵ�ƽ��������ȣ�Ϊ0��
            L_Rotate(T); // �Ը��ڵ��������
            break;
        case LH: // �½ڵ������T���Һ��ӵ��������ϣ�Ҫ��˫������
            RL = R->lchild; // RLָ��T���Һ��ӵ���������
            switch (RL->bf) {
                case RH: // �������ϸ�
                    (*T)->bf = LH; // ����T��ƽ���������
                    R->bf = LH; // ����R��ƽ���������
                    break;
                case EH: // ���������ȸ�
                    (*T)->bf = R->bf = EH; // ����T��L��ƽ�����ӵȸ�
                    break;
                case LH: // �������ϸ�
                    (*T)->bf = EH; // ����T��ƽ�����ӵȸ�
                    R->bf = RH; // ����L��ƽ������Ϊ�Ҹ�
                    break;
            }
            RL->bf = EH; // ����RL��ƽ�����ӵȸ�
            R_Rotate(&(*T)->rchild); // ��T��������������ƽ�⴦��
            L_Rotate(T); // ��T������ƽ�⴦��
    }
}

/**
 * ����ƽ�����������T�в����ں�e����ͬ�ؼ��ֵĽڵ㣬�����һ��Ԫ��Ϊe���½ڵ�
 * ��������ʹ����������ʧȥƽ�⣬����ƽ����ת����
 * @param T ����������
 * @param e �ؼ���
 * @param taller �ж�T�ĸ߶��Ƿ�����
 * @return �Ƿ����ڵ�ɹ�
 */
Status InsertAVL(BiTree *T, int e, Status *taller) {
    // ����TΪ�գ������½ڵ��Ϊ���ڵ�
    if (!*T) {
        *T = (BiTree) malloc(sizeof(BiTNode)); // Ϊ�½ڵ����洢�ռ�
        (*T)->data = e; // �����½ڵ������Ϊe
        (*T)->lchild = (*T)->rchild = NULL; // �����½ڵ�����ָ��Ϊ��
        (*T)->bf = EH; // �����½ڵ��ƽ������Ϊ�Ǹ�
        *taller = TRUE; // ���õȸ߱�־λΪ��
    } else { // ���ǿ�

        // ����������e����ͬ�ؼ��ֵĽڵ����ٲ���
        if (e == (*T)->data) {
            *taller = FALSE; // ������δ����
            return FALSE; // ���ò���ʧ��
        }

        // e��ֵС�ڸ��ڵ��ֵ
        if (e < (*T)->data) {
            if (!InsertAVL(&(*T)->lchild, e, taller)) { // ��ͼ������������ڵ�e������δ�ɹ�
                return FALSE;
            }

            // T�ĸ߶����ӣ��ڵ�e�Ѳ��뵽T���������������������ߡ�
            if (*taller) {
                switch ((*T)->bf) { // ���ݸ��ڵ�ƽ���������ж�
                    case LH: // ԭ�����������������ߣ���Ҫ����ƽ�⴦��
                        LeftBalance(T); // ���Ը�ΪT������������
                        *taller = FALSE; // ������δ����
                        break;
                    case EH: // ԭ�����������ȸߣ��������������߶�ʹ������
                        (*T)->bf = LH; // ���ø��ڵ�T��ƽ���������
                        *taller = TRUE; // ��������������
                        break;
                    case RH: // ԭ�����������������ߣ������������ȸ�
                        (*T)->bf = EH; // ���ø��ڵ�T��ƽ�����ӵȸ�
                        *taller = FALSE;  // ������δ����
                        break;
                }
            }
        } else { // e��ֵ���ڻ�С�ڸ��ڵ��ֵ
            if (!InsertAVL(&(*T)->rchild, e, taller)) { // ��ͼ������������ڵ�e������δ�ɹ�
                return FALSE;
            }

            // T�ĸ߶����ӣ��ڵ�e�Ѳ��뵽T���������������������ߡ�
            if (*taller) {
                switch ((*T)->bf) { // ���ݸ��ڵ�ƽ���������ж�
                    case LH: // ԭ�����������������ߣ������������ȸ�
                        (*T)->bf = EH; // ���ø��ڵ�T��ƽ�����ӵȸ�
                        *taller = FALSE; // ������δ����
                        break;
                    case EH: // ԭ�����������ȸߣ��������������߶�ʹ������
                        (*T)->bf = RH; // ���ø��ڵ�T��ƽ�������Ҹ�
                        *taller = TRUE; // ��������������
                        break;
                    case RH: // ԭ�����������������ߣ���Ҫ����ƽ�⴦��
                        RightBalance(T); // �Ը��ڵ�T������ƽ�⴦��
                        *taller = FALSE;  // ������δ����
                        break;
                }
            }
        }
    }
    return TRUE;
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
    BiTree T = NULL; // ����ƽ����
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8}; // �������е�Ԫ��
    Status taller; // �ж����Ƿ�����

    for (i = 0; i < 10; i++) {
        // �������Ԫ�����β��������������
        InsertAVL(&T, a[i], &taller);
    }

    printf("��������Ľ��Ϊ��");
    PreOrderTraverse(T); // �����������������

    return 0;
}