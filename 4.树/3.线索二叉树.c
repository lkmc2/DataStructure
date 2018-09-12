// 线索二叉树
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败

typedef int Status; // 执行状态
typedef char ElemType; // 元素类型
// 枚举，Link等于0表示指向左右孩子指针，Thread等于1表示指向前驱或后继的线索
typedef enum {Link, Thread} PointerTag;

// 线索二叉树存储结构
typedef struct BiThrNode {
    ElemType data; // 节点数据
    struct BiThrNode *lchild, *rchild; // 左孩子指针，右孩子指针
    PointerTag LTag; // 左标志
    PointerTag RTag; // 右标志
} BiThrNode, *BiThrTree;

ElemType Nil = '#'; // 表示节点为空

/**
 * 生成二叉线索树（按前序遍历输入）
 * @param T 二叉树
 * @return 执行状态
 */
Status CreateBiThrTree(BiThrTree *T) {
    ElemType h; // 元素值
    scanf("%c", &h); // 从控制台获取元素值

    if (h == Nil) { // 元素值为空
        *T = NULL; // 设置树为空
    } else { // 元素值非空
        *T = (BiThrTree) malloc(sizeof(BiThrNode)); // 为树生成新节点

        if (!*T) { // 生成新节点失败，结束程序
            exit(OVERFLOW);
        }

        (*T)->data = h; // 设置根节点数据

        CreateBiThrTree(&(*T)->lchild); // 递归构造左子树

        if ((*T)->lchild) { // 有左孩子
            (*T)->LTag = Link; // 左标签指向Link表示有左孩子
        }

        CreateBiThrTree(&(*T)->rchild); // 递归构造右子树

        if ((*T)->rchild) { // 有右孩子
            (*T)->RTag = Link; // 右标签指向Link表示有右孩子
        }
    }
    return OK;
}

BiThrTree pre; // 全局变量，始终指向刚刚访问过的节点

/**
 * 对二叉树中序遍历进行中序线索化
 * @param p 二叉树
 */
void InThreading(BiThrTree p) {
    if (p) { // 节点非空
        InThreading(p->lchild); // 递归左子树线索化

        if (!p->lchild) { // 没有左孩子
            p->LTag = Thread; // 设置左标签为前驱线索
            p->lchild = pre; // 左孩子指针指向前驱元素
        }

        if (!pre->rchild) { // 前驱节点没有右孩子
            pre->RTag = Thread; // 设置前驱结点右标签为后继线索
            pre->rchild = p; // 前驱节点的右指针指向后继节点（当前节点p）
        }

        pre = p; // 当前节点p变成刚刚访问过的节点

        InThreading(p->rchild); // // 递归右子树线索化
    }
}

/**
 * 将二叉树转换成线索二叉树
 * @param Thrt 线索二叉树
 * @param T 二叉树
 * @return 执行状态
 */
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T) {
    *Thrt = (BiThrTree) malloc(sizeof(BiThrNode)); // 为线索二叉树分配存储空间

    // 分配存储空间失败，结束程序
    if (!*Thrt) {
        exit(OVERFLOW);
    }

    /**
     * 设置线索二叉树头节点
     * （头节点不含值，但头节点的左指针指向二叉树的头节点，
     * 二叉树的最后一个元素指向线索二叉树的头节点，
     * 所以线索二叉树的头节点可以从二叉树的头部开始遍历，
     * 也可以从二叉树的尾部开始遍历）
     */
    (*Thrt)->LTag = Link; // 左标签指向左子树
    (*Thrt)->RTag = Thread; // 右标签指向后继元素
    (*Thrt)->rchild = (*Thrt);  // 右指针指向线索二叉树头节点


    if (!T) { // 二叉树T为空
        (*Thrt)->lchild = *Thrt; // 线索二叉树左指针指向线索二叉树头节点
    } else { // 二叉树T非空
        (*Thrt)->lchild = T; // 线索二叉树头节点左指针指向
        pre = (*Thrt); // 记录二叉树根节点为刚刚访问过的节点
        InThreading(T); // 将二叉树T进行中序线索化

        pre->rchild = *Thrt; // 二叉树T的最后一个节点指向线索二叉树头节点
        pre->RTag = Thread; // 二叉树T的最后一个节点右标签指向后继元素

        (*Thrt)->rchild = pre; // 线索二叉树头节点右指针指向后继元素（也就是二叉树T的最后一个元素）
    }
    return OK;
}

/**
 * 打印单个元素的值
 * @param e 元素值
 * @return 执行状态
 */
Status visit(ElemType e) {
    printf("%c ", e);
    return OK;
}

/**
 * 中序遍历线索二叉树
 * @param T 线索二叉树
 * @return 执行状态
 */
Status InOrderTraverse_Thr(BiThrTree T) {
    BiThrTree p; // 用来遍历元素的指针
    p = T->lchild; // p指向二叉树T 的左孩子（头节点没有元素，树的第一个元素在左孩子）

    // 当p未遍历回头指针（未遍历完二叉树中的元素）
    while (p != T) {
        while (p->LTag == Link) { // 当p的左标签指向左孩子
            p = p->lchild; // p向左孩子移动
        }
        if (!visit(p->data)) { // 如果打印元素失败，结束遍历
            return ERROR;
        }

        // 当p的右标签指向后继元素，并且右指针不指向根节点
        while (p->RTag == Thread && p->rchild != T) {
            p = p->rchild; // p向右孩子移动
            visit(p->data); // 打印p节点的值
        }
        p = p->rchild; // p向右孩子移动
    }
    return OK;
}

int main() {
    BiThrTree H, T; // 线索二叉树，二叉树
    printf("请按前序输入二叉树：ABDH##I##EJ###CF##G##\n");
    CreateBiThrTree(&T); // 生成二叉树T
    InOrderThreading(&H, T); // 使用二叉树T，生成线索二叉树H
    printf("中序遍历线索二叉树H：\n");
    InOrderTraverse_Thr(H); // 中序遍历线索二叉树H
    printf("\n");

    return 0;
}