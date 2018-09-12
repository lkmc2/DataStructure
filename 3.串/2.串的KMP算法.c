// KMP模式匹配
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define OK 1      // 执行成功
#define ERROR 0   // 执行失败

#define MAXSIZE 100 // 存储空间初始分配大小

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

        for (i = 1; i <= T[0]; i++) {
            // 将字符串chars的所有内容存到字符串T中
            T[i] = *(chars + i - 1); //（T从1下标开始存，chars从0下标开始取值，所以要减1）
        }
        return OK;
    }
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

/**
 * 输出next数组
 * @param next 数组
 * @param length 数组长度
 */
void NextPrint(int next[], int length) {
    int i; // 用于遍历元素

    // 打印next数组中的每个值
    for (i = 1; i <= length; i++) {
        printf("%d", next[i]);
    }
    printf("\n");
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
 * 通过计算返回子串T的next数组
 * @param T 子串
 * @param next next数组
 */
void get_next(String T, int *next) {
    int i, j; // i用于定位在串T中的位置，j用于设置next数组的值

    i = 1; // i从1开始，因为下标为0的地方用来存串的长度
    j = 0;

    next[1] = 0; // 第一个位置默认值为0

    // i小于串T的长度
    while (i < T[0]) {
        // j等于0，或数组中i和j位置的值相等时
        if (j == 0 || T[i] == T[j]) {
            i++; // i向后移动
            j++; // j向后移动
            next[i] = j; // i位置的值等于j
        } else { // 数组中i和j位置的值不相等
            j = next[j]; // j值进行回溯，等于数组中上次对应位置存的值
        }
    }
}

/**
 * 定位字串T在串S第pos个字符之后的位置，若不存在则返回0
 * （KMP算法）
 * @param S 主串S
 * @param T 字串T
 * @param pos 从主串开始定位子串的下标
 * @return 字串T在串S第pos个字符之后的位置，若不存在则返回0
 */
int Index_KMP(String S, String T, int pos) {
    int i = pos; // i用于表示主串S当前位置的下标，若pos不为1，则从pos位置开始匹配
    int j = 1; // j御用表示子串T当前位置的下标
    int next[255]; // next数组

    get_next(T, next); // 对串T进行分析，获取next数组的值

    // 下标i和j都在串的合理范围内
    while (i <= S[0] && j <= T[0]) {
        // j等于0，或数组中i和j位置的值相等时
        if (j == 0 || S[i] == T[j]) {
            i++; // i向后移动
            j++; // j向后移动
        } else { // 指针回退后重新开始匹配
            j = next[j]; // j退回合适的位置，i值不变
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
 * 获取串T的next函数修正值，并存入数组nextval
 * @param T 串
 * @param nextval 数组
 */
void get_nextval(String T, int *nextval) {
    int i, j; // i用于定位在串T中的位置，j用于设置nextval数组的值

    i = 1; // i从1开始，因为下标为0的地方用来存串的长度
    j = 0;

    nextval[1] = 0; // 数组默认第一个元素值为0

    // i小于串T的长度
    while (i < T[0]) {
        // j等于0，或数组中i和j位置的值相等时
        if (j == 0 || T[i] == T[j]) { // T[i]表示后缀的单个字符，T[j]表示前缀的单个字符
            i++; // i向后移动
            j++; // j向后移动

            // 若当前字符和前缀字符不相等
            if (T[i] != T[j]) {
                nextval[i] = j; // i位置的值赋值为j
            } else { // 当前字符和前缀字符相等
                nextval[i] = nextval[j]; // i位置的值赋值为j位置的值
            }
        } else {
            j = nextval[j]; // 若字符不相同，则j值回溯
        }
    }
}

/**
 * 定位字串T在串S第pos个字符之后的位置，若不存在则返回0
 * （KMP的改进算法）
 * @param S 主串S
 * @param T 字串T
 * @param pos 从主串开始定位子串的下标
 * @return 字串T在串S第pos个字符之后的位置，若不存在则返回0
 */
int Index_KMP1(String S, String T, int pos) {
    int i = pos; // i用于表示主串S当前位置的下标，若pos不为1，则从pos位置开始匹配
    int j = 1; // j御用表示子串T当前位置的下标
    int next[255]; // next数组

    get_nextval(T, next); // 对串T进行分析，获取next数组的值

    // 下标i和j都在串的合理范围内
    while (i <= S[0] && j <= T[0]) {
        // j等于0，或数组中i和j位置的值相等时
        if (j == 0 || S[i] == T[j]) {
            i++; // i向后移动
            j++; // j向后移动
        } else { // 指针回退后重新开始匹配
            j = next[j]; // j退回合适的位置，i值不变
        }
    }

    // 串T的所有元素都与S的某个字串相等
    if (j > T[0]) {
        return i - T[0]; // i位置减去串T的长度，得到字串的起始位置
    } else { // 未定位到串T
        return 0;
    }
}

int main()
{
    int i,*p;
    String s1,s2;

    StrAssign(s1,"abcdex");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"abcabx");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"ababaaaba");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"aaaaaaaab");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"ababaaaba");
    printf("   子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("   Next为: ");
    NextPrint(p,StrLength(s1));
    get_nextval(s1,p);
    printf("NextVal为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"aaaaaaaab");
    printf("   子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("   Next为: ");
    NextPrint(p,StrLength(s1));
    get_nextval(s1,p);
    printf("NextVal为: ");
    NextPrint(p,StrLength(s1));

    printf("\n");

    StrAssign(s1,"00000000000000000000000000000000000000000000000001");
    printf("主串为: ");
    StrPrint(s1);
    StrAssign(s2,"0000000001");
    printf("子串为: ");
    StrPrint(s2);
    printf("\n");
    printf("主串和子串在第%d个字符处首次匹配（朴素模式匹配算法）\n",Index(s1,s2,1));
    printf("主串和子串在第%d个字符处首次匹配（KMP算法） \n",Index_KMP(s1,s2,1));
    printf("主串和子串在第%d个字符处首次匹配（KMP改良算法） \n",Index_KMP1(s1,s2,1));

    return 0;
}
