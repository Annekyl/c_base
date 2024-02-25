#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义哈夫曼树的结点
typedef struct HuffmanNode {
    unsigned int freq;      // 汉字出现的频率
    unsigned char ch;       // 汉字
    struct HuffmanNode *left, *right;
} HuffmanNode;

// 创建哈夫曼树
HuffmanNode* createHuffmanTree(unsigned int *freq) {
    // 创建结点数组
    int n = 0;    // 汉字的种类数
    for (int i = 0; i < 65536; i++) {
        if (freq[i] > 0) {
            n++;
        }
    }

    HuffmanNode **nodes = (HuffmanNode**)malloc(n * sizeof(HuffmanNode*));
    int j = 0;
    for (int i = 0; i < 65536; i++) {
        if (freq[i] > 0) {
            HuffmanNode *node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
            node->freq = freq[i];
            node->ch = i;
            node->left = NULL;
            node->right = NULL;
            nodes[j++] = node;
        }
    }

    // 构建哈夫曼树
    while (n > 1) {
        // 找出最小的两个结点
        int min1 = 0, min2 = 1;
        if (nodes[min1]->freq > nodes[min2]->freq) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < n; i++) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            }
            else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }

        // 创建新结点，合并两个最小结点
        HuffmanNode *newNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        newNode->freq = nodes[min1]->freq + nodes[min2]->freq;
        newNode->ch = 0;
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        // 将新结点插入结点数组中
        nodes[min1] = newNode;
        nodes[min2] = nodes[n - 1];
        n--;
    }

    return nodes[0];
}

// 生成汉字的哈夫曼编码
void generateHuffmanCode(HuffmanNode *root, char **codes, char *code) {
    if (root->left == NULL && root->right == NULL) {
        int ch = root->ch;
        codes[ch] = (char*)malloc((strlen(code) + 1) * sizeof(char));
        strcpy(codes[ch], code);
        return;
    }

    int len = strlen(code);
    code[len] = '0';
    code[len + 1] = '\0';
    generateHuffmanCode(root->left, codes, code);

    code[len] = '1';
    code[len + 1] = '\0';
    generateHuffmanCode(root->right, codes, code);

    code[len] = '\0';
}

int main() {
    // 假设频率数据已经给出，freq数组中存储了汉字的频率
    unsigned int freq[65536] = {0};  // 汉字频率统计，假设已经初始化

    HuffmanNode *root = createHuffmanTree(freq);

    char *codes[65536] = {NULL};  // 汉字的哈夫曼编码
    char code[65536] = {0};  // 当前路径

    generateHuffmanCode(root, codes, code);

    // 输出汉字及其对应的哈夫曼编码
    for (int i = 0; i < 65536; i++) {
        if (codes[i] != NULL) {
            printf("%c: %s\n", i, codes[i]);
        }
    }

    return 0;
}
