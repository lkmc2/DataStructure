// 二叉排序树
#include <stdio.h>
#include <malloc.h>

#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

typedef int Status; // 函数返回结果类型

// 二叉排序树结构
typedef struct BiTNode {
    int data; // 节点数据
    struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

/**
 * 递归查找二叉排序树T中是否存在key
 * @param T 二叉排序树
 * @param key 关键字
 * @param f 指针f（指向T的双亲，初始调用值为NULL）
 * @param p 指针p，查找成功指向查找成功的元素节点，查找失败返回上次访问的最后一个节点
 * @return 执行状态
 */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) {
    if (!T) { // 树T为空，查找失败
        *p = f; // p指向T的双亲节点
        return FALSE;
    } else if (key == T->data) { // 成功查找到值为key的元素
        *p = T; //指针p指向查找成功的节点
        return TRUE;
    } else if (key < T->data) { // key元素的值比当前节点小
        return SearchBST(T->lchild, key, T, p); // 在左子树中继续查找
    } else {  // key元素的值比当前节点大
        return SearchBST(T->rchild, key, T, p); // 在右子树继续查找
    }
}

/**
 * 当二叉排序树不存在关键字为key的元素时，插入值为key的元素
 * @param T 二叉排序树
 * @param key 关键字
 * @return 执行状态
 */
Status InsertBST(BiTree *T, int key) {
    BiTree p, s; // p获取树遍历时上次访问的最后一个节点，s用来创建新节点

    // 搜索树中节点，若不存在值为key的节点
    if (!SearchBST(*T, key, NULL, &p)) {
        s = (BiTree) malloc(sizeof(BiTNode)); // 创建树的新节点
        s->data = key; // 设置节点的值为key
        s->lchild = s->rchild = NULL; // 设置新节点的左右子树为空

        if (!p) { // 树遍历时访问的最后一个节点为空（即树为空）
            *T = s; // 插入s为新的根节点
        } else if (key < p->data) { // key的值小于父节点
            p->lchild = s; // 插入s为左孩子
        } else { // key的值大于父节点
            p->rchild = s; // 插入s为右孩子
        }
        return TRUE;
    } else { // 树中已有关键字相同的节点，插入失败
        return FALSE;
    }
}

/**
 * 从二叉排序树中删除节点p，并重接它的左或右子树
 * @param p 树的节点
 * @return 执行状态
 */
Status Delete(BiTree *p) {
    BiTree q, s; // 用于遍历节点

    // 右子树为空时只需重接它的左子树（待删除节点是叶子节点时也走此分支）
    if ((*p)->rchild == NULL) {
        q = *p; // q指向被删除节点
        *p = (*p)->lchild; // p指向其左孩子（跳过被删除节点）
        free(q); // 释放被删除节点
    } else if ((*p)->lchild == NULL) { // 左子树为空，只需重接它的右子树
        q = *p;  // q指向被删除节点
        *p = (*p)->rchild; // p指向其右孩子（跳过被删除节点）
        free(q); // 释放被删除节点
    } else { // 左右子树都不为空
        q = *p; // q指向被删除节点

        // 转左，然后向右到尽头（找到待删除节点的前驱节点，最接近又小于待删除节点的节点）
        s = (*p)->lchild; // s指向被删除节点的左孩子

        while (s->rchild) {
            q = s; // q指向s节点
            s = s->rchild; // s节点指向右孩子
        }

        (*p)->data = s->data; // 将前驱结点的值赋值给待删除节点

        if (q != *p) { // s节点有右孩子
            q->rchild = s->lchild; // 重接q的右子树
        } else { // s节点没有右孩子（即s为前驱结点）
            q->lchild = s->lchild; // 重接q的左子树
        }
        free(s); // 释放s节点
    }
    return TRUE;
}

/**
 * 删除排序二叉树中值为key的节点
 * @param T 排序二叉树
 * @param key 关键字
 * @return 执行状态
 */
Status DeleteBST(BiTree *T, int key) {
    if (!*T) { // 树为空，删除失败
        return FALSE;
    } else {
        if (key == (*T)->data) { // 找到值为key的节点
            return Delete(T); // 删除该节点，并重接它的左或右子树
        } else if (key < (*T)->data) { // 该节点的值小于key
            return DeleteBST(&(*T)->lchild, key); // 到左子树中查找值为key的节点并删除
        } else {
            return DeleteBST(&(*T)->rchild, key); // 到右子树中查找值为key的节点并删除
        }
    }
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
    BiTree T = NULL; // 二叉排序树
    // 用于插入树中的数组值
    int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};

    // 将数组中的所有元素插入二叉排序树中
    for (i = 0; i < 10; i++) {
        InsertBST(&T, a[i]); // 将元素插入树中
    }

    printf("插入10元素后，前序遍历二叉树的值为：");
    PreOrderTraverse(T); // 前序遍历

    DeleteBST(&T, 93); // 删除树中值为93的

    printf("\n删除元素93后，前序遍历二叉树的值为：");
    PreOrderTraverse(T); // 前序遍历

    DeleteBST(&T, 47); // 删除树中值为93的

    printf("\n删除元素47后，前序遍历二叉树的值为：");
    PreOrderTraverse(T); // 前序遍历
}