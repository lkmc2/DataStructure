// ɢ�б�
#include <stdio.h>
#include <malloc.h>

#define OK 1 // ִ�гɹ�

#define SUCCESS 1 // ���ҳɹ�
#define UNSUCCESS 0 // ����ʧ��

#define HASHSIZE 12 // ɢ�б��
#define NULLKEY -32768 // ��ʾ��λ����Ԫ��

typedef int Status; // �������ؽ������

int m = 0; // ɢ�б����ȫ�ֱ���

// ɢ�б�ṹ
typedef struct {
    int *elem; // �洢����ԶԪ�ص�����
    int count; // ��ǰ����Ԫ�ظ���
} HashTable;

/**
 * ��ʼ��ɢ�б�
 * @param H ɢ�б�
 * @return ִ��״̬
 */
Status InitHashTable(HashTable *H) {
    int i; // ��������Ԫ��
    m = HASHSIZE; // ����ȫ��ɢ�б��
    H->count = m; // ���õ�ǰ����Ԫ�ظ���
    H->elem = (int *) malloc(m * sizeof(int)); // ��ʼ���洢Ԫ�ص�����

    // ����ɢ�б�������Ԫ��Ϊ��
    for (i = 0; i < m; i++) {
        H->elem[i] = NULLKEY;
    }
    return OK;
}

/**
 * ɢ�к���
 * @param key �ؼ���
 * @return �Թؼ�����ֵ���ɢ�е�ַ
 */
int Hash(int key) {
    return key % m; // ����������
}

/**
 * ����ؼ��ֵ�ɢ�б���
 * @param H ɢ�б�
 * @param key �ؼ���
 */
void InsertHash(HashTable *H, int key) {
    int addr = Hash(key); // ��ɢ�е�ַ

    // �����λ�õ�ֵ��Ϊ�գ����ͻ��������һ��λ���ƶ�
    while (H->elem[addr] != NULLKEY) {
        addr = (addr + 1) % m; // ������ַ��������̽��
    }
    H->elem[addr] = key; // ֱ���п�λ�����ؼ���
}

/**
 * ��ɢ�б��в��ҹؼ���
 * @param H ɢ�б�
 * @param key �ؼ���
 * @param addr ɢ�е�ַ
 * @return ���ҳɹ���ʧ��
 */
Status SearchHash(HashTable H, int key, int *addr) {
    *addr = Hash(key); // ��ɢ�е�ַ

    // ��ɢ�б��иõ�ַ��Ԫ�ز����ڹؼ���
    while (H.elem[*addr] != key) {
        *addr = (*addr + 1) % m; // ������ַ��������̽��

        // ����λ�õ�Ԫ��Ϊ�գ��������»ص��ص���ʼɢ�е�ַ
        if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) {
            return UNSUCCESS; // ����ʧ��
        }
    }
    return SUCCESS; // ���ҳɹ�
}

int main() {
    int arr[HASHSIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
    int i, p; // i��������Ԫ�أ�p�����洢Ԫ�ص�ַ
    int key; // key�洢�ؼ���
    Status status; // status�洢ִ��״̬
    HashTable H; // ��ϣ��



    InitHashTable(&H); // ��ʼ��ɢ�б�
    for (i = 0; i < m; i++) {
        InsertHash(&H, arr[i]); // ��arr�����Ԫ�ز���ɢ�б���
    }

    /************ ����һ��ɢ�б��в����ڵ�Ԫ�� ************/
    key = 39; // ���ò��ҹؼ���

    status = SearchHash(H, key, &p); // ��ɢ�б�������key����λ��

    if (status) {
        printf("����Ԫ��%d�ĵ�ַΪ��%d\n", key, p);
    } else {
        printf("����Ԫ��%dʧ��", key);
    }

    /************ ����ɢ�б��д��ڵ�Ԫ�� ************/
    for (i = 0; i < m; i++) {
        key = arr[i]; // ���ò��ҹؼ���
        SearchHash(H, key, &p); // ��ɢ�б�������key����λ��
        printf("����Ԫ��%d��λ��Ϊ��%d\n", key, p);
    }

    return 0;
}