/*
* 程序：使用Huffman编码进行英文文档的编码、压缩、译码全过程
* 作者：友人帐_
* 文章地址：https://blog.csdn.net/m15253053181/article/details/127457700?spm=1001.2014.3001.5501
* 个人主页：https://blog.csdn.net/m15253053181?type=blog
* 希望可以帮助到大家，也欢迎进入我的主页查看更多优质文章~
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 100
#define MAXBIT 256

/* 字符Huffman结点 */
typedef struct HuffmanNode {
    char character;             // 字符
    long count;                 // 出现频数
    char code[MAXBIT];          // 编码
    struct HuffmanNode *lchild; // 左孩子
    struct HuffmanNode *rchild; // 右孩子
    struct HuffmanNode *parent; // 父亲
} HuffmanNode, *HuffmanTree;

/* 存放字符及其编码结果的结构体 */
typedef struct Dic {
    HuffmanTree charNode[128]; // 字符结点数组，起到字典的作用(只适用于ASCII码表)
} Dic;

/* 堆的结构 */
typedef struct HeapStruct {
    HuffmanTree *elem; // 存放堆元素(Huffman结点)的数组
    int size;          // 当前元素个数
    int capacity;      // 存储容量
} HeapStruct, *Heap;

HuffmanTree createHuffmanNode();              // 生成Huffman树结点
HuffmanTree createHuffmanTree();              // 构造Huffman树
Heap createHeap(int maxsize);                 // 创建容量为maxsize的堆
void traverseHeap(Heap H);                    // 堆的遍历
void insertMinHeap(Heap H, HuffmanTree data); // 最小堆的插入
HuffmanTree deleteMinHeap(Heap H);            // 最小堆的删除

int countChFrequency(FILE *fp);           // 统计字符出现频率
void genHuffmanCode(HuffmanTree root);    // 生成Huffman编码
void encoded(FILE *source, FILE *output); // 编码
void decoded(FILE *source, FILE *output); // 解码

Dic dic; // 字典，全局变量，用于编码压缩

int main() {
    float begintime, endtime;
    // 编码
    FILE *originalText = fopen("./original_text.txt", "rb");     // 源文件
    FILE *compressedText = fopen("./compressed_text.txt", "wb"); // 压缩后的二进制文件
    if (!(originalText && compressedText))
        printf("Failed to open files!\n ");
    else {
        begintime = clock(); //计时开始
        encoded(originalText, compressedText);
        endtime = clock(); //计时结束
        printf("Program time consuming: %fs\n\n", (endtime - begintime) / ((double) CLOCKS_PER_SEC));
    }
    fclose(originalText);
    fclose(compressedText);

    // 解码
    FILE *binText = fopen("./compressed_text.txt", "rb");  // 压缩后的二进制文件
    FILE *decodedText = fopen("./decoded_text.txt", "wb"); // 解码后的文件
    if (!(binText && decodedText))
        printf("Failed to open files!\n");
    else {
        begintime = clock(); //计时开始
        decoded(binText, decodedText);
        endtime = clock(); //计时结束
        printf("Program time consuming: %fs\n\n", (endtime - begintime) / ((double) CLOCKS_PER_SEC));
    }
    fclose(binText);
    fclose(decodedText);

    system("pause");
    return 0;
}

