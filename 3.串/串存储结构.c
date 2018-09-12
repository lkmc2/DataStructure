// ���洢�ṹ
#include <stdio.h>
#include <string.h>

#define OK 1      // ִ�гɹ�
#define ERROR 0   // ִ��ʧ��
#define TRUE 1    // ����ֵΪ��
#define FALSE 0   // ����ֵΪ��

#define MAXSIZE 20 // �洢�ռ��ʼ�����С

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

        for (i = 1; i <= T[0]; ++i) {
            // ���ַ���chars���������ݴ浽�ַ���T��
            T[i] = *(chars + i - 1); //��T��1�±꿪ʼ�棬chars��0�±꿪ʼȡֵ������Ҫ��1��
        }
        return OK;
    }
}

/**
 * ����S���������ݸ��Ƶ���T��
 * @param T �����ɵĴ�
 * @param S �����ƵĴ�
 * @return ִ��״̬
 */
Status StrCopy(String T, String S) {
    int i; // ���ڱ���Ԫ��

    // ����S������ӿ��
    for (i = 0; i <= S[0]; ++i) {
        T[i] = S[i];
    }
    return OK;
}

/**
 * �жϴ��Ƿ�Ϊ��
 * @param S ��
 * @return �Ƿ�Ϊ�մ�
 */
