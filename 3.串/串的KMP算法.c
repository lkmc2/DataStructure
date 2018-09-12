// KMPģʽƥ��
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��

#define MAXSIZE 100 // �洢�ռ��ʼ�����С

typedef int Status; // �������ؽ������

// ���Ĵ洢�ṹ��0�±�λ����������ַ�������
typedef char String[MAXSIZE + 1];

/**
 * ����һ��ֵ�����ַ���chars���ַ���T
 * @param T �����ɵ��ַ���
 * @param chars ԭ�ַ���
 * @return ִ��״̬
 */
Status StrAssign(String T, char *chars) {
    int i; // ���ڱ���Ԫ��

    // �ַ���chars�ĳ��ȴ����ַ���T�ķ���ռ䣬����ʧ��
    if (strlen(chars) > MAXSIZE) {
        return ERROR;
    } else {
        // �����ַ���chars�ĳ��ȣ��浽T��0�±�λ��
        T[0] = strlen(chars);

        for (i = 1; i <= T[0]; i++) {
            // ���ַ���chars���������ݴ浽�ַ���T��
            T[i] = *(chars + i - 1); //��T��1�±꿪ʼ�棬chars��0�±꿪ʼȡֵ������Ҫ��1��
        }
        return OK;
    }
}

/**
 * ���ش���Ԫ�ظ���
 * @param S ��
 * @return ����Ԫ�ظ���
 */
int StrLength(String S) {
    return S[0];
}

/**
 * �������������
 * @param S ��
 * @return ִ��״̬
 */
Status ClearString(String S) {
    S[0] = 0; // ��ĳ���Ϊ0
    return OK;
}

/**
 * ��ӡ��������
 * @param T ��T
 */
void StrPrint(String T) {
    int i; // ���ڱ���Ԫ��
    // ��ӡ�ַ���������Ԫ�ص�ֵ
    for (i = 1; i <= T[0]; i++) {
        printf("%c", T[i]);
    }
    printf("\n");
}

/**
 * ���next����
 * @param next ����
 * @param length ���鳤��
 */
void NextPrint(int next[], int length) {
    int i; // ���ڱ���Ԫ��

    // ��ӡnext�����е�ÿ��ֵ
    for (i = 1; i <= length; i++) {
        printf("%d", next[i]);
    }
    printf("\n");
}

/**
 * ��λ�ִ�T�ڴ�S��pos���ַ�֮���λ�ã����������򷵻�0
 * ���˷����У�����ģʽ��ƥ���㷨��
 * @param S ԭ�ַ���
 * @param T �ִ�
 * @param pos ��S�п�ʼ��λ��λ��
 * @return �ִ�T�ڴ�S��pos���ַ�֮���λ�ã����������򷵻�0
 */
int Index(String S, String T, int pos) {
    int i = pos; // i���ڴ�S��ʼ��λ���±�
    int j = 1; // j���ڼ�¼�ִ�T�е�ǰ�±��λ��

    // iС�ڴ�S�ĳ��ȣ�����jС�ڴ�T�ĳ���
    while (i <= S[0] && j <= T[0]) {
        // ����Ӧλ�õ��ַ���ȣ�i��j����1
        if (S[i] == T[j]) {
            i++;
            j++;
        } else { // ����Ӧλ�õ��ַ������
            i = i - j + 2; // i�˻��ϴ�ƥ����λ����һλ
            j = 1; // j�˻��ִ�T����λ
        }
    }

    // ��T������Ԫ�ض���S��ĳ���ִ����
    if (j > T[0]) {
        return i - T[0]; // iλ�ü�ȥ��T�ĳ��ȣ��õ��ִ�����ʼλ��
    } else { // δ��λ����T
        return 0;
    }
}

/**
 * ͨ�����㷵���Ӵ�T��next����
 * @param T �Ӵ�
 * @param next next����
 */
void get_next(String T, int *next) {
    int i, j; // i���ڶ�λ�ڴ�T�е�λ�ã�j��������next�����ֵ

    i = 1; // i��1��ʼ����Ϊ�±�Ϊ0�ĵط������洮�ĳ���
    j = 0;

    next[1] = 0; // ��һ��λ��Ĭ��ֵΪ0

    // iС�ڴ�T�ĳ���
    while (i < T[0]) {
        // j����0����������i��jλ�õ�ֵ���ʱ
        if (j == 0 || T[i] == T[j]) {
            i++; // i����ƶ�
            j++; // j����ƶ�
            next[i] = j; // iλ�õ�ֵ����j
        } else { // ������i��jλ�õ�ֵ�����
            j = next[j]; // jֵ���л��ݣ������������ϴζ�Ӧλ�ô��ֵ
        }
    }
}

/**
 * ��λ�ִ�T�ڴ�S��pos���ַ�֮���λ�ã����������򷵻�0
 * ��KMP�㷨��
 * @param S ����S
 * @param T �ִ�T
 * @param pos ��������ʼ��λ�Ӵ����±�
 * @return �ִ�T�ڴ�S��pos���ַ�֮���λ�ã����������򷵻�0
 */