/*---------------------------------------- 编码 ----------------------------------------*/
void encoded(FILE *source, FILE *output) {
    int i, j;
    int types = 0;
    int textLength = countChFrequency(source); // 计算字符频率
    HuffmanTree root = createHuffmanTree();    // 由字符频率构造Huffman树
    genHuffmanCode(root);                      // 编码

    // 输出编码结果
    printf("   *------------> Huffman Code Table <-----------*\n");
    printf("    ____________________________________________\n      charcater |  frequency  |     code\n");
    printf("    ____________|_____________|_________________\n");
    for (i = 0; i < 128; i++)
        if (dic.charNode[i]->count > 0) {
            if (dic.charNode[i]->character == 10) // 换行符
                printf("       \\n\t|%8ld     |   %s\n", dic.charNode[i]->count, dic.charNode[i]->code);
            else if (dic.charNode[i]->character == 0) // 结束符
                printf("       \\0\t|%8ld     |   %s\n", dic.charNode[i]->count, dic.charNode[i]->code);
            else if (dic.charNode[i]->character == 9) // 制表符
                printf("       \\t\t|%8ld     |   %s\n", dic.charNode[i]->count, dic.charNode[i]->code);
            else if (dic.charNode[i]->character == 13) // 回车
                printf("       \\r\t|%8ld     |   %s\n", dic.charNode[i]->count, dic.charNode[i]->code);
            else if (dic.charNode[i]->character == 32) // 空格
                printf("     space      |%8ld     |   %s\n", dic.charNode[i]->count, dic.charNode[i]->code);
            else
                printf("       %c\t|%8ld     |   %s\n", dic.charNode[i]->character, dic.charNode[i]->count,
                       dic.charNode[i]->code);
            types++;
        }
    printf("   _____________|_____________|_________________\n\n");

    // 压缩文件准备操作
    fseek(source, 0, SEEK_SET);  // 找到源文件开头
    fseek(output, 12, SEEK_SET); // 找到输出文件的12个字节后的位置，前12字节存相关信息
    int lenCompressedFile = 12;  // 压缩文件的长度，单位字节
    char tempCode[MAXBIT] = {0}; // 临时存放字符编码
    int lenTempCode = 0;         // 暂存的字符编码长度

    // 写入文本
    char ch = fgetc(source);
    while (ch != EOF) {
        strcat(tempCode, dic.charNode[ch]->code); // 将字符的编码追加给tempCode暂存
        lenTempCode = strlen(tempCode);
        ch = 0;                  //二进制为00000000，作为写入文本的二进制编码的临时容器
        while (lenTempCode >= 8) // 暂存编码位数大于8时，执行写入操作
        {
            for (i = 0; i < 8; i++) // 八位二进制数写入文件一次
            {
                if (tempCode[i] == '1') // ch的二进制数左移并加1
                {
                    ch = ch << 1;
                    ch = ch + 1;
                } else
                    ch = ch << 1; // ch的二进制数左移
            }
            fwrite(&ch, sizeof(char), 1, output);
            lenCompressedFile++;
            strcpy(tempCode, tempCode + 8); // temoCode的值重新覆盖
            lenTempCode = strlen(tempCode);
        }
        ch = fgetc(source);
    }
    if (lenTempCode > 0) // 若最后不满8位，则补0
    {
        ch = 0;
        strcat(tempCode, "00000000");
        for (i = 0; i < 8; i++) {
            if (tempCode[i] == '1') // ch的二进制数左移并加1
            {
                ch = ch << 1;
                ch = ch + 1;
            } else
                ch = ch << 1; // ch的二进制数左移
        }
        fwrite(&ch, sizeof(char), 1, output); // 将最后一个字符写入
        lenCompressedFile++;
    }

    // 写入源文件大小、压缩后文件大小和字符种类数(bytes)
    fseek(output, 0, SEEK_SET);                         // 输出文件指针指向开头，写入参数
    fwrite(&textLength, sizeof(int), 1, output);        // 写入源文件大小
    fwrite(&lenCompressedFile, sizeof(int), 1, output); // 写入压缩后文件大小(包括12字节的文本信息及正文，不包括字典)
    fwrite(&types, sizeof(int), 1, output);             // 写入字符种类数

    // 写入字典
    fseek(output, lenCompressedFile, SEEK_SET); // 找到output的末尾
    HuffmanTree tempNode;
    char codeLenBit;
    for (i = 0; i < 128; i++) {
        if (dic.charNode[i]->count > 0) {
            tempNode = dic.charNode[i];
            lenTempCode = strlen(tempNode->code);
            fwrite(&(tempNode->character), 1, 1, output); // 写入字符ASCII码
            lenCompressedFile++;
            codeLenBit = lenTempCode;
            fwrite(&codeLenBit, 1, 1, output); // 写入字符编码的长度-1个字节就够了
            lenCompressedFile++;

            while (lenTempCode % 8 != 0) // 当编码不够整数字节时，补0
            {
                strcat(tempNode->code, "0");
                lenTempCode = strlen(tempNode->code);
            }

            while (tempNode->code[0] != 0) {
                ch = 0;
                for (j = 0; j < 8; j++) {
                    if (tempNode->code[j] == '1') {
                        ch = ch << 1;
                        ch += 1;
                    } else
                        ch = ch << 1;
                }
                strcpy(tempNode->code, tempNode->code + 8);
                fwrite(&ch, 1, 1, output); // 将所得的编码信息写入文件
                lenCompressedFile++;
            }
        }
    }
    printf("\n>>> Original File Information\n");
    printf("- filename: original_text.txt\n- file length: %ld bytes\n", textLength);
    printf("\n>>> Compressed File Information\n");
    printf("- filename: decoded_text.txt\n- file length: %ld bytes\n", lenCompressedFile);
    printf("\nThe compress has finished! Compression ratio: %.2f%%\n",
           (float) lenCompressedFile / (float) textLength * 100);
}

