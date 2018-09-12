// ��·��������B����
#include <stdio.h>
#include <malloc.h>

#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

#define m 3 // B���Ľף���ʱ����Ϊ3
#define N 17 // ����Ԫ�ظ���

typedef int Status; // �������ؽ������

// B���ṹ
typedef struct BTNode {
    int keynum; // �ڵ��йؼ��ָ������ڵ�ɴ洢���Ԫ�ص�ֵ��
    struct BTNode *parent; // ָ��˫�׽ڵ��ָ��
    struct Node { // �ڵ�ṹ
        int key; // �ؼ�������
        struct BTNode *ptr; // ����ָ������
        int recptr; // ��¼ָ������
    } node[m + 1];
} BTNode, *BTree;

// B�����ҽ���ṹ
typedef struct {
    BTNode *pt; // ָ���ҵ��Ľڵ�
    int i; // 1..m���ڽڵ��еĹؼ������
    int tag; // �Ƿ��ҵ���ǣ�1��ʾ���ҳɹ���2��ʾ����ʧ��
} Result;

/**
 * �����нڵ������ӽ���С�ڹؼ���K��Ԫ�ص��±�
 * ��p->node[1..keynum].key�в���i��ʹ��p->node[i].key < K < p->node[i+1].key
 * @param p B��
 * @param K �ؼ���
 * @return ��ӽ���С�ڹؼ���K��Ԫ�ص��±�
 */
int Search(BTree p, int K) {
    int i = 0; // ������¼��ӽ���С�ڹؼ���K��Ԫ�ص��±�
    int j; // ��������Ԫ��

    // �������е�����Ԫ�أ��ҵ���ӽ���С�ڹؼ���K��Ԫ�ص��±�
    for (j = 1; j <= p->keynum; j++) {
        // ����ýڵ��ֵС�ڹؼ���K
        if (p->node[j].key <= K) {
            i = j; // ��¼��Ԫ�ص��±�
        }
    }
    return i; // ������ӽ���С�ڹؼ���K��Ԫ�ص��±�
}

/**
 * ��m��B��T�ϲ��ҹؼ���K������Result���(pt, i, tag)
 * �����ҳɹ�����Result��tag=1��ָ��pt��ָ�ڵ��е�i���ؼ��ֵ���K��
 * ���Ҳ��ɹ���Result��tag=0������K�Ĺؼ���Ӧ������ָ��pt��ֵ�ڵ��е�i�͵�i+1���ؼ���֮��
 * @param T B��
 * @param K �ؼ���
 * @return B�����ҽ��
 */
Result SearchBTree(BTree T, int K) {
    BTree p = T; // B��pָ��T
    BTree q = NULL; // B��q
    Status found = FALSE; // �Ƿ��ҵ�Ԫ��
    int i = 0; // ���ڼ�¼�ҵ�Ԫ�ص��±�
    Result r; // B�����ҽ��

    // δ��������T����δ�ҵ�ֵ���ڹؼ���K��Ԫ��
    while (p && !found) {
        // �����нڵ������ӽ���С�ڹؼ���K��Ԫ�ص��±�
        i = Search(p, K);

        // ���ҵ���Ԫ�ص��±����0������Ԫ�ص�ֵ���ڹؼ���K
        if (i > 0 && p->node[i].key == K) {
            found = TRUE; // ����ҵ�Ԫ��
        } else { // δ�ҵ�ֵ����K��Ԫ��
            q = p; // qָ��ǰ���ڵ�p
            p = p->node[i].ptr; // pָ����һ���ڵ�
        }
    }
    r.i = i; // ���ؽ�����ڽڵ��еĹؼ����������Ϊi

    if (found) { // ���ҳɹ�
        r.pt = p; // ptָ��ڵ��е�i���ؼ��ֵ���KԪ��
        r.tag = 1; // tag=1��ʾ���ҳɹ�
    } else { // ����ʧ��
        r.pt = q; // ptָ��q��ʾָ�򽫽��в����λ��
        r.tag = 0;  // tag=0��ʾ����ʧ��
    }
    return r;
}

/**
 * ��r->key��r��ap�ֱ���뵽q->key[i+1]��q->recptr[i+1]��q->ptr[i+1]��
 * @param q B��
 * @param i ����λ���±�
 * @param key �����ֵ
 * @param ap �²���ڵ�ָ�����һ���ڵ�
 */
void Insert(BTree *q, int i, int key, BTree ap) {
    int j; // ��������Ԫ��

    // ������λ�õ�Ԫ������ƶ�һλ���ճ�(*q)->node[i+1]��λ��
    for (j = (*q)->keynum; j > i; j--) {
        (*q)->node[j + 1] = (*q)->node[j];
    }

    (*q)->node[i + 1].key = key; // �����²���ڵ��ֵ
    (*q)->node[i + 1].ptr = ap; // �����²���ڵ�ָ��ĵ������ڵ�
    (*q)->node[i + 1].recptr = key; // �����²���ڵ�ļ�¼��ָ������
    (*q)->keynum++; // ���нڵ��������
}

/**
 * ���ڵ�q�ֲ�������ڵ㣬ǰһ�뱣������һ�����������ڵ�ap
 * @param q ԭ�ڵ㣬ǰһ���ֵ�����ڴ˽ڵ�
 * @param aq �½ڵ㣬��һ���ֵ�ƶ����˽ڵ�
 */