int Index_KMP(String S, String T, int pos) {
    int i = pos; // i���ڱ�ʾ����S��ǰλ�õ��±꣬��pos��Ϊ1�����posλ�ÿ�ʼƥ��
    int j = 1; // j���ñ�ʾ�Ӵ�T��ǰλ�õ��±�
    int next[255]; // next����

    get_next(T, next); // �Դ�T���з�������ȡnext�����ֵ

    // �±�i��j���ڴ��ĺ���Χ��
    while (i <= S[0] && j <= T[0]) {
        // j����0����������i��jλ�õ�ֵ���ʱ
        if (j == 0 || S[i] == T[j]) {
            i++; // i����ƶ�
            j++; // j����ƶ�
        } else { // ָ����˺����¿�ʼƥ��
            j = next[j]; // j�˻غ��ʵ�λ�ã�iֵ����
        }
    }

    // ��T������Ԫ�ض���S��ĳ���ִ����
    if (j > T[0]) {
        return i - T[0]; // iλ�ü�ȥ��T�ĳ��ȣ��õ��ִ�����ʼλ��
    } else { // δ��λ����T
        return 0;
    }
}

/**
 * ��ȡ��T��next��������ֵ������������nextval
 * @param T ��
 * @param nextval ����
 */
void get_nextval(String T, int *nextval) {
    int i, j; // i���ڶ�λ�ڴ�T�е�λ�ã�j��������nextval�����ֵ

    i = 1; // i��1��ʼ����Ϊ�±�Ϊ0�ĵط������洮�ĳ���
    j = 0;

    nextval[1] = 0; // ����Ĭ�ϵ�һ��Ԫ��ֵΪ0

    // iС�ڴ�T�ĳ���
    while (i < T[0]) {
        // j����0����������i��jλ�õ�ֵ���ʱ
        if (j == 0 || T[i] == T[j]) { // T[i]��ʾ��׺�ĵ����ַ���T[j]��ʾǰ׺�ĵ����ַ�
            i++; // i����ƶ�
            j++; // j����ƶ�

            // ����ǰ�ַ���ǰ׺�ַ������
            if (T[i] != T[j]) {
                nextval[i] = j; // iλ�õ�ֵ��ֵΪj
            } else { // ��ǰ�ַ���ǰ׺�ַ����
                nextval[i] = nextval[j]; // iλ�õ�ֵ��ֵΪjλ�õ�ֵ
            }
        } else {
            j = nextval[j]; // ���ַ�����ͬ����jֵ����
        }
    }
}

/**
 * ��λ�ִ�T�ڴ�S��pos���ַ�֮���λ�ã����������򷵻�0
 * ��KMP�ĸĽ��㷨��
 * @param S ����S
 * @param T �ִ�T
 * @param pos ��������ʼ��λ�Ӵ����±�
 * @return �ִ�T�ڴ�S��pos���ַ�֮���λ�ã����������򷵻�0
 */
int Index_KMP1(String S, String T, int pos) {
    int i = pos; // i���ڱ�ʾ����S��ǰλ�õ��±꣬��pos��Ϊ1�����posλ�ÿ�ʼƥ��
    int j = 1; // j���ñ�ʾ�Ӵ�T��ǰλ�õ��±�
    int next[255]; // next����

    get_nextval(T, next); // �Դ�T���з�������ȡnext�����ֵ

    // �±�i��j���ڴ��ĺ���Χ��
    while (i <= S[0] && j <= T[0]) {
        // j����0����������i��jλ�õ�ֵ���ʱ
        if (j == 0 || S[i] == T[j]) {
            i++; // i����ƶ�
            j++; // j����ƶ�
        } else { // ָ����˺����¿�ʼƥ��
            j = next[j]; // j�˻غ��ʵ�λ�ã�iֵ����
        }
    }

    // ��T������Ԫ�ض���S��ĳ���ִ����
    if (j > T[0]) {
        return i - T[0]; // iλ�ü�ȥ��T�ĳ��ȣ��õ��ִ�����ʼλ��
    } else { // δ��λ����T
        return 0;
    }
}

int main()
{
    int i,*p;
    String s1,s2;

    StrAssign(s1,"abcdex");
    printf("�Ӵ�Ϊ: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("NextΪ: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"abcabx");
    printf("�Ӵ�Ϊ: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("NextΪ: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"ababaaaba");
    printf("�Ӵ�Ϊ: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("NextΪ: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"aaaaaaaab");
    printf("�Ӵ�Ϊ: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("NextΪ: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"ababaaaba");
    printf("   �Ӵ�Ϊ: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("   NextΪ: ");
    NextPrint(p,StrLength(s1));
    get_nextval(s1,p);
    printf("NextValΪ: ");
    NextPrint(p,StrLength(s1));
    printf("\n");

    StrAssign(s1,"aaaaaaaab");
    printf("   �Ӵ�Ϊ: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("   NextΪ: ");
    NextPrint(p,StrLength(s1));
    get_nextval(s1,p);
    printf("NextValΪ: ");
    NextPrint(p,StrLength(s1));

    printf("\n");

    StrAssign(s1,"00000000000000000000000000000000000000000000000001");
    printf("����Ϊ: ");
    StrPrint(s1);
    StrAssign(s2,"0000000001");
    printf("�Ӵ�Ϊ: ");
    StrPrint(s2);
    printf("\n");
    printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨����ģʽƥ���㷨��\n",Index(s1,s2,1));
    printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨KMP�㷨�� \n",Index_KMP(s1,s2,1));
    printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨KMP�����㷨�� \n",Index_KMP1(s1,s2,1));

    return 0;
}
