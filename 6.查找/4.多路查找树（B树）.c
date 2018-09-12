// 多路查找树（B树）
#include <stdio.h>
#include <malloc.h>

#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

#define m 3 // B树的阶，暂时设置为3
#define N 17 // 数据元素个数

typedef int Status; // 函数返回结果类型

// B树结构
typedef struct BTNode {
    int keynum; // 节点中关键字个数（节点可存储多个元素的值）
    struct BTNode *parent; // 指向双亲节点的指针
    struct Node { // 节点结构
        int key; // 关键字向量
        struct BTNode *ptr; // 子树指针向量
        int recptr; // 记录指针向量
    } node[m + 1];
} BTNode, *BTree;

// B树查找结果结构
typedef struct {
    BTNode *pt; // 指向找到的节点
    int i; // 1..m，在节点中的关键字序号
    int tag; // 是否找到标记，1表示查找成功，2表示查找失败
} Result;

/**
 * 在树中节点查找最接近但小于关键字K的元素的下标
 * 在p->node[1..keynum].key中查找i，使得p->node[i].key < K < p->node[i+1].key
 * @param p B树
 * @param K 关键字
 * @return 最接近但小于关键字K的元素的下标
 */
int Search(BTree p, int K) {
    int i = 0; // 用来记录最接近但小于关键字K的元素的下标
    int j; // 用来遍历元素

    // 遍历树中的所有元素，找到最接近但小于关键字K的元素的下标
    for (j = 1; j <= p->keynum; j++) {
        // 如果该节点的值小于关键字K
        if (p->node[j].key <= K) {
            i = j; // 记录该元素的下标
        }
    }
    return i; // 返回最接近但小于关键字K的元素的下标
}

/**
 * 在m阶B树T上查找关键字K，返回Result结果(pt, i, tag)
 * 若查找成功，则Result中tag=1，指针pt所指节点中第i个关键字等于K，
 * 查找不成功，Result中tag=0，等于K的关键字应插入在指针pt所值节点中第i和第i+1个关键字之间
 * @param T B树
 * @param K 关键字
 * @return B树查找结果
 */
Result SearchBTree(BTree T, int K) {
    BTree p = T; // B树p指向T
    BTree q = NULL; // B树q
    Status found = FALSE; // 是否找到元素
    int i = 0; // 用于记录找到元素的下标
    Result r; // B树查找结果

    // 未遍历完树T，且未找到值等于关键字K的元素
    while (p && !found) {
        // 在树中节点查找最接近但小于关键字K的元素的下标
        i = Search(p, K);

        // 查找到的元素的下标大于0，并且元素的值等于关键字K
        if (i > 0 && p->node[i].key == K) {
            found = TRUE; // 标记找到元素
        } else { // 未找到值等于K的元素
            q = p; // q指向当前树节点p
            p = p->node[i].ptr; // p指向下一个节点
        }
    }
    r.i = i; // 返回结果的在节点中的关键字序号设置为i

    if (found) { // 查找成功
        r.pt = p; // pt指向节点中第i个关键字等于K元素
        r.tag = 1; // tag=1表示查找成功
    } else { // 查找失败
        r.pt = q; // pt指向q表示指向将进行插入的位置
        r.tag = 0;  // tag=0表示查找失败
    }
    return r;
}

/**
 * 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中
 * @param q B树
 * @param i 插入位置下标
 * @param key 插入的值
 * @param ap 新插入节点指向的下一个节点
 */
void Insert(BTree *q, int i, int key, BTree ap) {
    int j; // 用来遍历元素

    // 将插入位置的元素向后移动一位，空出(*q)->node[i+1]的位置
    for (j = (*q)->keynum; j > i; j--) {
        (*q)->node[j + 1] = (*q)->node[j];
    }

    (*q)->node[i + 1].key = key; // 设置新插入节点的值
    (*q)->node[i + 1].ptr = ap; // 设置新插入节点指向的的子树节点
    (*q)->node[i + 1].recptr = key; // 设置新插入节点的记录的指针向量
    (*q)->keynum++; // 树中节点个数增加
}

/**
 * 将节点q分拆成两个节点，前一半保留，后一遍移入新生节点ap
 * @param q 原节点，前一半的值保留在此节点
 * @param aq 新节点，后一半的值移动到此节点
 */
