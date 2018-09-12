// 平衡二叉树
#include <stdio.h>
#include <malloc.h>

#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

#define LH +1 // 左边节点较高
#define EH 0 // 两边节点等高
#define RH -1 // 右边节点较高

typedef int Status; // 函数返回结果类型



// 二叉树结构
typedef struct BiTNode {
    int data; // 节点数据
    int bf; // 节点的平衡因子
    struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

/**
 * 对以P为根的二叉排序树做右旋处理
 * 处理之后，原来的根节点P指向新的树根节点L（即旋转处理之前的左子树的根节点）
 * @param P 二叉排序树
 */
void R_Rotate(BiTree *P) {
    BiTree L; // 用来指向新形成的树的根节点

    L = (*P)->lchild; // L指向原来树P的左节点
    (*P)->lchild = L->rchild; // 原来根节点P的左指针指向L（新的根节点）的右节点
    L->rchild = (*P);  // 旧的根节点P成为新的根节点L的右孩子
    *P = L; // P指向L，L成为新的根节点
}

/**
 * 对以P为根的二叉排序树做左旋处理
 * 处理之后，原来的根节点P指向新的树根节点R（即旋转处理之前的右子树的根节点）
 * @param P 二叉排序树
 */
void L_Rotate(BiTree *P) {
    BiTree R; // 用来指向新形成的树的根节点

    R = (*P)->rchild; // R指向原来树P的右节点
    (*P)->rchild = R->lchild; // 原来根节点P的右指针指向R（新的根节点）的左节点
    R->lchild = (*P);  // 旧的根节点P成为新的根节点R的左孩子
    *P = R; // P指向R，R成为新的根节点
}

/**
 * 对以指针T所指节点未为根的二叉树做左平衡处理
 * 本算法结束时，指针T指向新的根节点
 * @param T 二叉排序树
 */
void LeftBalance(BiTree *T) {
    BiTree L, Lr; // L指向T的左子树的根节点，Lr指向L的右节点

    L = (*T)->lchild; // L指向T的左子树的根节点

    // 根据左子树节点的平衡因子判断
    switch (L->bf) {
        case LH: // 新节点插入在T的左孩子的左子树上，要做单右旋处理
            (*T)->bf = L->bf = EH; // 设置根节点T和其左孩子的平衡因子相等（为0）
            R_Rotate(T); // 对根节点进行右旋
            break;
        case RH: // 新节点插入在T的左孩子的右子树上，要做双旋处理
            Lr = L->rchild; // Lr指向T的左孩子的右子树根
            switch (Lr->bf) {
                case LH: // 左子树较高
                    (*T)->bf = RH; // 设置T的平衡因子为右高
                    L->bf = EH; // 设置L的平衡因子为等高
                    break;
                case EH: // 左右子树等高
                    (*T)->bf = L->bf = EH; // 设置T和L的平衡因子等高
                    break;
                case RH: // 右子树较高
                    (*T)->bf = EH; // 设置T的平衡因子等高
                    L->bf = LH; // 设置L的平衡因子左高
                    break;
            }
            Lr->bf = EH; // 设置Lr的平衡因子等高
            L_Rotate(&(*T)->lchild); // 对T的左子树做左旋平衡处理
            R_Rotate(T); // 对T做右旋平衡处理
    }
}

/**
 * 对以指针T所指节点未为根的二叉树做右平衡处理
 * 本算法结束时，指针T指向新的根节点
 * @param T 二叉排序树
 */
void RightBalance(BiTree *T) {
    BiTree R, RL; // R指向T的左子树的根节点，Lr指向R的右节点

    R = (*T)->rchild; // L指向T的右子树的根节点

    // 根据右子树节点的平衡因子判断
    switch (R->bf) {
        case RH: // 新节点插入在T的右孩子的右子树上，要做单左旋处理
            (*T)->bf = R->bf = EH; // 设置根节点T和其右孩子的平衡因子相等（为0）
            L_Rotate(T); // 对根节点进行左旋
            break;
        case LH: // 新节点插入在T的右孩子的左子树上，要做双旋处理
            RL = R->lchild; // RL指向T的右孩子的左子树根
            switch (RL->bf) {
                case RH: // 右子树较高
                    (*T)->bf = LH; // 设置T的平衡因子左高
                    R->bf = LH; // 设置R的平衡因子左高
                    break;
                case EH: // 左右子树等高
                    (*T)->bf = R->bf = EH; // 设置T和L的平衡因子等高
                    break;
                case LH: // 左子树较高
                    (*T)->bf = EH; // 设置T的平衡因子等高
                    R->bf = RH; // 设置L的平衡因子为右高
                    break;
            }
            RL->bf = EH; // 设置RL的平衡因子等高
            R_Rotate(&(*T)->rchild); // 对T的右子树做右旋平衡处理
            L_Rotate(T); // 对T做左旋平衡处理
    }
}

/**
 * 若在平衡二叉排序树T中不存在和e右相同关键字的节点，则插入一个元素为e的新节点
 * 若因插入而使二叉排序树失去平衡，则作平衡旋转处理
 * @param T 二叉排序树
 * @param e 关键字
 * @param taller 判断T的高度是否增加
 * @return 是否插入节点成功
 */
Status InsertAVL(BiTree *T, int e, Status *taller) {
    // 若树T为空，创建新节点成为根节点
    if (!*T) {
        *T = (BiTree) malloc(sizeof(BiTNode)); // 为新节点分配存储空间
        (*T)->data = e; // 设置新节点的数据为e
        (*T)->lchild = (*T)->rchild = NULL; // 设置新节点左右指针为空
        (*T)->bf = EH; // 设置新节点的平衡因子为登高
        *taller = TRUE; // 设置等高标志位为真
    } else { // 树非空

        // 树中已有与e有相同关键字的节点则不再插入
        if (e == (*T)->data) {
            *taller = FALSE; // 设置树未长高
            return FALSE; // 设置插入失败
        }

        // e的值小于根节点的值
        if (e < (*T)->data) {
            if (!InsertAVL(&(*T)->lchild, e, taller)) { // 试图在左子树插入节点e，但是未成功
                return FALSE;
            }

            // T的高度增加，节点e已插入到T的左子树且左子树“长高”
            if (*taller) {
                switch ((*T)->bf) { // 根据根节点平衡因子做判断
                    case LH: // 原本左子树比右子树高，需要做左平衡处理
                        LeftBalance(T); // 对以根为T的树进行左旋
                        *taller = FALSE; // 设置树未增高
                        break;
                    case EH: // 原本左、右子树等高，现因左子树增高而使树增高
                        (*T)->bf = LH; // 设置根节点T的平衡因子左高
                        *taller = TRUE; // 设置树进行增高
                        break;
                    case RH: // 原本右子树比左子树高，现左右子树等高
                        (*T)->bf = EH; // 设置根节点T的平衡因子等高
                        *taller = FALSE;  // 设置树未增高
                        break;
                }
            }
        } else { // e的值大于或小于根节点的值
            if (!InsertAVL(&(*T)->rchild, e, taller)) { // 试图在右子树插入节点e，但是未成功
                return FALSE;
            }

            // T的高度增加，节点e已插入到T的左子树且左子树“长高”
            if (*taller) {
                switch ((*T)->bf) { // 根据根节点平衡因子做判断
                    case LH: // 原本左子树比右子树高，现左右子树等高
                        (*T)->bf = EH; // 设置根节点T的平衡因子等高
                        *taller = FALSE; // 设置树未增高
                        break;
                    case EH: // 原本左、右子树等高，现因右子树增高而使树增高
                        (*T)->bf = RH; // 设置根节点T的平衡因子右高
                        *taller = TRUE; // 设置树进行增高
                        break;
                    case RH: // 原本右子树比左子树高，需要做右平衡处理
                        RightBalance(T); // 对根节点T进行右平衡处理
                        *taller = FALSE;  // 设置树未增高
                        break;
                }
            }
        }
    }
    return TRUE;
}

/**
 * 先序遍历二叉树
 * @param T 二叉树
 */
void PreOrderTraverse(BiTree T) {
    // 树为空，结束遍历
    if (T == NULL) {
        return;
    }

    printf("%d ", T->data); // 打印节点的值
    PreOrderTraverse(T->lchild); // 先序遍历左子树
    PreOrderTraverse(T->rchild); // 先序遍历右子树
}

int main() {
    int i; // 用于遍历元素
    BiTree T = NULL; // 二叉平衡树
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8}; // 插入树中的元素
    Status taller; // 判断树是否增高

    for (i = 0; i < 10; i++) {
        // 将数组的元素依次插入二叉排序树中
        InsertAVL(&T, a[i], &taller);
    }

    printf("先序遍历的结果为：");
    PreOrderTraverse(T); // 先序遍历二叉排序树

    return 0;
}