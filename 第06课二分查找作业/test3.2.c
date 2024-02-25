#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEVEL 6 // ��Ծ���������

// ��Ծ��ڵ�ṹ
typedef struct skipListNode {
    int key; // ��ֵ
    struct skipListNode **forward; // ָ��ǰ���ڵ��ָ������
} skipListNode;

// ��Ծ��ṹ
typedef struct skipList {
    int level; // ��ǰ��Ծ�����߲���
    struct skipListNode *header; // ��Ծ��ͷ�ڵ�ָ��
} skipList;

// �����½ڵ�
skipListNode* createNode(int key, int level) {
    skipListNode* newNode = (skipListNode*)malloc(sizeof(skipListNode));
    newNode->key = key;
    newNode->forward = (skipListNode**)malloc(sizeof(skipListNode*) * (level + 1)); // ������Ծ������������̬����ָ������ռ�
    return newNode;
}

// ������Ծ��
skipList* createSkipList() {
    skipList* newSkipList = (skipList*)malloc(sizeof(skipList));
    newSkipList->level = 0;
    newSkipList->header = createNode(-1, MAX_LEVEL); // ͷ�ڵ��ֵΪ -1�����ڸ�������
    for (int i = 0; i <= MAX_LEVEL; i++) {
        newSkipList->header->forward[i] = NULL; // ��ʼʱ����ǰ���ڵ�ָ��Ϊ��
    }
    return newSkipList;
}

// �����������
int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) // ������ɲ�������֤����������������
        level++;
    return level;
}

// ����ڵ㵽��Ծ����
void insert(skipList* list, int key) {
    skipListNode* update[MAX_LEVEL + 1]; // ���ڼ�¼��ÿ����Ҫ�����½ڵ��ǰһ���ڵ�ָ��
    skipListNode* current = list->header; // ��ͷ�ڵ㿪ʼ����

    for (int i = list->level; i >= 0; i--) { // ����߲㿪ʼ���²���
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // �ڵ�ǰ�����ҵ����һ����ֵС��Ҫ����ļ�ֵ�Ľڵ�
            current = current->forward[i];
        }
        update[i] = current; // ��¼��ǰ����Ҫ�����½ڵ��ǰһ���ڵ�ָ��
    }

    current = current->forward[0]; // �л����� 0 �㣬����ײ�Ľڵ�

    if (current == NULL || current->key != key) { // ����ҵ��Ľڵ�Ϊ�ջ��߼�ֵ������Ҫ����ļ�ֵ
        int newLevel = randomLevel(); // ��������½ڵ�Ĳ���

        if (newLevel > list->level) { // ����½ڵ�Ĳ������ڵ�ǰ��Ծ�����߲�������Ҫ������߲���
            for (int i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header; // �����²��е�ǰһ���ڵ�ָ�붼ָ��ͷ�ڵ�
            }
            list->level = newLevel; // ������Ծ�����߲���
        }

        skipListNode* newNode = createNode(key, newLevel); // �����½ڵ�

        for (int i = 0; i <= newLevel; i++) { // ���½ڵ���뵽ÿһ����
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// ����Ծ���в���ָ���ļ�ֵ
skipListNode* search(skipList* list, int key) {
    skipListNode* current = list->header;

    for (int i = list->level; i >= 0; i--) { // ����߲㿪ʼ���²���
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // �ڵ�ǰ�����ҵ����һ����ֵС��Ҫ���ҵļ�ֵ�Ľڵ�
            current = current->forward[i];
        }
    }

    current = current->forward[0]; // �л����� 0 �㣬����ײ�Ľڵ�

    if (current != NULL && current->key == key) { // ����ҵ��Ľڵ㲻Ϊ���Ҽ�ֵ����Ҫ���ҵļ�ֵ
        return current; // �����ҵ��Ľڵ�ָ��
    } else {
        return NULL; // ���򷵻ؿ�ָ��
    }
}

// ��ӡ��Ծ��
void printSkipList(skipList* list) {
    printf("Skip List:\n");
    for (int i = list->level; i >= 0; i--) { // ����߲㿪ʼ���´�ӡ
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

// ��ȡ�ļ���������ѧ�����ݵĶ�ά����
int** readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�ļ���ʧ��: %s\n", filename);
        return NULL;
    }

    // ͳ���ļ��е�ѧ������
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        studentCount++;
    }

    // �����洢ѧ�����ݵĶ�ά����
    int** students = (int**)malloc(sizeof(int*) * studentCount);
    for (int i = 0; i < studentCount; i++) {
        students[i] = (int*)malloc(sizeof(int) * 3);
    }

    // ��ȡ�ļ��е�ѧ������
    rewind(file); // ���ļ�ָ������ָ���ļ���ͷ
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " ");
        int count = 0;
        while (token != NULL) {
            if(count==0||count==4||count==5||count==6||count==7) {
                students[index][count] = atoi(token);
            } else{
                students[index][count] = *token;
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
    // ������Ծ��
    skipList* list = createSkipList();

    // ���ļ��ж�ȡѧ������
    int** students = readFile("score.txt");
    if (students == NULL) {
        return 1;
    }

    // ����ѧ�����ݵ���Ծ����
    for (int i = 0; i < studentCount; i++) {
        int key = students[i][0]; // ʹ��ѧ��ID��Ϊ��ֵ
        insert(list, key);
    }

    // ��ӡ��Ծ��
    printSkipList(list);

    // �ͷ��ڴ�
    for (int i = 0; i < studentCount; i++) {
        free(students[i]);
    }
    free(students);
    free(list->header->forward);
    free(list->header);
    free(list);

    return 0;
}
