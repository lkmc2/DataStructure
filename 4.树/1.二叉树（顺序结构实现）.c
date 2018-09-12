// 二叉树（顺序结构实现）
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1   // 结果为真
#define FALSE 0   // 结果为假
#define OK 1      // 执行成功
#define ERROR 0   // 执行失败

#define MAX_TREE_SIZE 100 // 二叉树最大节点数

typedef int Status; // 函数返回结果类型
typedef int ElemType; // 树节点类型
typedef ElemType SqBiTree[MAX_TREE_SIZE]; // 二叉树结构（下标为0的元素为根节点）

// 位置结构
typedef struct {
    int level, order; // 节点的层数，本层序号（按满二叉树计算）
} Position;

ElemType Nil = 0; // 表示该节点为空

/**
 * 初始化二叉树
 * @param T 二叉树
 * @return 执行状态
 */
Status InitBiTree(SqBiTree T) {
    int i; // 用于遍历元素

    // 将数的所有节点置空
    for (i = 0; i < MAX_TREE_SIZE; i++) {
        T[i] = Nil;
    }
    return OK;
}

/**
 * 按层次构建二叉树
 * @param T 二叉树
 * @return 执行状态
 */
Status CreateBiTree(SqBiTree T) {
    int i = 0; // 用于遍历元素

    printf("请按层序输入节点的值(整形)，0表示空姐点，输入999结束。节点数<= %d\n", MAX_TREE_SIZE);
    // 往树中存储1到10这十个数字
    while (i < 10) {
        T[i] = i + 1; // 为节点赋值

        // 进行防出错判断
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil) {
            printf("出现无双亲的非根节点%d\n", T[i]);
            exit(ERROR); // 错误结束程序
        }
        i++; // i加1
    }
    // 下标i为到达树的最后节点
    while (i < MAX_TREE_SIZE) {
        T[i] = Nil; // 将剩下的节点赋值为空
        i++;
    }
    return OK;
}

/***
 * 清空二叉树（与初始化二叉树一样）
 */
#define ClearBiTree InitBiTree

/**
 * 判断二叉树是否为空
 * @param T 二叉树
 * @return 树是否为空
 */
Status BiTreeEmpty(SqBiTree T) {
    // 树的根节点为空
    if (T[0] == Nil) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 获取树的深度
 * @param T 二叉树
 * @return 执行状态
 */
int BiTreeDepth(SqBiTree T) {
    int i, j = -1; // i是计算树的最后一个元素的下标，j是计算树的层数
    // 找到树的最后一个元素
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (T[i] != Nil) {
            break;
        }
    }
    i++; // 树的节点数加1
    /*
     * 层数 该层节点数
     *   1      1
     *   2      2
     *   3      4
     *   4      8
     *   若i = 7，因为4 < 7 < 8，所以该节点在第4层
     */
    do {
        j++; // 计算层数
    } while (i >= powl(2, j)); // 2的j次方
    return j; // 返回节点的层数
}

/**
 * 获取根节点的值
 * @param T 二叉树
 * @param e 用来获取根节点的值
 * @return 执行状态
 */
Status Root(SqBiTree T, ElemType *e) {
    // 二叉树为空，获取失败
    if (BiTreeEmpty(T)) {
        return ERROR;
    } else {
        *e = T[0]; // 将根节点的值赋值给e
        return OK;
    }
}

/**
 * 返回二叉树中该位置对应的值
 * @param T 二叉树
 * @param e 位置
 * @return 该位置的值
 */
ElemType Value(SqBiTree T, Position e) {
    return T[(int) powl(2, e.level - 1) + e.order - 2];
}

/**
 * 给二叉树对应位置的节点重新赋值
 * @param T 二叉树
 * @param e 重新赋值的节点
 * @param value 新值
 * @return 执行状态
 */
Status Assign(SqBiTree T, Position e, ElemType value) {
    // 获取将赋值节点在数组中的下标
    int i = (int)powl(2, e.level - 1) + e.order - 2;

    // 给叶子赋非空值，但双亲节点为空，赋值失败
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil) {
        return ERROR;
    }
    // 给双亲节点赋空值，但叶子节点非空，赋值失败
    else if (value == Nil && (T[i * 2 + 1] != Nil || T[i * 2 + 2] != Nil)) {
        return ERROR;
    }
    T[i] = value; // 给对应节点赋值为value
    return OK;
}

/**
 * 获取值为e的元素的双亲节点（无该节点则返回Nil）
 * @param T 二叉树
 * @param e 元素值
 * @return 值为e的元素的双亲节点
 */