void split(BTree *q, BTree *ap) {
    int i, s = (m + 1) / 2; // ��������Ԫ�أ�s�ǽڵ������һ��
    *ap = (BTree) malloc(sizeof(BTNode)); // Ϊ�½ڵ����洢�ռ�
    (*ap)->node[0].ptr = (*q)->node[s].ptr; // �½ڵ�apָ��ԭ�ڵ����һ��Ԫ��

    // ����һ���Ԫ���ƶ����½ڵ�
    for (i = s + 1; i <= m; i++) {
        (*ap)->node[i - s] = (*q)->node[i]; // ����һ���Ԫ��ֵ���õ��½ڵ�

        if ((*ap)->node[i - s].ptr) { // ���½ڵ������ָ����ֵ
            (*ap)->node[i - s].ptr->parent = *ap; // ��Ԫ�صĸ��ڵ�ָ��ָ��ap
        }
    }

    (*ap)->keynum = m - s; // qp���ڵ��������
    (*ap)->parent = (*q)->parent;
    (*q)->keynum = s - 1; // q���ڵ������1
}

/**
 * �����µĸ��ڵ�
 * @param T
 * @param key �ڵ�ֵ
 * @param ap
 */
void NewRoot(BTree *T, int key, BTree ap) {
    BTree p; // �µĸ��ڵ�
    p = (BTree) malloc(sizeof(BTNode)); // Ϊ�µĸ��ڵ����洢�ռ�
    p->node[0].ptr = *T; // ���ڵ�ĵ�0��Ԫ��ָ��ԭ����T�ڵ㣨��Ϊ�µĸ��ڵ����Ԫ�أ�
    *T = p; // T�ڵ�ָ���µĸ��ڵ�

    // ����½ڵ��0��Ԫ�ص�ָ���ֵ�ǿ�
    if ((*T)->node[0].ptr) {
        // ���½ڵ��0��Ԫ�ص�ָ���ֵ�ĸ��ڵ�ΪT
        (*T)->node[0].ptr->parent = *T;
    }

    (*T)->parent = NULL; // �����µĸ��ڵ���˫��
    (*T)->keynum = 1; // ���ø��ڵ��Ԫ������Ϊ1
    (*T)->node[1].key = key; // ���ø��ڵ�Ԫ�ص�ֵ
    (*T)->node[1].recptr = key; // ���ü�¼ָ������Ϊkey
    (*T)->node[1].ptr = ap; // ���ø��ڵ��1��Ԫ��ָ��ap�ڵ�

    // ����½ڵ��1��Ԫ�ص�ָ���ֵ�ǿ�
    if ((*T)->node[1].ptr) {
        // ���½ڵ��1��Ԫ�ص�ָ���ֵ�ĸ��ڵ�ΪT
        (*T)->node[1].ptr->parent = *T;
    }
}

/**
 * ��m��B��T�Ͻڵ�*q��key[i]��key[i+1]֮�����ؼ���K��ָ��r
 * ������ڵ��������˫�������б�Ҫ�Ľڵ�ֲ������ʹT����m��B��
 * @param T B��
 * @param key �ؼ���
 * @param q
 * @param i
 */
void InsertBTree(BTree *T, int key, BTree q, int i) {
    BTree ap = NULL; //
    Status finished = FALSE; // �Ƿ������ɵı��
    int s; // ������ȡ�ڵ��м�λ�õ��±�
    int rx; // ���� ��ȡ�м�λ�õļ�¼��

    rx = key; // ���ü�¼�����ڹؼ���

    // ��q�ڵ�ǿգ�����δ���
    while (q && !finished) {
        // ��ֵΪrx��Ԫ�ز��뵽��qe�ĵ�i��λ��
        Insert(&q, i, rx, ap);

        // �������B��q�Ľڵ���С�ڽ���
        if (q->keynum < m) {
            finished = TRUE; // �������
        } else { // B��q�Ľڵ������ڵ���m�����ֲ�ýڵ�
            s = (m + 1) / 2; // ��ȡ�м�ڵ��±�
            rx = q->node[s].recptr; // ��ȡ�м�λ�õļ�¼��
            split(&q, &ap); // �Խڵ���зֲ�

            q = q->parent; // qָ���Լ���˫�׽ڵ�
            if (q) {
                i = Search(q, key); // ��˫�׽ڵ�*q�в���rx->key�Ĳ���λ��
            }
        }
    }

    // ������δ���
    if (!finished) {
        NewRoot(T, rx, ap); // �����µĸ��ڵ�
    }
}

/**
 * ��ӡB���е�i���ڵ��ֵ
 * @param p B��
 * @param i �ڵ��±�
 */
void print(BTNode p, int i) {
    printf("(%d)", p.node[i].key);
}

int main() {
    int r[N] = {22, 16, 41, 58, 8, 11, 12, 16, 17, 22, 23, 31, 41, 52, 58, 59, 61};
    BTree T = NULL; // B��
    Result result; // B�����ҽ���ṹ
    int i; // ��������Ԫ��

    for (i = 0; i < N; i++) {
        // ��B��T����������r���±�Ϊi��Ԫ�أ��������������
        result = SearchBTree(T, r[i]);
        // ���r���±�Ϊi��Ԫ����B��T�в����ڣ�����Ԫ�ز���B��T��
        if (!result.tag) {
            InsertBTree(&T, r[i], result.pt, result.i);
        }
    }

    printf("\n����������Ҽ�¼�Ĺؼ��֣�");
    scanf("%d", &i);
    result = SearchBTree(T, i); // ��B���������ùؼ��֣�����ȡ���

    // ����ý�����Ϊ���ҵ�
    if (result.tag) {
        print(*(result.pt), result.i); // ��ӡB���е�i���ڵ��ֵ
    } else {
        printf("δ�ҵ��ùؼ���");
    }

    return 0;
}