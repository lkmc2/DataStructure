// 串存储结构
#include <stdio.h>
#include <string.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败
#define TRUE 1    // 返回值为真
#define FALSE 0   // 返回值为假

#define MAXSIZE 20 // 存储空间初始分配大小

typedef int Status; // 函数返回结果类型

// 串的存储结构，0下标位置用来存放字符串长度
typedef char String[MAXSIZE + 1];

/**
 * 生成一个值等于字符串chars的字符串T
 * @param T 新生成的字符串
 * @param chars 原字符串
 * @return 执行状态
 */
Status StrAssign(String T, char *chars) {
    int i; // 用于遍历元素

    // 字符串chars的长度大于字符串T的分配空间，生成失败
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    } else {
        // 计算字符串chars的长度，存到T的0下标位置
        T[0] = strlen(chars);

        for (i = 1; i <= T[0]; ++i) {
            // 将字符串chars的所有内容存到字符串T中
            T[i] = *(chars + i - 1); //（T从1下标开始存，chars从0下标开始取值，所以要减1）
        }
        return OK;
    }
}

/**
 * 将串S的所有内容复制到串T中
 * @param T 新生成的串
 * @param S 被复制的串
 * @return 执行状态
 */
Status StrCopy(String T, String S) {
    int i; // 用于遍历元素

    // 遍历S的所有涌入
    for (i = 0; i <= S[0]; ++i) {
        T[i] = S[i];
    }
    return OK;
}

/**
 * 判断串是否为空
 * @param S 串
 * @return 是否为空串
 */
