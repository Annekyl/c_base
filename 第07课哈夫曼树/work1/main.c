#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Ϊ��ʹ��INT_MAX

// ������������Ľڵ�ṹ
typedef struct {
    int weight; // �ڵ��Ȩ��
    int parent, lchild, rchild; // ���ڵ㡢���ӡ��Һ����������е�����
} HTNode, *HuffmanTree;

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
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n) {
    if (n <= 1) return; // ���ֻ��һ����û���ַ����򲻽��в���
    int m = 2 * n - 1; // �����ܽڵ���
    *HT = (HTNode *) malloc((m + 1) * sizeof(HTNode)); // ����ռ䣬0��λ�ò���
    HuffmanTree ht = *HT;
    for (int i = 1; i <= n; ++i) { // ��ʼ��Ҷ�ӽڵ�
        ht[i].weight = w[i - 1];
        ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
    }
    for (int i = n + 1; i <= m; ++i) { // ��ʼ����Ҷ�ӽڵ�
        ht[i].weight = ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
    }

    // ������������
    for (int i = n + 1; i <= m; ++i) {
        int s1, s2;
        select(ht, i - 1, &s1, &s2); // ѡ����С�������ڵ�
        ht[s1].parent = i;
        ht[s2].parent = i; // ����ѡ�нڵ�ĸ��ڵ�
        ht[i].lchild = s1;
        ht[i].rchild = s2; // �����½ڵ���ӽڵ�
        ht[i].weight = ht[s1].weight + ht[s2].weight; // �½ڵ��Ȩ���������ӽڵ�Ȩ��֮��
    }
}

// ��ʾ������������
void DisplayHuffmanTree(HuffmanTree HT, int n) {
    int m = 2 * n - 1; // �ܽڵ���
    printf("����\tȨ��\t�����\t����\t�Һ���\n");
    for (int i = 1; i <= m; ++i) { // ������ӡÿ���ڵ�
        // ע�⣺��Ҷ�ӽڵ���ַ����ܲ�����Ч�ַ�
        printf("%d\t%d\t%d\t%d\t%d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild,
               HT[i].rchild);
    }
}

int main() {
    int w[5];
    for (int i = 0; i < 5; ++i) {
        printf("������Ȩ��");
        scanf("%d", &w[i]);
    }
    int n = sizeof(w) / sizeof(w[0]); // Ȩ�ص�����
    HuffmanTree HT;

    CreateHuffmanTree(&HT, w, n); // ������������
    DisplayHuffmanTree(HT, n); // ��ʾ��������

    free(HT); // �ͷŷ�����ڴ�
    return 0;
}
