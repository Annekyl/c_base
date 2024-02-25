#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // 为了使用INT_MAX

// 定义哈夫曼树的节点结构
typedef struct {
    int weight; // 节点的权重
    int parent, lchild, rchild; // 父节点、左孩子、右孩子在数组中的索引
} HTNode, *HuffmanTree;

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
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n) {
    if (n <= 1) return; // 如果只有一个或没有字符，则不进行操作
    int m = 2 * n - 1; // 计算总节点数
    *HT = (HTNode *) malloc((m + 1) * sizeof(HTNode)); // 分配空间，0号位置不用
    HuffmanTree ht = *HT;
    for (int i = 1; i <= n; ++i) { // 初始化叶子节点
        ht[i].weight = w[i - 1];
        ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
    }
    for (int i = n + 1; i <= m; ++i) { // 初始化非叶子节点
        ht[i].weight = ht[i].parent = ht[i].lchild = ht[i].rchild = 0;
    }

    // 构建哈夫曼树
    for (int i = n + 1; i <= m; ++i) {
        int s1, s2;
        select(ht, i - 1, &s1, &s2); // 选择最小的两个节点
        ht[s1].parent = i;
        ht[s2].parent = i; // 设置选中节点的父节点
        ht[i].lchild = s1;
        ht[i].rchild = s2; // 设置新节点的子节点
        ht[i].weight = ht[s1].weight + ht[s2].weight; // 新节点的权重是两个子节点权重之和
    }
}

// 显示哈夫曼树数组
void DisplayHuffmanTree(HuffmanTree HT, int n) {
    int m = 2 * n - 1; // 总节点数
    printf("索引\t权重\t父结点\t左孩子\t右孩子\n");
    for (int i = 1; i <= m; ++i) { // 遍历打印每个节点
        // 注意：非叶子节点的字符可能不是有效字符
        printf("%d\t%d\t%d\t%d\t%d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild,
               HT[i].rchild);
    }
}

int main() {
    int w[5];
    for (int i = 0; i < 5; ++i) {
        printf("请输入权重");
        scanf("%d", &w[i]);
    }
    int n = sizeof(w) / sizeof(w[0]); // 权重的数量
    HuffmanTree HT;

    CreateHuffmanTree(&HT, w, n); // 创建哈夫曼树
    DisplayHuffmanTree(HT, n); // 显示哈夫曼树

    free(HT); // 释放分配的内存
    return 0;
}