/*---------------------------------------- 解码 ----------------------------------------*/
void decoded(FILE *source, FILE *output) {
    int i, j, k;
    int temp;
    unsigned char ch;
    int writeCount = 0;                 // 写入字符数的统计
    char tempCode[MAXBIT] = {0};        // 临时存放字符编码
    char codeToBeDecoded[MAXBIT] = {0}; // 存放待译码的二进制序列(1个char)
    Dic dic_decode;                     // 解码用字典

    // 对dic进行初始化
    for (i = 0; i < 128; i++) {
        dic_decode.charNode[i] = (HuffmanTree) malloc(sizeof(HuffmanNode)); // 申请空间
        dic_decode.charNode[i]->character = 0;                             // 此时下标无含义
        dic_decode.charNode[i]->count = 0;                                 // 此时用于存放编码长度 strlen(code)
        dic_decode.charNode[i]->lchild = NULL;
        dic_decode.charNode[i]->rchild = NULL;
        dic_decode.charNode[i]->parent = NULL;
        dic_decode.charNode[i]->code[0] = 0;
    }

    // 读取相关文本信息
    int textLen, binLen, types, biFileLen, codeLen, byteNum;
    fseek(source, 0, SEEK_END);
    biFileLen = ftell(source); // 二进制文件总大小
    fseek(source, 0, SEEK_SET);
    fread(&textLen, sizeof(int), 1, source); // 源文本大小
    fread(&binLen, sizeof(int), 1, source);  // 压缩后的文件大小(不含字典)
    fread(&types, sizeof(int), 1, source);   // 字符种类数

    // 读取字典并转换成二进制码(char数组)
    fseek(source, binLen, SEEK_SET);
    for (i = 0; i < types; i++) {

        fread(&dic_decode.charNode[i]->character, 1, 1, source); // 读取字符(ASCII码)
        fread(&ch, 1, 1, source);
        dic_decode.charNode[i]->count = (long) ch;  // 读取字符编码长度 strlen(code)
        if (dic_decode.charNode[i]->count % 8 > 0) // 当前字符的编码占了几个字节
            byteNum = dic_decode.charNode[i]->count / 8 + 1;
        else
            byteNum = dic_decode.charNode[i]->count / 8;

        for (j = 0; j < byteNum; j++) {
            fread(&ch, 1, 1, source); // 此步读取的是单个字节对应的ASCII码
            temp = (int) ch;
            _itoa(temp, tempCode, 2); // 将ch的值转为二进制字符串存入tempCode
            temp = strlen(tempCode);
            for (k = 8; k > temp; k--) {
                strcat(dic_decode.charNode[i]->code, "0"); //位数不足，执行补零操作
            }
            strcat(dic_decode.charNode[i]->code, tempCode);
        }
        dic_decode.charNode[i]->code[dic_decode.charNode[i]->count] = 0; // 放上/0
    }

    // 按Huffman码长度从小到大排序，便于译码时查找 - 冒泡
    HuffmanTree tmp;
    for (i = 0; i < types; i++) {
        for (j = 0; j < types - i - 1; j++) {
            if (strlen(dic_decode.charNode[j]->code) > strlen(dic_decode.charNode[j + 1]->code)) {
                tmp = dic_decode.charNode[j];
                dic_decode.charNode[j] = dic_decode.charNode[j + 1];
                dic_decode.charNode[j + 1] = tmp;
            }
        }
    }

    int maxLen = strlen(dic_decode.charNode[types - 1]->code); // 最长编码数
    fseek(source, 12, SEEK_SET);                               // 指向正文开头
    tempCode[0] = 0;
    while (1) {
        while (strlen(codeToBeDecoded) < maxLen) // 确保一定找到一个字符
        {
            fread(&ch, 1, 1, source);
            temp = (int) ch;
            _itoa(temp, tempCode, 2); // 将ch的值转为二进制字符串存入tempCode
            temp = strlen(tempCode);
            for (k = 8; k > temp; k--) // 转十进制再转二进制会丢掉0，进行补0操作
                strcat(codeToBeDecoded, "0");
            strcat(codeToBeDecoded, tempCode);
        }
        // Huffman码与字符的匹配
        for (i = 0; i < types; i++) {
            if (memcmp(dic_decode.charNode[i]->code, codeToBeDecoded, dic_decode.charNode[i]->count) == 0)
                break;
        }
        strcpy(codeToBeDecoded, codeToBeDecoded + dic_decode.charNode[i]->count); // 将已经解译的编码覆盖
        ch = dic_decode.charNode[i]->character;
        fwrite(&ch, 1, 1, output); //写入解码的文件
        writeCount++;
        if (writeCount == textLen) // 限定写入只写到正文内容，再往后存储的就是字典
            break;
    }
    printf("The decoded has finish!\n");
}

