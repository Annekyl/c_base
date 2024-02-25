#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef struct Node {
    char name[4];  // ��ź����ַ�
    int weight;  // ���Ȩ��
    int left;  // ����
    int right;  // �Һ���
    int parent;  // ���ڵ�
    char code[50];  // ����������
} HTNode, *HuffmanTree;

int n = 0;  // �ڵ����
char leaf_name[5000][4];   // �ڵ��ַ�
int leaf_weight[5000]; // �ڵ�Ȩ��
char huf[5000][2][30];  // ����ַ������Ӧ�Ĺ���������
int hu = 0; // ���������ڲ����ַ�

// ��ȡȨ���ļ�
void ReadWright() {
    FILE *file1;    // Ȩ���ļ�

    // ���ļ�
    file1 = fopen("Ȩ��.txt", "r");
    if (file1 == NULL) {
        printf("Ȩ���ļ���ʧ��");
        exit(1);
    }

    // �����ȡ�ļ����ݲ��洢
    char line[50];
    while (fgets(line, sizeof(line), file1) != NULL) {
        n++;
        char *token = strtok(line, ":\n");
        strcpy(leaf_name[n], token);
        token = strtok(NULL, ":\n");
        leaf_weight[n] = atoi(token);
    }

    // �ر��ļ�
    fclose(file1);
    printf("Ȩ���ļ���ȡ�ɹ�\n");
}

// ѡ��������С�Ľڵ�
void select(HuffmanTree HT, int end, int *s1, int *s2) {
    int min1 = INT_MAX, min2 = INT_MAX;
    for (int i = 1; i <= end; ++i) {
        if (HT[i].parent == 0) { // ֻ���ǻ�û�и��ڵ�Ľڵ�
            if (HT[i].weight < min1) { // �ҵ��ȵ�ǰ��С��С�Ľڵ�
                min2 = min1;
                *s2 = *s1; // ���µڶ���С�Ľڵ�
                min1 = HT[i].weight;
                *s1 = i; // ������С�Ľڵ�
            } else if (HT[i].weight < min2) { // �ҵ��ȵڶ�С�Ļ�С��������С�Ĵ�Ľڵ�
                min2 = HT[i].weight;
                *s2 = i;
            }
        }
    }
}

// ������������
void Create(HuffmanTree HT) {
    // ��ʼ����������ȫ���ڵ�
    for (int i = 1; i <= 2 * n - 1; i++) {
        HT[i].parent = HT[i].left = HT[i].right = 0;
        strcpy(HT[i].code, "\0");
        if (i <= n) {
            HT[i].weight = leaf_weight[i];
            strcpy(HT[i].name, leaf_name[i]);
        } else {
            HT[i].weight = 0;
            strcpy(HT[i].name, "\0");
        }
    }

    // ������������
    for (int i = n + 1; i <= 2 * n - 1; ++i) {
        int s1, s2;
        select(HT, i - 1, &s1, &s2);     // ѡ��������С�ڵ�
        HT[s1].parent = i;
        HT[s2].parent = i; // ����ѡ�нڵ�ĸ��ڵ�
        HT[i].left = s1;
        HT[i].right = s2; // �����½ڵ���ӽڵ�
        HT[i].weight = HT[s1].weight + HT[s2].weight; // �½ڵ��Ȩ���������ӽڵ�Ȩ��֮��

    }
    printf("�������������ɹ�\n");
}

// ��ʾ������������
void DisplayHuffmanTree(HuffmanTree HT) {
    printf("����\t�ַ�\tȨ��\t����\t�Һ���\t���ڵ�\t����������\n");
    for (int i = 1; i <= 2 * n - 1; ++i) { // ������ӡÿ���ڵ�
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%s\n", i, HT[i].name, HT[i].weight, HT[i].left, HT[i].right,
               HT[i].parent, HT[i].code);
    }
}

// ��ù��������벢���ɱ����ļ�
void GetHuffmanCode(HuffmanTree HT) {
    // �򿪱����ļ�
    FILE *file2 = fopen("����.txt", "w");
    if (file2 == NULL) {
        printf("���ļ�ʧ��");
    }

    //����Ҷ�ӽ��õ�����������
    for (int i = 1; i <= n; ++i) {
        char code[50];
        int current = i;
        int a = 0;

        // ��Ҷ�ӽڵ�һֱ���������ڵ�
        while (current != 0) {
            // �õ�����������
            if (HT[HT[current].parent].left == current) {
                code[a++] = '0';
            } else if (HT[HT[current].parent].right == current) {
                code[a++] = '1';
            }
            current = HT[current].parent;
        }

        // ����ַ�
        fprintf(file2, "%s:", HT[i].name);

        // �������������
        int m = 0;
        for (int j = a; j >= 0; --j) {
            if (code[j] == '0' || code[j] == '1') {
                HT[i].code[m++] = code[j];
                fprintf(file2, "%c", code[j]);
            }
        }
        HT[i].code[m] = '\0';

        // ���У�Ϊ�´������׼��
        fprintf(file2, "\n");
    }

    // �ر��ļ�
    fclose(file2);
    printf("��ȡ����������ɹ�\n");
}