ElemType Parent(SqBiTree T, ElemType e) {
    int i; // 用来遍历元素

    // 根节点为空，无双亲节点
    if (T[0] == Nil) {
        return Nil;
    }

    // 从树的第二层起遍历元素
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++) {
        // 找到值为e的节点
        if (T[i] == e) {
            // 返回值为e节点的双亲节点
            return T[(i + 1) / 2 - 1];
        }
    }
    return Nil; // 未找到值为e元素的双亲节点
}

/**
 * 获取值为e的元素的左孩子
 * @param T 二叉树
 * @param e 元素e
 * @return 值为e的元素的左孩子
 */
ElemType LeftChild(SqBiTree T, ElemType e) {
    int i; // 用来遍历元素

    // 根节点为空，无双亲节点
    if (T[0] == Nil) {
        return Nil;
    }

    // 从根节点开始遍历树的节点
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++) {
        // 找到值为e的节点
        if (T[i] == e) {
            // 返回值为e节点的左孩子
            return T[i * 2 + 1];
        }
    }
    return Nil; // 未找到值为e元素的左孩子
}

/**
 * 获取值为e的元素的右孩子
 * @param T 二叉树
 * @param e 元素e
 * @return 值为e的元素的右孩子
 */
ElemType RightChild(SqBiTree T, ElemType e) {
    int i; // 用来遍历元素

    // 根节点为空，无双亲节点
    if (T[0] == Nil) {
        return Nil;
    }

    // 从根节点开始遍历树的节点
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++) {
        // 找到值为e的节点
        if (T[i] == e) {
            // 返回值为e节点的右孩子
            return T[i * 2 + 2];
        }
    }
    return Nil; // 未找到值为e元素的右孩子
}

/**
 * 获取值为e的元素的左兄弟
 * @param T 二叉树
 * @param e 元素e
 * @return 值为e的元素的左兄弟
 */
ElemType LeftSibling(SqBiTree T, ElemType e) {
    int i; // 用来遍历元素

    // 根节点为空，无双亲节点
    if (T[0] == Nil) {
        return Nil;
    }

    // 从第二层开始遍历树的节点
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++) {
        // 找到值为e的节点，并且序号为偶数(是右孩子)
        if (T[i] == e && i % 2 == 0) {
            // 返回值为e节点的左兄弟
            return T[i - 1];
        }
    }
    return Nil; // 未找到值为e元素的左兄弟
}

/**
 * 获取值为e的元素的右兄弟
 * @param T 二叉树
 * @param e 元素e
 * @return 值为e的元素的右兄弟
 */
ElemType RightSibling(SqBiTree T, ElemType e) {
    int i; // 用来遍历元素

    // 根节点为空，无双亲节点
    if (T[0] == Nil) {
        return Nil;
    }

    // 从第二层开始遍历树的节点
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++) {
        // 找到值为e的节点，并且序号为偶数(是右孩子)
        if (T[i] == e && i % 2 == 1) {
            // 返回值为e节点的右兄弟
            return T[i + 1];
        }
    }
    return Nil; // 未找到值为e元素的右兄弟
}

/**
 * 打印单个元素
 * @param e 元素值
 * @return 执行状态
 */
Status visit(ElemType e) {
    printf("%d ", e);
    return OK;
}

/**
 * 先序遍历二叉树
 * @param T 二叉树
 * @param i 元素下标
 */
void PreTraverse(SqBiTree T, int i) {
    visit(T[i]); // 打印该元素的值

    // 左子树不空
    if (T[2 * i + 1] != Nil) {
        PreTraverse(T, 2 * i + 1); // 遍历左子树
    }

    // 右子树不空
    if (T[2 * i + 2] != Nil) {
        PreTraverse(T, 2 * i + 2); // 遍历右子树
    }
}

/**
 * 先序遍历辅助函数
 * @param T 二叉树
 * @return 执行状态
 */
Status PreOrderTraverse(SqBiTree T) {
    // 二叉树非空
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0); // 先序遍历二叉树
    }
    printf("\n");
    return OK;
}

/**
 * 中序遍历二叉树
 * @param T 二叉树
 * @param i 元素下标
 */
void InTraverse(SqBiTree T, int i) {

    // 左子树不空
    if (T[2 * i + 1] != Nil) {
        InTraverse(T, 2 * i + 1); // 遍历左子树
    }

    visit(T[i]); // 打印该元素的值

    // 右子树不空
    if (T[2 * i + 2] != Nil) {
        InTraverse(T, 2 * i + 2); // 遍历右子树
    }
}

/**
 * 中序遍历辅助函数
 * @param T 二叉树
 * @return 执行状态
 */
Status InOrderTraverse(SqBiTree T) {
    // 二叉树非空
    if (!BiTreeEmpty(T)) {
        InTraverse(T, 0); // 先序遍历二叉树
    }
    printf("\n");
    return OK;
}

