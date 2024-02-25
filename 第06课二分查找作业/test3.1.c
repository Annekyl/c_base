#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVEL 6 // 定义跳表的最大层数

// 跳表节点结构体
typedef struct skip_node {
    int key; // 节点的键
    int value; // 节点的值
    struct skip_node *forward[]; // 指向下一个节点的指针数组（大小为1）
} skip_node;

// 跳表结构体
typedef struct skip_list {
    int level; // 跳表的当前层数
    skip_node *header; // 指向头节点的指针
} skip_list;

// 创建新节点
skip_node *createNode(int key, int value, int level) {
    // 分配内存空间
    skip_node *newNode = (skip_node *)malloc(sizeof(skip_node) + level * sizeof(skip_node*));
    newNode->key = key;
    newNode->value = value;
    return newNode;
}

// 创建跳表
skip_list *createSkipList() {
    // 分配内存空间
    skip_list *list = (skip_list *)malloc(sizeof(skip_list));
    list->level = 0; // 初始化层数为0
    // 创建头节点并将其指针数组初始化为NULL
    list->header = createNode(-1, -1, MAX_LEVEL);
    for (int i = 0; i < MAX_LEVEL; i++) {
        list->header->forward[i] = NULL;
    }
    return list;
}

// 生成随机层数
int randomLevel() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)
        level++; // 随机生成层数
    return level;
}

// 插入节点
void insert(skip_list *list, int key, int value) {
    skip_node *update[MAX_LEVEL]; // 用于存储每一层需要更新的节点
    skip_node *current = list->header; // 从头节点开始查找
    for (int i = list->level - 1; i >= 0; i--) { // 从高层到低层遍历跳表
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // 找到当前层中第一个比要插入的节点的键大的节点
            current = current->forward[i];
        }
        update[i] = current; // 记录需要更新的节点
    }
    current = current->forward[0]; // 下降到底层
    if (current == NULL || current->key != key) { // 如果当前节点为空或者键不等于要插入的键
        int newLevel = randomLevel(); // 随机生成新节点的层数
        if (newLevel > list->level) { // 如果新节点的层数大于当前跳表的层数
            for (int i = list->level; i < newLevel; i++)
                update[i] = list->header; // 将所有需要更新的节点设置为头节点
            list->level = newLevel; // 更新跳表的层数
        }
        current = createNode(key, value, newLevel); // 创建新节点
        for (int i = 0; i < newLevel; i++) {
            current->forward[i] = update[i]->forward[i]; // 将新节点的指针数组设置为需要更新的节点的指针数组
            update[i]->forward[i] = current; // 将需要更新的节点的指针数组设置为新节点
        }
    }
}

// 查找节点
skip_node *search(skip_list *list, int key) {
    skip_node *current = list->header; // 从头节点开始查找
    for (int i = list->level - 1; i >= 0; i--) { // 从高层到低层遍历跳表
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // 找到当前层中第一个比要查找的键大的节点
            current = current->forward[i];
        }
    }
    current = current->forward[0]; // 下降到底层
    if (current != NULL && current->key == key)
        return current; // 如果找到了节点就返回该节点
    return NULL; // 没有找到就返回NULL
}

// 删除节点
void deleteNode(skip_list *list, int key) {
    skip_node *update[MAX_LEVEL]; // 用于存储每一层需要更新的节点
    skip_node *current = list->header; // 从头节点开始查找
    for (int i = list->level - 1; i >= 0; i--) { // 从高层到低层遍历跳表
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // 找到当前层中第一个比要删除的键大的节点
            current = current->forward[i];
        }
        update[i] = current; // 记录需要更新的节点
    }
    current = current->forward[0]; // 下降到底层
    if (current != NULL && current->key == key) { // 如果找到了要删除的节点
        for (int i = 0; i < list->level; i++) {
            if (update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i]; // 将需要更新的节点的指针数组设置为要删除节点的指针数组
        }
        free(current); // 释放要删除的节点
        while (list->level > 1 && list->header->forward[list->level - 1] == NULL) { // 如果跳表的最高层没有节点，则降低跳表的层数
            list->level--;
        }
    }
}

// 打印跳表
void printSkipList(skip_list *list) {
    printf("Skip List:\n");
    for (int i = list->level - 1; i >= 0; i--) { // 从高层到低层遍历跳表
        skip_node *node = list->header->forward[i]; // 从头节点开始
        printf("Level %d: ", i);
        while (node != NULL) { // 遍历当前层的所有节点
            printf("%d:%d ", node->key, node->value);
            node = node->forward[i];
        }
        printf("\n");
    }
}

// 主函数
int main() {
    skip_list *list = createSkipList(); // 创建跳表

    insert(list, 3, 30); // 插入节点
    insert(list, 6, 60);
    insert(list, 9, 90);
    printSkipList(list); // 打印跳表

    skip_node *node = search(list, 6); // 查找节点
    if (node != NULL) {
        printf("Found node with key 6 and value %d\n", node->value);
    } else {
        printf("Node with key 6 not found\n");
    }

    deleteNode(list, 6); // 删除节点
    printSkipList(list); // 打印跳表

    return 0;
}