// ��ȡ����������
void compress_read() {
    // ���ļ�
    FILE *file2 = fopen("����.txt", "r");
    if (file2 == NULL) {
        printf("���ļ�ʧ��\n");
        exit(1);
    }

    // ��ȡ����
    char line[50];
    while (fgets(line, sizeof(line), file2) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // ȥ�����з�
        char *token = strtok(line, ":\n");
        strcpy(huf[hu][0], token);
        token = strtok(NULL, ":\n");
        strcpy(huf[hu++][1], token);

    }

    // �ر��ļ�
    fclose(file2);
    printf("�����������ļ���ȡ�ɹ�\n");
}

// ѹ��ԭ�Ĳ��õ��������ļ�
void compress() {
    // ���ļ�
    FILE *file3 = fopen("��������.txt", "r");
    if (file3 == NULL) {
        printf("ԭ�Ĵ�ʧ��");
        exit(1);
    }
    FILE *file4 = fopen("ѹ��.txt", "w");
    if (file4 == NULL) {
        printf("ѹ���ļ���ʧ��");
        exit(1);
    }

    // ����ѹ��
    char word[3];
    unsigned char ch = 0;// 0000 0000
    int bit = 0;
    while (fgets(word, sizeof(word), file3)) {
        for (int i = 0; i <= hu; i++) {
            if (strcmp(huf[i][0], word) == 0) {
                for (int k = 0; k < strlen(huf[i][1]); k++) {
                    ch += (huf[i][1][k] - '0');
                    bit++;
                    if (bit == 8) {
                        fwrite(&ch, sizeof(char), 1, file4);
                        bit = 0;
                    }
                    ch = ch << 1;
                }
                memset(word, '\0', sizeof(word));
            }
        }
    }

    // �ر��ļ�
    fclose(file3);
    fclose(file4);
    printf("ѹ���ɹ�\n");
}

// ��ѹ�õ�ԭ��
void decompress(HuffmanTree HT) {
    // ���ļ�
    FILE *file4 = fopen("ѹ��.txt", "rb");
    if (file4 == NULL) {
        printf("ѹ���ļ���ʧ��");
        exit(1);
    }
    FILE *file5 = fopen("��ѹ.txt", "w");
    if (file5 == NULL) {
        printf("��ѹ�ļ���ʧ��");
        exit(1);
    }

    // ���ֽ�ѹ
    int current = 2 * n - 1;  // �ӹ��������ĸ��ڵ㿪ʼ
    char ch;
    while (fread(&ch, sizeof(ch), 1, file4) > 0) {
        for (int i = 7; i >= 0; --i) {
            if ((ch >> i) & 1) {  // ��ȡһ������
                current = HT[current].right;  // ���Ϊ1���ƶ����Һ���
            } else {
                current = HT[current].left;  // ���Ϊ0���ƶ�������
            }
            if (current <= n) {  // ����Ҷ�ӽڵ㣬�����Ӧ�ַ�
                if (strcmp(HT[current].name, "^") == 0) {
                    fprintf(file5, "\u3000");
                } else if (strcmp(HT[current].name, "*") == 0) {
                    fprintf(file5, " ");
                } else if (strcmp(HT[current].name, "+") == 0) {
                    fprintf(file5, "\n");
                } else {
                    fprintf(file5, "%s", HT[current].name);
                }
                current = 2 * n - 1;  // �Ӹ��ڵ����¿�ʼ
            }
        }
    }

    //�ر��ļ�
    fclose(file4);
    fclose(file5);
    printf("��ѹ�ɹ�\n");
}

int main() {
    // ��ȡȨ���ļ�
    ReadWright();

    // ������������ڴ沢������������
    HuffmanTree HT = (HuffmanTree) malloc((2 * n) * sizeof(HTNode));    // 0��λ�ò���
    Create(HT);

    // ��ù���������
    GetHuffmanCode(HT);

    // ��ʾ��������
//    DisplayHuffmanTree(HT);

    // ѹ���ļ�
    compress_read();
    compress();

    // ��ѹ�ļ�
    decompress(HT);

    return 0;
}