/**
 * 后序遍历二叉树
 * @param T 二叉树
 * @param i 元素下标
 */
void PostTraverse(SqBiTree T, int i) {

    // 左子树不空
    if (T[2 * i + 1] != Nil) {
        PostTraverse(T, 2 * i + 1); // 遍历左子树
    }

    // 右子树不空
    if (T[2 * i + 2] != Nil) {
        PostTraverse(T, 2 * i + 2); // 遍历右子树
    }

    visit(T[i]); // 打印该元素的值
}

/**
 * 后序遍历辅助函数
 * @param T 二叉树
 * @return 执行状态
 */
Status PostOrderTraverse(SqBiTree T) {
    // 二叉树非空
    if (!BiTreeEmpty(T)) {
        PostTraverse(T, 0); // 先序遍历二叉树
    }
    printf("\n");
    return OK;
}

/**
 * 层序遍历二叉树
 * @param T 二叉树
 */
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1, j; // i用来计算二叉树最后一个节点的位置，j用来遍历元素

    // 找到二叉树最后一个元素的下标
    while (T[i] == Nil) {
        i--;
    }

    // 从根节点遍历二叉树的值
    for (j = 0; j <= i; j++) {
        if (T[j] != Nil) {
            visit(T[j]);
        }
    }
    printf("\n");
}

/**
 * 遍历二叉树的所有节点
 * @param T 二叉树
 */
void Print(SqBiTree T) {
    int j, k; // j用来表示层数，k用来表示元素是该层的第几个元素

    Position p; // 位置结构
    ElemType e; // 节点元素值

    // 从第一层开始遍历到最后二叉树的一层
    for (j = 1; j <= BiTreeDepth(T); j++) {
        printf("第%d层：\n", j);
        // powl(2, j-1)可计算该层有多少个节点
        for (k = 1; k <= powl(2, j - 1); k++) {
            p.level = j; // 设置本层层数
            p.order = k; // 设置本层序号
            e = Value(T, p); // 获取树中该位置的值
            if (e != Nil) { // 元素不为空节点
                printf("%d:%d ", k, e);
            }
            printf("\n");
        }
    }
}

int main() {
    Status status; // 执行状态
    ElemType e; // 用来获取二叉树节点的值
    Position p; // 设置节点的位置
    SqBiTree T; // 二叉树

    /*** 二叉树的初始化 ***/
    InitBiTree(T); // 初始化二叉树
    CreateBiTree(T); // 按层次构建二叉树
    printf("建立二叉树后，树是否为空：%s；树的深度为：%d\n", BiTreeEmpty(T) == TRUE ? "是" : "否", BiTreeDepth(T));

    /*** 获取二叉树根的值 ***/
    status = Root(T, &e); // 获取树根的值e

    printf("status=%d\n", status);
    if (status == OK) { // 根节点有值
        printf("二叉树根的值为：%d\n", e);
    } else {
        printf("二叉树为空\n");
    }

    /*** 前序遍历二叉树 ***/
    printf("前序遍历二叉树：\n");
    PreOrderTraverse(T);

    /*** 中序遍历二叉树 ***/
    printf("中序遍历二叉树：\n");
    InOrderTraverse(T);

    /*** 后序遍历二叉树 ***/
    printf("后序遍历二叉树：\n");
    PostOrderTraverse(T);

    /*** 层序遍历二叉树 ***/
    printf("层序遍历二叉树：\n");
    LevelOrderTraverse(T);

    /*** 获取指定节点的值 ***/
    // 设置节点p为第三层第二个元素
    p.level = 3;
    p.order = 2;

    e = Value(T, p); // 获取树中p节点的值
    printf("树中第三层第二个元素的值为：%d\n", e);

    /*** 修改指定节点的值 ***/
    e = 50;
    Assign(T, p, e); // 修改第三层第二个元素的值为50
    printf("修改节点后，层序遍历二叉树：\n");
    LevelOrderTraverse(T); // 层序遍历

    /*** 获取指定节点的双亲，左孩子，右孩子，左兄弟，右兄弟 ***/
    printf("节点50的双亲为：%d，左孩子为：%d，右孩子为：%d\n", Parent(T, e), LeftChild(T, e), RightChild(T, e));
    printf("节点50的左兄弟为：%d，右兄弟为：%d\n", LeftSibling(T, e), RightSibling(T, e));

    /*** 清空二叉树 ***/
    ClearBiTree(T); // 清空二叉树
    printf("清空二叉树后，二叉树是否为空：%s；树的深度为：%d\n", BiTreeEmpty(T) == TRUE ? "是" : "否", BiTreeDepth(T));

//    Print(T); // 遍历二叉树
}