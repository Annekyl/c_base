#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    const char *name;
    int weight;
    int parent;
    int lchild;
    int rchild;
} Node;

void compare(int *s1, int *s2, Node *ps, int n) {
    int min1 = 9999999, min2 = 9999999, i;

    for (i = 0; i < 2 * n - 1; i++) {
        if (ps[i].weight != 0 && ps[i].parent == -1) {
            if (min1 > ps[i].weight) {
                *s1 = i;
                min1 = ps[i].weight;
            }
        }
    }

    for (i = 0; i < 2 * n - 1; i++) {
        if (ps[i].weight != 0 && ps[i].parent == -1) {
            if (min2 > ps[i].weight && i != *s1) {
                *s2 = i;
                min2 = ps[i].weight;
            }
        }
    }
}

Node *create(int leaf_weight[], const char hanzi[][20], int n) {
    int s1, s2;
    Node *ps = (Node *)malloc((2 * n - 1) * sizeof(Node));

    for (int i = 0; i < 2 * n - 1; i++) {
        ps[i].parent = ps[i].lchild = ps[i].rchild = -1;
        if (i < n) {
            ps[i].weight = leaf_weight[i];
            ps[i].name = strdup(hanzi[i]);
        } else {
            ps[i].weight = 0;
            ps[i].name = "";  // ��ʼ��Ϊ���ַ���
        }
    }

    for (int i = n; i < 2 * n - 1; i++) {
        compare(&s1, &s2, ps, n);
        ps[i].weight = ps[s1].weight + ps[s2].weight;
        ps[s2].parent = ps[s1].parent = i;
        ps[i].lchild = s1;
        ps[i].rchild = s2;
    }
    return ps;
}

void writeHuffmanCodeToFile(Node *ps, int n) {
    FILE *file;
    file = fopen("����������.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ�");
        exit(1);
    }
    else {
        for (int i = 0; i < n; i++) {
            fprintf(file, "%s\t", ps[i].name);
            int current = i;
            char huffmanCode[256] = "";  // ʹ���������洢����������
            while (ps[current].parent != -1)
            {
                if (current == ps[ps[current].parent].lchild) {
                    strcat(huffmanCode, "0");
                }
                else if (current == ps[ps[current].parent].rchild) {
                    strcat(huffmanCode, "1");
                }
                current = ps[current].parent;
            }
            int len = strlen(huffmanCode);
            for (int j = 0; j < len / 2; j++) {
                char temp = huffmanCode[j];
                huffmanCode[j] = huffmanCode[len - j - 1];
                huffmanCode[len - j - 1] = temp;
            }
            fprintf(file, "%s\n", huffmanCode);
            printf("%s\n", huffmanCode);
        }
        fclose(file);  // ��д����ɺ�ر��ļ�
    }
}

int main() {
    int n;
    FILE *weight_file = fopen("Ȩ��2.txt", "r");
    if (weight_file == NULL) {
        printf("�޷���Ȩ���ļ�");
        exit(1);
    }

    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), weight_file)) {
        if (strlen(line) > 1) {  // ����е������Ƿ����1�������ֿ���
            count++;
        }
    }
    n = count;
    fseek(weight_file, 0, SEEK_SET);

    char hanzi[n][20];
    int leaf_weight[n];

    for (int i = 0; i < n; i++)
    {
        if (fgets(line, sizeof(line), weight_file))
        {
            char *token = strtok(line, ":");
            if (token != NULL)
            {
                strncpy(hanzi[i], token, sizeof(hanzi[i]) - 1);
                hanzi[i][sizeof(hanzi[i]) - 1] = '\0';  // ȷ���ַ�����ֹ��
                token = strtok(NULL, ":");
                if (token != NULL)
                {
                    leaf_weight[i] = atoi(token);
                }
                else
                {
                    printf("��ȡ�ļ�ʧ��");
                    fclose(weight_file);
                    exit(1);
                }
                printf("%s %d\n", hanzi[i], leaf_weight[i]);  // ������
            }
            else
            {
                printf("��ȡ�ļ�ʧ��");
                fclose(weight_file);
                exit(1);
            }
        } else {
            printf("��ȡ�ļ�ʧ��");
            fclose(weight_file);
            exit(1);
        }
    }
    fclose(weight_file);

    Node *ps = create(leaf_weight, hanzi, n);//������������
    writeHuffmanCodeToFile(ps, n);//����

    for (int i = 0; i < n; i++) {
        free((void*)ps[i].name);
    }
    free(ps);

    return 0;
}