Status StrEmpty(String S) {
    // �±�Ϊ0��λ�ô洢���ĳ��ȣ�������0����Ϊ��
    if (S[0] == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * �Ƚϴ�S��T�Ĵ�С
 * ��S>T������ֵ>0����S=T������ֵΪ0����S<T������ֵ<0
 * @param S ��
 * @param T ��
 * @return ��S�Ƿ�ȴ�T��
 */
int StrCompare(String S, String T) {
    int i; // ���ڱ���Ԫ��

    // ������������
    for (i = 0; i <= S[0] && i <= T[0]; i++) {
        // ������Ӧλ���ַ������
        if (S[i] != T[i]) {
            // ʹ�ö�Ӧλ��
            return S[i] - T[i];
        }
    }
    // ʹ���������ĳ������
    return S[0] - T[0];
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
 * ����S1��S2���µĴ�T
 * ���δ�ضϷ���TRUE���ض��򷵻�FALSE
 * @param T ���ӳɵ��´�
 * @param S1 ��
 * @param S2 ��
 * @return �Ƿ�����ӳɵ��ַ����ض�
 */
Status Concat(String T, String S1, String S2) {
    int i; // ���ڱ���Ԫ��

    // ��T�Ĵ�С����װ�´�S1�ʹ�S2������
    if (S1[0] + S2[0] <= MAXSIZE) {
        // ����S1���������ݵ�T��
        for (i = 1; i <= S1[0]; i++) {
            T[i] = S1[i];
        }
        // ����S2���������ݵ�T��
        for (i = 1; i <= S2[0]; i++) {
            T[S1[0] + i] = S2[i]; // S2��������S1������֮��
        }
        // ��T�ĳ��ȵ���S1��S2�ĳ���֮��
        T[0] = S1[0] + S2[0];
        return TRUE; // ��ʾS2�ַ���δ���ض�
    }
    // ��T�Ĵ�С����װ�´�S1�ʹ�S2�����ݣ����ض�S2
    else {
        // ����S1���������ݵ�T��
        for (i = 1; i <= S1[0]; ++i) {
            T[i] = S1[i];
        }
        // ��δ����T����󳤶�ʱ������S2�����ݵ�T��
        for (i = 1; i <= MAXSIZE - S1[0]; i++) {
            T[S1[0] + i] = S2[i]; // S2��������S1������֮��
        }
        // T�ĳ��ȵ����޶�����󳤶�
        T[0] = MAXSIZE;
        return FALSE; // ��ʾ�ַ���S2���ض�
    }
}

/**
 * �ô�Sub���ش�S��pos���ַ��𳤶�Ϊlen���ַ�
 * @param Sub ��ȡ���Ӵ�
 * @param S ԭ��
 * @param pos ��ʼ��ȡλ��
 * @param len ��ȡ����
 * @return ִ��״̬
 */
Status SubString(String Sub, String S, int pos, int len) {
    int i; // ���ڱ���Ԫ��

    // ��ȡ�Ŀ�ʼλ�û򳤶Ȳ�������ȡʧ��
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1) {
        return ERROR;
    }

    // ��ȡ��S�д�posλ�ÿ�ʼ������Ϊlen�����ݵ���Sub��
    for (i = 1; i <= len; ++i) {
        Sub[i] = S[pos + i - 1];
    }
    // ����Sub�ĳ�������Ϊlen
    Sub[0] = len;
    return OK;
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
 * �ڴ�S�ĵ�pos��λ�ò��봮T��ֵ
 * ����TRUE��ʾ��ȫ��T�����ݲ���S�У�FALSE��ʾ������ȫ��T�����ݲ���S��
 * @param S ��S
 * @param pos �±�
 * @param T ��T
 * @return ִ��״̬
 */
Status StrInsert(String S, int pos, String T) {
    int i; // ���ڱ���Ԫ��

    // ����λ�ò������������
    if (pos < 1 || pos > S[0] + 1) {
        return ERROR;
    }

    // ��T���㹻��λ����ȫ���봮S��
    if (S[0] + T[0] <= MAXSIZE) {
        // ��S��iλ�ÿ�ʼ������Ԫ������ƶ���T�ĳ���
        for (i = S[0]; i >= pos; i--) {
            S[i + T[0]] = S[i];
        }
        // �ӵ�i��λ�ò��봮T��ֵ
        for (i = pos; i < pos + T[0]; i++) {
            S[i] = T[i - pos + 1];
        }
        // ����S�ĳ���Ϊԭ��S�ĳ�����T����֮��
        S[0] = S[0] + T[0];
        return TRUE; // ����TRUE��ʾ��ȫ��T�����ݲ���S��
    } else {  // ��Tû�����㹻��λ����ȫ���봮S�У�ֻ�ܲ��ֲ���
        // ��S��posλ�ÿ�ʼ��Ԫ������ƶ�T��λ��
        for (i = MAXSIZE; i <= pos; i--) {
            S[i] = S[i - T[0]];
        }
        // �ӵ�i��λ�ò��봮T��ֵ
        for (i = pos; i < pos + T[0]; i++) {
            S[i] = T[i - pos + 1];
        }
        S[0] = MAXSIZE; // S�ĳ���Ϊ����ʼֵ
        return FALSE; // ����FALSE��ʾ������ȫ��T�����ݲ���S��
    }
}

/**
 * �Ӵ�S�ĵ�pos��λ�ÿ�ʼ��ɾ��len�����ȵ�����
 * @param S ��S
 * @param pos ��ʼɾ�����±�
 * @param len ɾ���ĳ���
 * @return ִ��״̬
 */
Status StrDelete(String S, int pos, int len) {
    int i; // ���ڱ���Ԫ��

    // ɾ��λ�ò�����ɾ��ʧ��
    if (pos < 1 || pos > S[0] - len + 1 || len < 0) {
        return ERROR;
    }

    // ����ɾ��λ�õ�ֵ�ú����ֵ����
    for (i = pos + len; i <= S[0]; i++) {
        S[i - len] = S[i];
    }

    S[0] -= len; // S�ĳ��ȼ�ȥlen
    return OK;
}

/**
 * ��S�����е��ڴ�T������ȫ���ô�V�����滻
 * @param S ��S
 * @param T ��T ���滻
 * @param V ��V �滻��������
 * @return ִ��״̬
 */
Status Replace(String S, String T, String V) {
    int i = 1; // �Ӵ�S�ĵ�һ���ַ�����Ҵ�T

    // ��T�ǿմ����滻ʧ��
    if (StrEmpty(T)) {
        return ERROR;
    }

    do {
        i = Index(S, T, i); // ��λ�ִ�T�ڴ�S��pos���ַ�֮���λ��
        // ��T�ڴ�S�д���
        if (i) {
            StrDelete(S, i, StrLength(T)); // �ڴ�S��ɾ����T
            StrInsert(S, i, V); // ��ԭ��T��λ��ɾ����V
            i += StrLength(V); // �ڲ���Ĵ�V�ĺ���������Ҵ�T
        }
    } while (i); // ����S�л��д�T�Ĵ���
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

int main() {
    String t, s1, s2; // ��
    Status status; // ִ��״̬
    int index; // ��ʼ����

    status = StrEmpty(t); // �ж��ַ���t�Ƿ�Ϊ��

    printf("��t�Ƿ�Ϊ�գ�%s\n", status == TRUE ? "��" : "��");

    /*** ���ַ���S��ֵΪabcd ***/
    status = StrAssign(t, "ab");

    printf("��t��ֵΪ��");
    StrPrint(t); // ��ӡ��t
    printf("��t�ĳ���Ϊ��%d\n", StrLength(t)); // ��ȡ���ĳ���
    
    /*** ���ַ���S��ֵΪabcd ***/
    status = StrAssign(s1, "abcd"); // ���ַ���S��ֵΪabcd
    
    printf("���ַ���S��ֵΪabcd�󣬴�s1��ֵΪ��");
    StrPrint(s1); // ��ӡ��s1
    printf("��s1�ĳ���Ϊ��%d\n", StrLength(s1)); // ��ȡ���ĳ���

    /*** ���ƴ�s1�����ݵ�s2�� ***/
    StrCopy(s2, s1); // ���ƴ�s1�����ݵ�s2��
    printf("���ƴ�s1�����ݵ�s2�󣬴�s2��ֵΪ��");
    StrPrint(s2); // ��ӡ��s2
    printf("��s2�ĳ���Ϊ��%d\n", StrLength(s1)); // ��ȡ���ĳ���

    /*** �Ƚ�t��s1�Ĵ�С ***/
    status = StrCompare(t, s1);

    if (status > 0) {
        printf("t����s1\n");
    } else if (status == 0) {
        printf("t����s1\n");
    } else {
        printf("tС��s2\n");
    }

    /*** ����ַ���s2�е����� ***/
    status = ClearString(s2);
    printf("s2�Ƿ�Ϊ�մ���%s\n", StrEmpty(s2) == TRUE ? "��" : "��");

    /*** ��s1��s2���Ӻ��ֵ����ֵ����t ***/
    status = StrAssign(s2, "efg"); // ���¸�ֵ��s2����efg

    status = Concat(t, s1, s2); // ����s1��s2��ֵ����ֵ����t
    printf("����s1��s2��ֵ��t�󣬴�t��ֵΪ��");
    StrPrint(t); // ��ӡ��t

    /*** ��ȡ��t�Ĳ������ݵ���s2 ***/
    status = SubString(s2, t, 2, 3); // �Ӵ�t��2�±�λ�ý�ȡ3���ַ�����ֵ��s2

    printf("��ȡ��t�Ĳ������ݺ󣬴�s2��ֵΪ��");
    StrPrint(s2); // ��ӡ��

    /*** ��λ�Ӵ�s2�ڴ�t�е���ʼλ�� ***/
    index = Index(t, s2, 0); // ��λ�Ӵ�s2�ڴ�t�е���ʼλ�ã���0�±꿪ʼͳ�ƣ�
    printf("��s2��t��λ��Ϊ��%d\n", index);

    /*** �ڴ�t�±�Ϊ4��λ�ò��봮s1 ***/
    status = StrInsert(t, 4, s1); // �ڴ�t�±�Ϊ4��λ�ò��봮s1
    printf("�±�Ϊ4��λ�ò���s1�󣬴�t��ֵΪ��");
    StrPrint(t); // ��ӡ��

    /*** �ڴ�t�±�Ϊ4��λ��ɾ��4���ַ� ***/
    status = StrDelete(t, 4, 4); // �ڴ�t�±�Ϊ4��λ��ɾ��4���ַ�

    printf("�±�Ϊ4��λ��ɾ�������ַ��󣬴�t��ֵΪ��");
    StrPrint(t); // ��ӡ��

    /*** �滻��t�е�abcd��123 ***/
    status = StrAssign(s2, "123"); // ���¸�ֵ��s2����123
    status = StrAssign(t, "abcdggggabcdggggabcd"); // ���¸�ֵ����t

    status = Replace(t, s1, s2); // �ڴ�t�У���s2��ֵ�滻��s1��ֵ

    printf("�滻���ݺ󣬴�t��ֵΪ��");
    StrPrint(t); // ��ӡ��
}