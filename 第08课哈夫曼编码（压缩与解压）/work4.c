#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef struct Node {
    char name[4];  // 存放汉字字符
    int weight;  // 存放权重
    int left;  // 左孩子
    int right;  // 右孩子
    int parent;  // 父节点
    char code[50];  // 哈夫曼编码
} HTNode, *HuffmanTree;

int n = 0;  // 节点个数
char leaf_name[5000][4];   // 节点字符
int leaf_weight[5000]; // 节点权重
char huf[5000][2][30];  // 存放字符及其对应的哈夫曼编码
int hu = 0; // 索引，用于查找字符

// 读取权重文件
void ReadWright() {
    FILE *file1;    // 权重文件

    // 打开文件
    file1 = fopen("权重.txt", "r");
    if (file1 == NULL) {
        printf("权重文件打开失败");
        exit(1);
    }

    // 逐个读取文件内容并存储
    char line[50];
    while (fgets(line, sizeof(line), file1) != NULL) {
        n++;
        char *token = strtok(line, ":\n");
        strcpy(leaf_name[n], token);
        token = strtok(NULL, ":\n");
        leaf_weight[n] = atoi(token);
    }

    // 关闭文件
    fclose(file1);
    printf("权重文件读取成功\n");
}

// 选择两个最小的节点
void select(HuffmanTree HT, int end, int *s1, int *s2) {
    int min1 = INT_MAX, min2 = INT_MAX;
    for (int i = 1; i <= end; ++i) {
        if (HT[i].parent == 0) { // 只考虑还没有父节点的节点
            if (HT[i].weight < min1) { // 找到比当前最小还小的节点
                min2 = min1;
                *s2 = *s1; // 更新第二最小的节点
                min1 = HT[i].weight;
                *s1 = i; // 更新最小的节点
            } else if (HT[i].weight < min2) { // 找到比第二小的还小，但比最小的大的节点
                min2 = HT[i].weight;
                *s2 = i;
            }
        }
    }
}

// 创建哈夫曼树
void Create(HuffmanTree HT) {
    // 初始化哈夫曼树全部节点
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

    // 构建哈夫曼树
    for (int i = n + 1; i <= 2 * n - 1; ++i) {
        int s1, s2;
        select(HT, i - 1, &s1, &s2);     // 选择两个最小节点
        HT[s1].parent = i;
        HT[s2].parent = i; // 设置选中节点的父节点
        HT[i].left = s1;
        HT[i].right = s2; // 设置新节点的子节点
        HT[i].weight = HT[s1].weight + HT[s2].weight; // 新节点的权重是两个子节点权重之和

    }
    printf("哈夫曼树创建成功\n");
}

// 显示哈夫曼树数组
void DisplayHuffmanTree(HuffmanTree HT) {
    printf("索引\t字符\t权重\t左孩子\t右孩子\t父节点\t哈夫曼编码\n");
    for (int i = 1; i <= 2 * n - 1; ++i) { // 遍历打印每个节点
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%s\n", i, HT[i].name, HT[i].weight, HT[i].left, HT[i].right,
               HT[i].parent, HT[i].code);
    }
}

// 获得哈夫曼编码并生成编码文件
void GetHuffmanCode(HuffmanTree HT) {
    // 打开编码文件
    FILE *file2 = fopen("编码.txt", "w");
    if (file2 == NULL) {
        printf("打开文件失败");
    }

    //遍历叶子结点得到哈夫曼编码
    for (int i = 1; i <= n; ++i) {
        char code[50];
        int current = i;
        int a = 0;

        // 由叶子节点一直遍历到根节点
        while (current != 0) {
            // 得到哈夫曼编码
            if (HT[HT[current].parent].left == current) {
                code[a++] = '0';
            } else if (HT[HT[current].parent].right == current) {
                code[a++] = '1';
            }
            current = HT[current].parent;
        }

        // 输出字符
        fprintf(file2, "%s:", HT[i].name);

        // 输出哈夫曼编码
        int m = 0;
        for (int j = a; j >= 0; --j) {
            if (code[j] == '0' || code[j] == '1') {
                HT[i].code[m++] = code[j];
                fprintf(file2, "%c", code[j]);
            }
        }
        HT[i].code[m] = '\0';

        // 换行，为下次输出做准备
        fprintf(file2, "\n");
    }

    // 关闭文件
    fclose(file2);
    printf("获取哈夫曼编码成功\n");
}

// 读取哈夫曼编码
void compress_read() {
    // 打开文件
    FILE *file2 = fopen("编码.txt", "r");
    if (file2 == NULL) {
        printf("打开文件失败\n");
        exit(1);
    }

    // 读取内容
    char line[50];
    while (fgets(line, sizeof(line), file2) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // 去除换行符
        char *token = strtok(line, ":\n");
        strcpy(huf[hu][0], token);
        token = strtok(NULL, ":\n");
        strcpy(huf[hu++][1], token);

    }

    // 关闭文件
    fclose(file2);
    printf("哈夫曼编码文件读取成功\n");
}

// 压缩原文并得到二进制文件
void compress() {
    // 打开文件
    FILE *file3 = fopen("三国演义.txt", "r");
    if (file3 == NULL) {
        printf("原文打开失败");
        exit(1);
    }
    FILE *file4 = fopen("压缩.txt", "w");
    if (file4 == NULL) {
        printf("压缩文件打开失败");
        exit(1);
    }

    // 逐字压缩
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

    // 关闭文件
    fclose(file3);
    fclose(file4);
    printf("压缩成功\n");
}

// 解压得到原文
void decompress(HuffmanTree HT) {
    // 打开文件
    FILE *file4 = fopen("压缩.txt", "rb");
    if (file4 == NULL) {
        printf("压缩文件打开失败");
        exit(1);
    }
    FILE *file5 = fopen("解压.txt", "w");
    if (file5 == NULL) {
        printf("解压文件打开失败");
        exit(1);
    }

    // 逐字解压
    int current = 2 * n - 1;  // 从哈夫曼树的根节点开始
    char ch;
    while (fread(&ch, sizeof(ch), 1, file4) > 0) {
        for (int i = 7; i >= 0; --i) {
            if ((ch >> i) & 1) {  // 读取一个比特
                current = HT[current].right;  // 如果为1，移动到右孩子
            } else {
                current = HT[current].left;  // 如果为0，移动到左孩子
            }
            if (current <= n) {  // 到达叶子节点，输出对应字符
                if (strcmp(HT[current].name, "^") == 0) {
                    fprintf(file5, "\u3000");
                } else if (strcmp(HT[current].name, "*") == 0) {
                    fprintf(file5, " ");
                } else if (strcmp(HT[current].name, "+") == 0) {
                    fprintf(file5, "\n");
                } else {
                    fprintf(file5, "%s", HT[current].name);
                }
                current = 2 * n - 1;  // 从根节点重新开始
            }
        }
    }

    //关闭文件
    fclose(file4);
    fclose(file5);
    printf("解压成功\n");
}

int main() {
    // 读取权重文件
    ReadWright();

    // 申请哈夫曼树内存并创建哈夫曼树
    HuffmanTree HT = (HuffmanTree) malloc((2 * n) * sizeof(HTNode));    // 0号位置不用
    Create(HT);

    // 获得哈夫曼编码
    GetHuffmanCode(HT);

    // 显示哈夫曼树
//    DisplayHuffmanTree(HT);

    // 压缩文件
    compress_read();
    compress();

    // 解压文件
    decompress(HT);

    return 0;
}