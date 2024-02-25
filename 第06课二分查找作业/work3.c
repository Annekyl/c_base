#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MAX_LEVEL 6 // ��Ծ���������
#define MAX_NAME_LENGTH 50  // ѧ����������
#define MAX_GENDER_LENGTH 50  // ѧ����������
#define MAX_CLASS_LENGTH 50  // ѧ����������

// ѧ���ṹ��
typedef struct {
    int num;  // ѧ��
    char name[MAX_NAME_LENGTH];  // ����
    char gender[MAX_GENDER_LENGTH];  // �Ա�
    char class[MAX_CLASS_LENGTH];  // �༶
    int grade1;
    int grade2;
    int grade3;
    int average_grade;
} Student;

// ��Ծ��ڵ�ṹ
typedef struct skipListNode {
    int key; // ��ֵ
    Student *student;
    struct skipListNode **forward; // ָ��ǰ���ڵ��ָ������
} skipListNode;

// ��Ծ��ṹ
typedef struct skipList {
    int level; // ��ǰ��Ծ�����߲���
    struct skipListNode *header; // ��Ծ��ͷ�ڵ�ָ��
} skipList;


// �����½ڵ�
skipListNode *createNode(int key, int level, Student *student) {
    skipListNode *newNode = (skipListNode *) malloc(sizeof(skipListNode));
    if (newNode == NULL) {
        printf("�ڴ����ʧ�ܣ�");

    }
    newNode->key = key;
    newNode->student = student;

    newNode->forward = (skipListNode **) malloc(sizeof(skipListNode *) * (level + 1)); // ������Ծ������������̬����ָ������ռ�
    return newNode;
}

// ������Ծ��
skipList *createSkipList() {
    skipList *newSkipList = (skipList *) malloc(sizeof(skipList));
    newSkipList->level = 0;
    newSkipList->header = createNode(-1, MAX_LEVEL, NULL); // ͷ�ڵ��ֵΪ -1�����ڸ�������
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

// ����ѧ�Ż�ƽ���ɼ�����ڵ�
void insert(skipList *list, int key, Student *student) {
    skipListNode *update[MAX_LEVEL + 1]; // ���ڼ�¼��ÿ����Ҫ�����½ڵ��ǰһ���ڵ�ָ�룬���������飬ֻ���������д�ŵ�Ԫ�ض��ǵ�ַ
    skipListNode *current = list->header; // ��ͷ�ڵ㿪ʼ����

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

        skipListNode *newNode = createNode(key, newLevel, student); // �����½ڵ�

        for (int i = 0; i <= newLevel; i++) { // ���½ڵ���뵽ÿһ����
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// ������������ڵ�
void insertByName(skipList *list, char name[], Student *student) {
    skipListNode *update[MAX_LEVEL];
    skipListNode *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->student->name, name) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // ����ײ����ڵ�
    current = current->forward[0];

    if (current == NULL || strcmp(current->student->name, name) != 0) {
        int newLevel = randomLevel(); // ��������½ڵ�Ĳ���

        if (newLevel > list->level) { // ����½ڵ�Ĳ������ڵ�ǰ��Ծ�����߲�������Ҫ������߲���
            for (int i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header; // �����²��е�ǰһ���ڵ�ָ�붼ָ��ͷ�ڵ�
            }
            list->level = newLevel; // ������Ծ�����߲���
        }

        skipListNode *newNode = createNode(1, newLevel, student); // �����½ڵ�

        for (int i = 0; i <= newLevel; i++) { // ���½ڵ���뵽ÿһ����
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// ���ѧ����Ϣ
void printStudentInfo(Student *student) {
    printf("ѧ��\t\t����\t�Ա�\t�༶\t\t����ת��\t�����ת��\t��ֵ����߼�����\tƽ���ɼ�\n");
    printf("%d\t%s\t%s\t%s\t%d\t\t%d\t\t%d\t\t\t%d\n",
           student->num,
           student->name, student->gender, student->class,
           student->grade1, student->grade2, student->grade3,
           student->average_grade);
}


// ����ѧ�Ŷ�ȡ����
void ReadScoreByNum(skipList *list) {
    FILE *file;  // �ļ�ָ��

    // ��ԭ�ɼ��ļ�
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�: %s\n", "score.txt");
        exit(1);
    }

    // ��ѧ�����ݴ�������
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        // ���������ͳɼ�
        Student *student = (Student *) malloc(sizeof(Student));
        int num;
        char name[MAX_NAME_LENGTH];
        char gender[10];
        char class[50];
        int grade1;
        int grade2;
        int grade3;
        sscanf(line, "%d %s %s %s %d %d %d",
               &num, name, gender, class, &grade1, &grade2, &grade3);
        student->num = num;
        strcpy(student->name, name);
        strcpy(student->gender, gender);
        strcpy(student->class, class);
        student->grade1 = grade1;
        student->grade2 = grade2;
        student->grade3 = grade3;
        student->average_grade = (grade1 + grade2 + grade3) / 3;
        insert(list, num, student);
    }
}

// ����������ȡѧ������
void ReadScoreByName(skipList *list) {
    FILE *file;  // �ļ�ָ��

    // ��ԭ�ɼ��ļ�
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�: %s\n", "score.txt");
        exit(1);
    }

    // ��ѧ�����ݴ�������
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        // ���������ͳɼ�
        Student *student = (Student *) malloc(sizeof(Student));
        int num;
        char name[MAX_NAME_LENGTH];
        char gender[10];
        char class[50];
        int grade1;
        int grade2;
        int grade3;
        sscanf(line, "%d %s %s %s %d %d %d",
               &num, name, gender, class, &grade1, &grade2, &grade3);
        student->num = num;
        strcpy(student->name, name);
        strcpy(student->gender, gender);
        strcpy(student->class, class);
        student->grade1 = grade1;
        student->grade2 = grade2;
        student->grade3 = grade3;
        student->average_grade = (grade1 + grade2 + grade3) / 3;
        insertByName(list, name, student);
    }
}

// ����ƽ���ɼ���ȡ����
void ReadScoreByAverageGrade(skipList *list) {
    FILE *file;  // �ļ�ָ��

    // ��ԭ�ɼ��ļ�
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�: %s\n", "score.txt");
        exit(1);
    }

    // ��ѧ�����ݴ�������
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        // ���������ͳɼ�
        Student *student = (Student *) malloc(sizeof(Student));
        int num;
        char name[MAX_NAME_LENGTH];
        char gender[10];
        char class[50];
        int grade1;
        int grade2;
        int grade3;
        sscanf(line, "%d %s %s %s %d %d %d",
               &num, name, gender, class, &grade1, &grade2, &grade3);
        student->num = num;
        strcpy(student->name, name);
        strcpy(student->gender, gender);
        strcpy(student->class, class);
        student->grade1 = grade1;
        student->grade2 = grade2;
        student->grade3 = grade3;
        student->average_grade = (grade1 + grade2 + grade3) / 3;
        insert(list, (grade1 + grade2 + grade3) / 3, student);
    }
}