void split(BTree *q, BTree *ap) {
    int i, s = (m + 1) / 2; // 用来遍历元素，s是节点个数的一半
    *ap = (BTree) malloc(sizeof(BTNode)); // 为新节点分配存储空间
    (*ap)->node[0].ptr = (*q)->node[s].ptr; // 新节点ap指向原节点的下一个元素

    // 将后一般的元素移动到新节点
    for (i = s + 1; i <= m; i++) {
        (*ap)->node[i - s] = (*q)->node[i]; // 将后一半的元素值设置到新节点

        if ((*ap)->node[i - s].ptr) { // 若新节点的子树指针有值
            (*ap)->node[i - s].ptr->parent = *ap; // 将元素的父节点指针指向ap
        }
    }

    (*ap)->keynum = m - s; // qp树节点个数等于
    (*ap)->parent = (*q)->parent;
    (*q)->keynum = s - 1; // q树节点个数减1
}

/**
 * 生成新的根节点
 * @param T
 * @param key 节点值
 * @param ap
 */
void NewRoot(BTree *T, int key, BTree ap) {
    BTree p; // 新的根节点
    p = (BTree) malloc(sizeof(BTNode)); // 为新的根节点分配存储空间
    p->node[0].ptr = *T; // 根节点的第0个元素指向原来的T节点（成为新的根节点的子元素）
    *T = p; // T节点指向新的根节点

    // 如果新节点第0个元素的指向的值非空
    if ((*T)->node[0].ptr) {
        // 让新节点第0个元素的指向的值的父节点为T
        (*T)->node[0].ptr->parent = *T;
    }

    (*T)->parent = NULL; // 设置新的根节点无双亲
    (*T)->keynum = 1; // 设置根节点的元素数量为1
    (*T)->node[1].key = key; // 设置根节点元素的值
    (*T)->node[1].recptr = key; // 设置记录指针向量为key
    (*T)->node[1].ptr = ap; // 设置根节点第1个元素指向ap节点

    // 如果新节点第1个元素的指向的值非空
    if ((*T)->node[1].ptr) {
        // 让新节点第1个元素的指向的值的父节点为T
        (*T)->node[1].ptr->parent = *T;
    }
}

/**
 * 在m阶B上T上节点*q的key[i]与key[i+1]之间插入关键字K的指针r
 * 若引起节点过大，则沿双亲链进行必要的节点分拆调整，使T仍是m阶B树
 * @param T B树
 * @param key 关键字
 * @param q
 * @param i
 */
void InsertBTree(BTree *T, int key, BTree q, int i) {
    BTree ap = NULL; //
    Status finished = FALSE; // 是否插入完成的标记
    int s; // 用来获取节点中间位置的下标
    int rx; // 用于 获取中间位置的记录数

    rx = key; // 设置记录数等于关键字

    // 当q节点非空，插入未完成
    while (q && !finished) {
        // 将值为rx的元素插入到树qe的第i个位置
        Insert(&q, i, rx, ap);

        // 若插入后B树q的节点数小于阶数
        if (q->keynum < m) {
            finished = TRUE; // 插入完成
        } else { // B树q的节点数大于等于m，将分拆该节点
            s = (m + 1) / 2; // 获取中间节点下标
            rx = q->node[s].recptr; // 获取中间位置的记录数
            split(&q, &ap); // 对节点进行分拆

            q = q->parent; // q指向自己的双亲节点
            if (q) {
                i = Search(q, key); // 在双亲节点*q中查找rx->key的插入位置
            }
        }
    }

    // 当插入未完成
    if (!finished) {
        NewRoot(T, rx, ap); // 创建新的根节点
    }
}

/**
 * 打印B树中第i个节点的值
 * @param p B树
 * @param i 节点下标
 */
void print(BTNode p, int i) {
    printf("(%d)", p.node[i].key);
}

int main() {
    int r[N] = {22, 16, 41, 58, 8, 11, 12, 16, 17, 22, 23, 31, 41, 52, 58, 59, 61};
    BTree T = NULL; // B树
    Result result; // B树查找结果结构
    int i; // 用来遍历元素

    for (i = 0; i < N; i++) {
        // 在B树T中搜索数组r中下标为i的元素，并返回搜索结果
        result = SearchBTree(T, r[i]);
        // 如果r中下标为i的元素在B中T中不存在，将该元素插入B中T中
        if (!result.tag) {
            InsertBTree(&T, r[i], result.pt, result.i);
        }
    }

    printf("\n请输入待查找记录的关键字：");
    scanf("%d", &i);
    result = SearchBTree(T, i); // 在B树中搜索该关键字，并获取结果

    // 如果该结果标记为已找到
    if (result.tag) {
        print(*(result.pt), result.i); // 打印B树中第i个节点的值
    } else {
        printf("未找到该关键字");
    }

    return 0;
}