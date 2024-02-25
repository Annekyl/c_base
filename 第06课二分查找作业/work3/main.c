#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEVEL 6 // 跳跃表的最大层数

// 跳跃表节点结构
typedef struct skipListNode {
    int key; // 键值
    struct skipListNode **forward; // 指向前进节点的指针数组
} skipListNode;

// 跳跃表结构
typedef struct skipList {
    int level; // 当前跳跃表的最高层数
    struct skipListNode *header; // 跳跃表头节点指针
} skipList;

// 创建新节点
skipListNode* createNode(int key, int level) {
    skipListNode* newNode = (skipListNode*)malloc(sizeof(skipListNode));
    newNode->key = key;
    newNode->forward = (skipListNode**)malloc(sizeof(skipListNode*) * (level + 1)); // 根据跳跃表的随机层数动态分配指针数组空间
    return newNode;
}

// 创建跳跃表
skipList* createSkipList() {
    skipList* newSkipList = (skipList*)malloc(sizeof(skipList));
    newSkipList->level = 0;
    newSkipList->header = createNode(-1, MAX_LEVEL); // 头节点键值为 -1，用于辅助查找
    for (int i = 0; i <= MAX_LEVEL; i++) {
        newSkipList->header->forward[i] = NULL; // 初始时所有前进节点指针为空
    }
    return newSkipList;
}

// 生成随机层数
int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) // 随机生成层数，保证层数不超过最大层数
        level++;
    return level;
}

// 插入节点到跳跃表中
void insert(skipList* list, int key) {
    skipListNode* update[MAX_LEVEL + 1]; // 用于记录在每层中要插入新节点的前一个节点指针
    skipListNode* current = list->header; // 从头节点开始查找

    for (int i = list->level; i >= 0; i--) { // 从最高层开始向下查找
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // 在当前层中找到最后一个键值小于要插入的键值的节点
            current = current->forward[i];
        }
        update[i] = current; // 记录当前层中要插入新节点的前一个节点指针
    }

    current = current->forward[0]; // 切换到第 0 层，即最底层的节点

    if (current == NULL || current->key != key) { // 如果找到的节点为空或者键值不等于要插入的键值
        int newLevel = randomLevel(); // 随机生成新节点的层数

        if (newLevel > list->level) { // 如果新节点的层数大于当前跳跃表的最高层数，需要更新最高层数
            for (int i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header; // 所有新层中的前一个节点指针都指向头节点
            }
            list->level = newLevel; // 更新跳跃表的最高层数
        }

        skipListNode* newNode = createNode(key, newLevel); // 创建新节点

        for (int i = 0; i <= newLevel; i++) { // 将新节点插入到每一层中
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// 在跳跃表中查找指定的键值
skipListNode* search(skipList* list, int key) {
    skipListNode* current = list->header;

    for (int i = list->level; i >= 0; i--) { // 从最高层开始向下查找
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // 在当前层中找到最后一个键值小于要查找的键值的节点
            current = current->forward[i];
        }
    }

    current = current->forward[0]; // 切换到第 0 层，即最底层的节点

    if (current != NULL && current->key == key) { // 如果找到的节点不为空且键值等于要查找的键值
        return current; // 返回找到的节点指针
    } else {
        return NULL; // 否则返回空指针
    }
}

// 打印跳跃表
void printSkipList(skipList* list) {
    printf("Skip List:\n");
    for (int i = list->level; i >= 0; i--) { // 从最高层开始向下打印
        skipListNode* current = list->header->forward[i];
        printf("Level %d: ", i);
        while (current != NULL) {
            printf("%d ", current->key);
            current = current->forward[i];
        }
        printf("\n");
    }
}

int studentCount = 0;

// 读取文件，并返回学生数据的二维数组
int** readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("文件打开失败: %s\n", filename);
        return NULL;
    }

    // 统计文件中的学生数量
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        studentCount++;
    }

    // 创建存储学生数据的二维数组
    int** students = (int**)malloc(sizeof(int*) * studentCount);
    for (int i = 0; i < studentCount; i++) {
        students[i] = (int*)malloc(sizeof(int) * 3);
    }

    // 读取文件中的学生数据
    rewind(file); // 将文件指针重新指向文件开头
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " ");
        int count = 0;
        while (token != NULL) {
            if(count==0||count==4||count==5||count==6||count==7) {
                students[index][count] = atoi(token);
            }
            token = strtok(NULL, " ");
            count++;
        }
        index++;
    }

    fclose(file);
    return students;
}

int main() {
    // 创建跳跃表
    skipList* list = createSkipList();

    // 从文件中读取学生数据
    int** students = readFile("score.txt");
    if (students == NULL) {
        return 1;
    }

    // 插入学生数据到跳跃表中
    for (int i = 0; i < studentCount; i++) {
        int key = students[i][0]; // 使用学生ID作为键值
        insert(list, key);
    }

    // 打印跳跃表
    printSkipList(list);

    // 释放内存
    for (int i = 0; i < studentCount; i++) {
        free(students[i]);
    }
    free(students);
    free(list->header->forward);
    free(list->header);
    free(list);

    return 0;
}
