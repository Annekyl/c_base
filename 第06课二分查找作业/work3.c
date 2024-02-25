#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MAX_LEVEL 6 // 跳跃表的最大层数
#define MAX_NAME_LENGTH 50  // 学生姓名长度
#define MAX_GENDER_LENGTH 50  // 学生姓名长度
#define MAX_CLASS_LENGTH 50  // 学生姓名长度

// 学生结构体
typedef struct {
    int num;  // 学号
    char name[MAX_NAME_LENGTH];  // 姓名
    char gender[MAX_GENDER_LENGTH];  // 性别。
    char class[MAX_CLASS_LENGTH];  // 班级
    int grade1;
    int grade2;
    int grade3;
    int average_grade;
} Student;

// 跳跃表节点结构
typedef struct skipListNode {
    int key; // 键值
    Student *student;
    struct skipListNode **forward; // 指向前进节点的指针数组
} skipListNode;

// 跳跃表结构
typedef struct skipList {
    int level; // 当前跳跃表的最高层数
    struct skipListNode *header; // 跳跃表头节点指针
} skipList;


// 创建新节点
skipListNode *createNode(int key, int level, Student *student) {
    skipListNode *newNode = (skipListNode *) malloc(sizeof(skipListNode));
    if (newNode == NULL) {
        printf("内存分配失败！");

    }
    newNode->key = key;
    newNode->student = student;

    newNode->forward = (skipListNode **) malloc(sizeof(skipListNode *) * (level + 1)); // 根据跳跃表的随机层数动态分配指针数组空间
    return newNode;
}

// 创建跳跃表
skipList *createSkipList() {
    skipList *newSkipList = (skipList *) malloc(sizeof(skipList));
    newSkipList->level = 0;
    newSkipList->header = createNode(-1, MAX_LEVEL, NULL); // 头节点键值为 -1，用于辅助查找
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

// 根据学号或平均成绩插入节点
void insert(skipList *list, int key, Student *student) {
    skipListNode *update[MAX_LEVEL + 1]; // 用于记录在每层中要插入新节点的前一个节点指针，本质是数组，只不过数组中存放的元素都是地址
    skipListNode *current = list->header; // 从头节点开始查找

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

        skipListNode *newNode = createNode(key, newLevel, student); // 创建新节点

        for (int i = 0; i <= newLevel; i++) { // 将新节点插入到每一层中
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// 根据姓名插入节点
void insertByName(skipList *list, char name[], Student *student) {
    skipListNode *update[MAX_LEVEL];
    skipListNode *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->student->name, name) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // 在最底层插入节点
    current = current->forward[0];

    if (current == NULL || strcmp(current->student->name, name) != 0) {
        int newLevel = randomLevel(); // 随机生成新节点的层数

        if (newLevel > list->level) { // 如果新节点的层数大于当前跳跃表的最高层数，需要更新最高层数
            for (int i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header; // 所有新层中的前一个节点指针都指向头节点
            }
            list->level = newLevel; // 更新跳跃表的最高层数
        }

        skipListNode *newNode = createNode(1, newLevel, student); // 创建新节点

        for (int i = 0; i <= newLevel; i++) { // 将新节点插入到每一层中
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// 输出学生信息
void printStudentInfo(Student *student) {
    printf("学号\t\t姓名\t性别\t班级\t\t进制转换\t多进制转换\t数值表达逻辑代数\t平均成绩\n");
    printf("%d\t%s\t%s\t%s\t%d\t\t%d\t\t%d\t\t\t%d\n",
           student->num,
           student->name, student->gender, student->class,
           student->grade1, student->grade2, student->grade3,
           student->average_grade);
}


// 按照学号读取数据
void ReadScoreByNum(skipList *list) {
    FILE *file;  // 文件指针

    // 打开原成绩文件
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("无法打开文件: %s\n", "score.txt");
        exit(1);
    }

    // 将学生数据存入数组
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        // 解析姓名和成绩
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

// 按照姓名读取学生数据
void ReadScoreByName(skipList *list) {
    FILE *file;  // 文件指针

    // 打开原成绩文件
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("无法打开文件: %s\n", "score.txt");
        exit(1);
    }

    // 将学生数据存入数组
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        // 解析姓名和成绩
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

// 按照平均成绩读取数据
void ReadScoreByAverageGrade(skipList *list) {
    FILE *file;  // 文件指针

    // 打开原成绩文件
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("无法打开文件: %s\n", "score.txt");
        exit(1);
    }

    // 将学生数据存入数组
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        // 解析姓名和成绩
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

// 按照学号查询数据
skipListNode *search(skipList *list, int key) {
    skipListNode *current = list->header;

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

// 按照姓名查询数据
skipListNode *searchByName(skipList *list, const char *name) {
    skipListNode *current = list->header;

    for (int i = list->level; i >= 0; i--) { // 从最高层开始向下查找
        while (current->forward[i] != NULL && strcmp(current->student->name, name) < 0) { // 在当前层中找到最后一个键值小于要查找的键值的节点
            current = current->forward[i];
        }
    }

    current = current->forward[0]; // 切换到第 0 层，即最底层的节点

    if (current != NULL && strcmp(current->student->name, name) == 0) { // 如果找到的节点不为空且键值等于要查找的键值
        return current;
    } else {
        return NULL;
    }
}

// 按照平均成绩查询数据
void searchAndPrintByAverageGrade(skipList *list, int key) {
    skipListNode *current = list->header;

    for (int i = list->level; i >= 0; i--) { // 从最高层开始向下查找
        while (current->forward[i] != NULL && current->forward[i]->key < key) { // 在当前层中找到最后一个键值小于要查找的键值的节点
            current = current->forward[i];
        }
    }

    current = current->forward[0]; // 切换到第 0 层，即最底层的节点

    while (current != NULL && current->key == key) { // 如果找到的节点不为空且键值等于要查找的键值
        printStudentInfo(current->student);
        current = current->forward[0];
    }
}


// 主函数
int main() {
    // 创建跳跃表
    skipList *list = createSkipList();
    while (1) {
        int select;
        printf("请选择查询方式:1.学号2.姓名3.平均成绩(退出请输入0)\n");
        scanf("%d", &select);
        if (select == 0) {
            exit(0);
        } else if (select == 1) {
            ReadScoreByNum(list);
            int key;
            printf("请输入要查询的学生学号");
            scanf("%d", &key);
            skipListNode *result = search(list, key);
            if (result != NULL) {
                printStudentInfo(result->student);
            } else {
                printf("未查询到相关学生信息\n");
            }
        } else if (select == 2) {
            ReadScoreByName(list);
            char name[MAX_NAME_LENGTH];
            printf("请输入学生姓名");
            scanf("%s", name);
            skipListNode *result = searchByName(list, name);
            if (result != NULL) {
                printStudentInfo(result->student);
            } else {
                printf("未查询到相关学生信息\n");
            }
        } else if (select == 3) {
            ReadScoreByAverageGrade(list);
            int key;
            printf("请输入要查询的平均成绩");
            scanf("%d", &key);
            searchAndPrintByAverageGrade(list, key);
        } else {
            printf("输入错误\n");
        }
    }


}