/*---------------------------------------- 编码所需操作 ----------------------------------------*/
/* 统计字符频率 */
int countChFrequency(FILE *fp) {
    int i;
    int length = 0; // 统计文本的长度

    // 对dic进行初始化
    for (i = 0; i < 128; i++) {
        dic.charNode[i] = (HuffmanTree) malloc(sizeof(HuffmanNode)); // 申请空间
        dic.charNode[i]->character = i;                             // 将下标与ASCII码对应
        dic.charNode[i]->count = 0;
        dic.charNode[i]->lchild = NULL;
        dic.charNode[i]->rchild = NULL;
        dic.charNode[i]->parent = NULL;
    }
    // 对字符进行统计
    char ch = fgetc(fp);
    while (ch != EOF) {
        dic.charNode[(int) ch]->count++;
        ch = fgetc(fp);
        length++;
    }
    return length;
}

/* 生成Huffman编码 */
void genHuffmanCode(HuffmanTree root) {
    int i, j;
    int count = 0;
    char tempCode[256]; // 临时存放字符编码
    HuffmanTree pMove = NULL;

    // 生成Huffman编码
    for (i = 0; i < 128; i++) {
        if (dic.charNode[i]->count > 0) // 对于出现过的字符，即Huffman树的叶子结点
        {
            pMove = dic.charNode[i];
            // 从叶子逆序到根，将编码逆序存放在tempCode中
            while (pMove->parent) {
                if (pMove->parent->lchild == pMove)
                    tempCode[count] = '0'; // 左子树为0
                else
                    tempCode[count] = '1'; // 右子树为1
                count++;
                pMove = pMove->parent;
            }
            // 将tempCode编码逆序存放在字符结点中
            for (j = 0; j < count; j++)
                dic.charNode[i]->code[j] = tempCode[count - j - 1];
            dic.charNode[i]->code[j] = '\0';
            count = 0;
        }
    }
}