// ����ѧ�Ų�ѯ����
skipListNode *search(skipList *list, int key) {
    skipListNode *current = list->header;

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

// ����������ѯ����
skipListNode *searchByName(skipList *list, const char *name) {
    skipListNode *current = list->header;

    for (int i = list->level; i >= 0; i--) { // ����߲㿪ʼ���²���
        while (current->forward[i] != NULL && strcmp(current->student->name, name) < 0) { // �ڵ�ǰ�����ҵ����һ����ֵС��Ҫ���ҵļ�ֵ�Ľڵ�
            current = current->forward[i];
        }
    }

    current = current->forward[0]; // �л����� 0 �㣬����ײ�Ľڵ�

    if (current != NULL && strcmp(current->student->name, name) == 0) { // ����ҵ��Ľڵ㲻Ϊ���Ҽ�ֵ����Ҫ���ҵļ�ֵ
        return current;
    } else {
        return NULL;
    }
}

// ����ƽ���ɼ���ѯ����
void searchAndPrintByAverageGrade(skipList *list, int key) {
    skipListNode *current = list->header;

    for (int i = list->level; i >= 0; i--) { // ����߲㿪ʼ���²���
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // �ڵ�ǰ�����ҵ����һ����ֵС��Ҫ���ҵļ�ֵ�Ľڵ�
            current = current->forward[i];
        }
    }

    current = current->forward[0]; // �л����� 0 �㣬����ײ�Ľڵ�

    while (current != NULL && current->key == key) { // ����ҵ��Ľڵ㲻Ϊ���Ҽ�ֵ����Ҫ���ҵļ�ֵ
        printStudentInfo(current->student);
        current = current->forward[0];
    }
}


// ������
int main() {
    // ������Ծ��
    skipList *list = createSkipList();
    while (1) {
        int select;
        printf("��ѡ���ѯ��ʽ:1.ѧ��2.����3.ƽ���ɼ�(�˳�������0)\n");
        scanf("%d", &select);
        if (select == 0) {
            exit(0);
        } else if (select == 1) {
            ReadScoreByNum(list);
            int key;
            printf("������Ҫ��ѯ��ѧ��ѧ��");
            scanf("%d", &key);
            skipListNode *result = search(list, key);
            if (result != NULL) {
                printStudentInfo(result->student);
            } else {
                printf("δ��ѯ�����ѧ����Ϣ\n");
            }
        } else if (select == 2) {
            ReadScoreByName(list);
            char name[MAX_NAME_LENGTH];
            printf("������ѧ������");
            scanf("%s", name);
            skipListNode *result = searchByName(list, name);
            if (result != NULL) {
                printStudentInfo(result->student);
            } else {
                printf("δ��ѯ�����ѧ����Ϣ\n");
            }
        } else if (select == 3) {
            ReadScoreByAverageGrade(list);
            int key;
            printf("������Ҫ��ѯ��ƽ���ɼ�");
            scanf("%d", &key);
            searchAndPrintByAverageGrade(list, key);
        } else {
            printf("�������\n");
        }
    }


}