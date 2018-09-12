// 散列表
#include <stdio.h>
#include <malloc.h>

#define OK 1 // 执行成功

#define SUCCESS 1 // 查找成功
#define UNSUCCESS 0 // 查找失败

#define HASHSIZE 12 // 散列表表长
#define NULLKEY -32768 // 表示该位置无元素

typedef int Status; // 函数返回结果类型

int m = 0; // 散列表表长，全局变量

// 散列表结构
typedef struct {
    int *elem; // 存储数据远元素的数组
    int count; // 当前数据元素个数
} HashTable;

/**
 * 初始化散列表
 * @param H 散列表
 * @return 执行状态
 */
Status InitHashTable(HashTable *H) {
    int i; // 用来遍历元素
    m = HASHSIZE; // 设置全局散列表表长
    H->count = m; // 设置当前数据元素个数
    H->elem = (int *) malloc(m * sizeof(int)); // 初始化存储元素的数组

    // 设置散列表中所有元素为空
    for (i = 0; i < m; i++) {
        H->elem[i] = NULLKEY;
    }
    return OK;
}

/**
 * 散列函数
 * @param key 关键字
 * @return 对关键字求值后的散列地址
 */
int Hash(int key) {
    return key % m; // 除留余数法
}

/**
 * 插入关键字到散列表中
 * @param H 散列表
 * @param key 关键字
 */
void InsertHash(HashTable *H, int key) {
    int addr = Hash(key); // 求散列地址

    // 如果该位置的值不为空，则冲突，并向下一个位置移动
    while (H->elem[addr] != NULLKEY) {
        addr = (addr + 1) % m; // 开发定址法的线性探测
    }
    H->elem[addr] = key; // 直到有空位后插入关键字
}

/**
 * 在散列表中查找关键字
 * @param H 散列表
 * @param key 关键字
 * @param addr 散列地址
 * @return 查找成功或失败
 */
Status SearchHash(HashTable H, int key, int *addr) {
    *addr = Hash(key); // 求散列地址

    // 当散列表中该地址的元素不等于关键字
    while (H.elem[*addr] != key) {
        *addr = (*addr + 1) % m; // 开发定址法的线性探测

        // 当该位置的元素为空，或者重新回到回到初始散列地址
        if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) {
            return UNSUCCESS; // 查找失败
        }
    }
    return SUCCESS; // 查找成功
}

int main() {
    int arr[HASHSIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
    int i, p; // i用来遍历元素，p用来存储元素地址
    int key; // key存储关键字
    Status status; // status存储执行状态
    HashTable H; // 哈希表



    InitHashTable(&H); // 初始化散列表
    for (i = 0; i < m; i++) {
        InsertHash(&H, arr[i]); // 将arr数组的元素插入散列表中
    }

    /************ 查找一个散列表中不存在的元素 ************/
    key = 39; // 设置查找关键字

    status = SearchHash(H, key, &p); // 在散列表中重找key所在位置

    if (status) {
        printf("查找元素%d的地址为：%d\n", key, p);
    } else {
        printf("查找元素%d失败", key);
    }

    /************ 查找散列表中存在的元素 ************/
    for (i = 0; i < m; i++) {
        key = arr[i]; // 设置查找关键字
        SearchHash(H, key, &p); // 在散列表中重找key所在位置
        printf("查找元素%d的位置为：%d\n", key, p);
    }

    return 0;
}