Status StrEmpty(String S) {
    // 下标为0的位置存储串的长度，若等于0，串为空
    if (S[0] == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 比较串S和T的大小
 * 若S>T，返回值>0；若S=T，返回值为0；若S<T，返回值<0
 * @param S 串
 * @param T 串
 * @return 串S是否比串T大
 */
int StrCompare(String S, String T) {
    int i; // 用于遍历元素

    // 遍历串的内容
    for (i = 0; i <= S[0] && i <= T[0]; i++) {
        // 碰到对应位置字符不相等
        if (S[i] != T[i]) {
            // 使用对应位置
            return S[i] - T[i];
        }
    }
    // 使用两个串的长度相减
    return S[0] - T[0];
}

/**
 * 返回串的元素个数
 * @param S 串
 * @return 串的元素个数
 */
int StrLength(String S) {
    return S[0];
}

/**
 * 将串的内容清空
 * @param S 串
 * @return 执行状态
 */
Status ClearString(String S) {
    S[0] = 0; // 令串的长度为0
    return OK;
}

/**
 * 连接S1和S2成新的串T
 * 如果未截断返回TRUE，截断则返回FALSE
 * @param T 连接成的新串
 * @param S1 串
 * @param S2 串
 * @return 是否对连接成的字符串截断
 */
Status Concat(String T, String S1, String S2) {
    int i; // 用于遍历元素

    // 串T的大小可以装下串S1和串S2的内容
    if (S1[0] + S2[0] <= MAXSIZE) {
        // 复制S1的所有内容到T中
        for (i = 1; i <= S1[0]; i++) {
            T[i] = S1[i];
        }
        // 复制S2的所有内容到T中
        for (i = 1; i <= S2[0]; i++) {
            T[S1[0] + i] = S2[i]; // S2的内容在S1的内容之后
        }
        // 串T的长度等于S1和S2的长度之和
        T[0] = S1[0] + S2[0];
        return TRUE; // 表示S2字符串未被截断
    }
    // 串T的大小不能装下串S1和串S2的内容，将截断S2
    else {
        // 复制S1的所有内容到T中
        for (i = 1; i <= S1[0]; ++i) {
            T[i] = S1[i];
        }
        // 当未超过T的最大长度时，复制S2的内容到T中
        for (i = 1; i <= MAXSIZE - S1[0]; i++) {
            T[S1[0] + i] = S2[i]; // S2的内容在S1的内容之后
        }
        // T的长度等于限定的最大长度
        T[0] = MAXSIZE;
        return FALSE; // 表示字符串S2被截断
    }
}

/**
 * 用串Sub返回串S第pos个字符起长度为len的字符
 * @param Sub 截取的子串
 * @param S 原串
 * @param pos 开始截取位置
 * @param len 截取长度
 * @return 执行状态
 */
Status SubString(String Sub, String S, int pos, int len) {
    int i; // 用于遍历元素

    // 截取的开始位置或长度不合理，截取失败
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1) {
        return ERROR;
    }

    // 截取串S中从pos位置开始，长度为len的内容到串Sub中
    for (i = 1; i <= len; ++i) {
        Sub[i] = S[pos + i - 1];
    }
    // 将串Sub的长度设置为len
    Sub[0] = len;
    return OK;
}

/**
 * 定位字串T在串S第pos个字符之后的位置，若不存在则返回0
 * （此方法叫：朴素模式的匹配算法）
 * @param S 原字符串
 * @param T 字串
 * @param pos 在S中开始定位的位置
 * @return 字串T在串S第pos个字符之后的位置，若不存在则返回0
 */
int Index(String S, String T, int pos) {
    int i = pos; // i等于串S开始定位的下标
    int j = 1; // j用于记录字串T中当前下标的位置

    // i小于串S的长度，并且j小于串T的长度
    while (i <= S[0] && j <= T[0]) {
        // 若对应位置的字符相等，i和j都加1
        if (S[i] == T[j]) {
            i++;
            j++;
        } else { // 若对应位置的字符不相等
            i = i - j + 2; // i退回上次匹配首位的下一位
            j = 1; // j退回字串T的首位
        }
    }

    // 串T的所有元素都与S的某个字串相等
    if (j > T[0]) {
        return i - T[0]; // i位置减去串T的长度，得到字串的起始位置
    } else { // 未定位到串T
        return 0; 
    }
}

/**
 * 在串S的第pos个位置插入串T的值
 * 返回TRUE表示完全将T的内容插入S中，FALSE表示不能完全将T的内容插入S中
 * @param S 串S
 * @param pos 下标
 * @param T 串T
 * @return 执行状态
 */
Status StrInsert(String S, int pos, String T) {
    int i; // 用于遍历元素

    // 插入位置不合理，插入错误
    if (pos < 1 || pos > S[0] + 1) {
        return ERROR;
    }

    // 串T有足够的位置完全插入串S中
    if (S[0] + T[0] <= MAXSIZE) {
        // 串S从i位置开始，所有元素向后移动串T的长度
        for (i = S[0]; i >= pos; i--) {
            S[i + T[0]] = S[i];
        }
        // 从第i个位置插入串T的值
        for (i = pos; i < pos + T[0]; i++) {
            S[i] = T[i - pos + 1];
        }
        // 设置S的长度为原来S的长度与T长度之和
        S[0] = S[0] + T[0];
        return TRUE; // 返回TRUE表示完全将T的内容插入S中
    } else {  // 串T没有有足够的位置完全插入串S中，只能部分插入
        // 将S的pos位置开始的元素向后移动T个位置
        for (i = MAXSIZE; i <= pos; i--) {
            S[i] = S[i - T[0]];
        }
        // 从第i个位置插入串T的值
        for (i = pos; i < pos + T[0]; i++) {
            S[i] = T[i - pos + 1];
        }
        S[0] = MAXSIZE; // S的长度为最大初始值
        return FALSE; // 返回FALSE表示不能完全将T的内容插入S中
    }
}

/**
 * 从串S的第pos个位置开始，删除len个长度的内容
 * @param S 串S
 * @param pos 开始删除的下标
 * @param len 删除的长度
 * @return 执行状态
 */
Status StrDelete(String S, int pos, int len) {
    int i; // 用于遍历元素

    // 删除位置不合理，删除失败
    if (pos < 1 || pos > S[0] - len + 1 || len < 0) {
        return ERROR;
    }

    // 将被删除位置的值用后面的值覆盖
    for (i = pos + len; i <= S[0]; i++) {
        S[i - len] = S[i];
    }

    S[0] -= len; // S的长度减去len
    return OK;
}

/**
 * 串S中所有等于串T的内容全都用串V进行替换
 * @param S 串S
 * @param T 串T 被替换
 * @param V 串V 替换的新内容
 * @return 执行状态
 */
Status Replace(String S, String T, String V) {
    int i = 1; // 从串S的第一个字符起查找串T

    // 串T是空串，替换失败
    if (StrEmpty(T)) {
        return ERROR;
    }

    do {
        i = Index(S, T, i); // 定位字串T在串S第pos个字符之后的位置
        // 串T在串S中存在
        if (i) {
            StrDelete(S, i, StrLength(T)); // 在串S中删除串T
            StrInsert(S, i, V); // 在原串T的位置删除串V
            i += StrLength(V); // 在插入的串V的后面继续查找串T
        }
    } while (i); // 当串S中还有串T的存在
    return OK;
}

/**
 * 打印串的内容
 * @param T 串T
 */
void StrPrint(String T) {
    int i; // 用于遍历元素
    // 打印字符串中所有元素的值
    for (i = 1; i <= T[0]; i++) {
        printf("%c", T[i]);
    }
    printf("\n");
}

int main() {
    String t, s1, s2; // 串
    Status status; // 执行状态
    int index; // 起始坐标

    status = StrEmpty(t); // 判断字符串t是否为空

    printf("串t是否为空：%s\n", status == TRUE ? "是" : "否");

    /*** 将字符串S赋值为abcd ***/
    status = StrAssign(t, "ab");

    printf("串t的值为：");
    StrPrint(t); // 打印串t
    printf("串t的长度为：%d\n", StrLength(t)); // 获取串的长度
    
    /*** 将字符串S赋值为abcd ***/
    status = StrAssign(s1, "abcd"); // 将字符串S赋值为abcd
    
    printf("将字符串S赋值为abcd后，串s1的值为：");
    StrPrint(s1); // 打印串s1
    printf("串s1的长度为：%d\n", StrLength(s1)); // 获取串的长度

    /*** 复制串s1的内容到s2中 ***/
    StrCopy(s2, s1); // 复制串s1的内容到s2中
    printf("复制串s1的内容到s2后，串s2的值为：");
    StrPrint(s2); // 打印串s2
    printf("串s2的长度为：%d\n", StrLength(s1)); // 获取串的长度

    /*** 比较t和s1的大小 ***/
    status = StrCompare(t, s1);

    if (status > 0) {
        printf("t大于s1\n");
    } else if (status == 0) {
        printf("t等于s1\n");
    } else {
        printf("t小于s2\n");
    }

    /*** 清空字符串s2中的内容 ***/
    status = ClearString(s2);
    printf("s2是否为空串：%s\n", StrEmpty(s2) == TRUE ? "是" : "否");

    /*** 将s1和s2连接后的值，赋值给串t ***/
    status = StrAssign(s2, "efg"); // 重新赋值串s2等于efg

    status = Concat(t, s1, s2); // 连接s1和s2的值，赋值给串t
    printf("连接s1和s2的值到t后，串t的值为：");
    StrPrint(t); // 打印串t

    /*** 截取串t的部分内容到串s2 ***/
    status = SubString(s2, t, 2, 3); // 从串t的2下标位置截取3个字符，赋值给s2

    printf("截取串t的部分内容后，串s2的值为：");
    StrPrint(s2); // 打印串

    /*** 定位子串s2在串t中的起始位置 ***/
    index = Index(t, s2, 0); // 定位子串s2在串t中的起始位置（从0下标开始统计）
    printf("串s2在t的位置为：%d\n", index);

    /*** 在串t下标为4的位置插入串s1 ***/
    status = StrInsert(t, 4, s1); // 在串t下标为4的位置插入串s1
    printf("下标为4的位置插入s1后，串t的值为：");
    StrPrint(t); // 打印串

    /*** 在串t下标为4的位置删除4个字符 ***/
    status = StrDelete(t, 4, 4); // 在串t下标为4的位置删除4个字符

    printf("下标为4的位置删除三个字符后，串t的值为：");
    StrPrint(t); // 打印串

    /*** 替换串t中的abcd成123 ***/
    status = StrAssign(s2, "123"); // 重新赋值串s2等于123
    status = StrAssign(t, "abcdggggabcdggggabcd"); // 重新赋值给串t

    status = Replace(t, s1, s2); // 在串t中，用s2的值替换调s1的值

    printf("替换内容后，串t的值为：");
    StrPrint(t); // 打印串
}