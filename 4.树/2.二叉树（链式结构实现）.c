// 二叉树（链式结构实现）
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1   // 结果为真
#define FALSE 0   // 结果为假

#define MAXSIZE 100 // 存储空间初始分配大小

typedef int Status; // 执行状态

/*********** 用于构建二叉树的串 **************/
int index = 1;
typedef char String[24]; // 0下标位置存放串的长度
String str;

/**
 * 给串赋值
 * @param T 串
 * @param chars 字符串
 * @return 执行状态
 */
Status StrAssign(String T, char *chars) {
    int i; // 用于遍历元素

    // 字符串长度超出最大长度，赋值失败
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    } else {
        T[0] = strlen(chars); // 串0存储串的长度

        // 为串元素赋值
        for (i = 1; i <= T[0]; i++) {
            T[i] = *(chars + i - 1);
        }
        return OK;
    }
}
/********************************************/

typedef char ElemType; // 树的元素类型
ElemType Nil = ' '; // 表示该节点元素为空

// 二叉树结构
typedef struct BiTNode{
    ElemType data; // 节点数据
    struct BiNode *lchild, *rchild; // 左孩子指针， 右孩子指针
} BiTNode, *BiTree;

/**
 * 初始化二叉树
 * @param T 二叉树
 * @return 执行状态
 */
Status InitBiTree(BiTree *T) {
    *T = NULL; // 将树根的指针赋值为NULL
    return OK;
}

/**
 * 销毁二叉树
 * @param T 二叉树
 */
void DestroyBiTree(BiTree *T) {
    if(*T) { // 树不为空
        if ((*T)->lchild) { // 有左孩子
            DestroyBiTree(&(*T)->lchild); // 销毁左孩子子树
        }
        if ((*T)->rchild) { // 有右孩子
            DestroyBiTree(&(*T)->rchild); // 销毁右孩子子树
        }
        free(*T); // 释放根节点
        *T = NULL; // 根节点指向NULL
    }
}

/**
 * 清空二叉树
 */
#define ClearBiTree DestroyBiTree // 该方法与销毁二叉一样

/**
 * 创建二叉树
 * @param T 二叉树
 */
void CreateBiTree(BiTree *T) {
    ElemType ch;
    ch = str[index++]; // 获取串中对应下标的值

    // 判断字符#表示叶子节点
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BiTree) malloc(sizeof(BiTNode)); // 为根节点分配存储空间
        // 分配空间失败，结束程序
        if (!*T) {
            exit(OVERFLOW);
        }
        (*T)->data = ch; // 为节点赋值
        CreateBiTree(&(*T)->lchild); // 构建左子树
        CreateBiTree(&(*T)->rchild); // 构建右子树
    }
}

/**
 * 判断二叉树是否为空
 * @param T 二叉树
 * @return 树是否为空
 */
Status BiTreeEmpty(BiTree T) {
    if (T) {  // 根节点有元素
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * 计算二叉树的深度
 * @param T 二叉树
 * @return 树的深度
 */
int BiTreeDepth(BiTree T) {
    int i, j; // i用来计算左子树深度，j用来计算右子树深度

    if (!T) { // 根节点没有元素
        return 0; // 树的深度为0
    }

    if (T->lchild) { // 有左孩子
        i = BiTreeDepth(T->lchild); // 求左孩子子树的深度
    } else {
        i = 0; // 设置左孩子深度为0
    }

    if (T->rchild) { // 有右孩子
        j = BiTreeDepth(T->rchild); // 求右孩子子树的深度
    } else {
        j = 0; // 设置右孩子深度为0
    }

    // i大于j表示在计算左子树的深度，否则是计算右子树的深度
    return (i > j) ? (i + 1) : (j + 1);
}

/**
 * 获取树的根元素的值（树为空时返回Nil）
 * @param T 二叉树
 * @return 树的根元素的值
 */
ElemType Root(BiTree T) {
    // 二叉树为空
    if (BiTreeEmpty(T)) {
        return Nil;
    } else { // 二叉树非空
        return T->data; // 返回根元素的值
    }
}

/**
 * 返回二叉树节点的值
 * @param T 二叉树节点
 * @return 节点的值
 */
ElemType Value(BiTree p) {
    return p->data;
}

/**
 * 为二叉树节点p赋值为value
 * @param p 二叉树节点
 * @param value 元素值
 */
void Assign(BiTree p, ElemType value) {
    p->data = value;
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

    printf("%c", T->data); // 打印节点的值
    PreOrderTraverse(T->lchild); // 先序遍历左子树
    PreOrderTraverse(T->rchild); // 先序遍历右子树
}

/**
 * 中序遍历二叉树
 * @param T 二叉树
 */
void InOrderTraverse(BiTree T) {
    // 树为空，结束遍历
    if (T == NULL) {
        return;
    }

    InOrderTraverse(T->lchild); // 中序遍历左子树
    printf("%c", T->data); // 打印节点的值
    InOrderTraverse(T->rchild); // 中序遍历右子树
}

/**
 * 后序遍历二叉树
 * @param T 二叉树
 */
void PostOrderTraverse(BiTree T) {
    // 树为空，结束遍历
    if (T == NULL) {
        return;
    }

    PostOrderTraverse(T->lchild); // 后序遍历左子树
    PostOrderTraverse(T->rchild); // 后序遍历右子树
    printf("%c", T->data); // 打印节点的值
}

int main() {
    int i;
    BiTree T; // 二叉树
    ElemType e; // 元素值

    /*** 初始化二叉树 ***/
    InitBiTree(&T); // 初始化二叉树

    StrAssign(str, "ABDH#K###E##CFI###G#J##"); // 为串str（全局变量）进行赋值

    CreateBiTree(&T); // 使用串创建二叉树

    printf("初始化二叉树后，树是否为空：%s；树的深度为：%d\n", BiTreeEmpty(T) == TRUE ? "是" : "否", BiTreeDepth(T));

    /*** 获取二叉树根元素的值 ***/
    e = Root(T); //获取根元素的值e
    printf("二叉树的根的值为：%c\n", e);

    /*** 前序遍历二叉树 ***/
    printf("前序遍历二叉树：");
    PreOrderTraverse(T);

    /*** 中序遍历二叉树 ***/
    printf("\n中序遍历二叉树：");
    InOrderTraverse(T);

    /*** 后序遍历二叉树 ***/
    printf("\n后序遍历二叉树：");
    PostOrderTraverse(T);

    /*** 清空二叉树 ***/
    ClearBiTree(&T); // 清空二叉树

    printf("\n清空二叉树后，树是否为空：%s；树的深度为：%d\n", BiTreeEmpty(T) == TRUE ? "是" : "否", BiTreeDepth(T));
}