/* 生成Huffman树结点 */
HuffmanTree createHuffmanNode() {
    HuffmanTree node = (HuffmanTree) malloc(sizeof(HuffmanNode));
    node->character = 0;
    node->count = 0;
    node->lchild = NULL;
    node->rchild = NULL;
    node->parent = NULL;
    return node;
}

/* 构造Huffman树 */
HuffmanTree createHuffmanTree() {
    int i;

    // 由字典构造最小堆
    Heap H = createHeap(MAXSIZE);
    for (i = 0; i < 128; i++) {
        if (dic.charNode[i]->count > 0) {
            insertMinHeap(H, dic.charNode[i]);
        }
    }

    // 构造Huffman树
    while (H->size > 1) {
        // 创建新结点，值为两最小结点的和
        HuffmanTree newNode = createHuffmanNode();
        HuffmanTree left = deleteMinHeap(H);
        HuffmanTree right = deleteMinHeap(H);
        newNode->count = left->count + right->count;
        newNode->lchild = left;
        newNode->rchild = right;
        left->parent = newNode;
        right->parent = newNode;

        // 将新结点插入堆中
        insertMinHeap(H, newNode);
    }
    HuffmanTree root = deleteMinHeap(H);
    return root;
}

/* 创建容量为maxsize的堆 */
Heap createHeap(int maxsize) {
    Heap H = (Heap) malloc(sizeof(struct HeapStruct));
    H->elem = (HuffmanTree *) malloc(sizeof(HuffmanTree) * (maxsize + 1)); // 从下标为1存放堆元素
    H->size = 0;
    H->capacity = maxsize;
    return H;
}

/* 堆的遍历 */
void traverseHeap(Heap H) {
    int i;

    if (H->size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    for (i = 1; i <= H->size; i++) {
        printf("%d ", H->elem[i]->count);
    }
    printf("\n");
}

/* 最小堆的插入 */
void insertMinHeap(Heap H, HuffmanTree data) {
    int i;

    if (H->size == H->capacity) // 堆满
    {
        printf("Min heap is full!\n");
        return;
    }

    i = H->size + 1; // i指向插入元素后堆中最后一个元素的位置
    H->size++;

    while (1) {
        if (i <= 1) // 如果堆为空，直接退出去，插入元素
            break;
        if (!(H->elem[i / 2]->count > data->count)) // 已经找到位置
            break;
        H->elem[i] = H->elem[i / 2]; // 如果插入位置的父结点大于其值，则将其插入位置与父结点交换
        i /= 2;
    }
    H->elem[i] = data; // 将data插入
}

/* 最小堆的删除 */
HuffmanTree deleteMinHeap(Heap H) {
    int parent, child;
    HuffmanTree min, temp;

    if (H->size == 0) {
        printf("Heap is empty!\n");
        return NULL;
    }

    min = H->elem[1]; // 取出最小值-根节点

    // 将堆最后一个元素作为树根，然后调整树的结构
    temp = H->elem[H->size]; // 存放堆的最后一个元素
    H->size--;
    for (parent = 1; parent * 2 <= H->size; parent = child) {
        child = parent * 2; // 先指向左子结点
        // child指向左右子结点的较小者
        if ((child != H->size) && (H->elem[child]->count > H->elem[child + 1]->count))
            child++;

        if (temp->count <= H->elem[child]->count) //找到位置了
            break;
        else // 将temp移动到下一层
            H->elem[parent] = H->elem[child];
    }
    H->elem[parent] = temp;
    return min;
}