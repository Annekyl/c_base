#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//随机数 

#define MAX_LEVEL 100 // 跳表的最大层数

//思路：构建三个跳表，分别用文本文件把id，名字，平均数排序给一次存入每个跳表中。
//其中的逻辑跟链式储存结构（动态链表）很像。 
// 跳表是所有元素在底层，然后通过随机数来取决每个节点的层数，然后比较数和最高层的那个数比较
//如果那个数比比较的数大那么就换到这个节点的下一层，然后依次比较，直到查到相同的数为止。 
//id和名字和平均数其中插入和查找以及存入跳表相似，平均数要找到所有相同分数的人 

// 学生信息结构
typedef struct {
    int id;
    char name[50];
    char gender[10];
    char classes[50];
    double score_1;
    double score_2;
    double score_3;
    double average_score;
} Student;

// 跳表节点结构
typedef struct Node {
    int key;
    Student *student;
    struct Node *forward[1]; // 这里使用柔性数组
    //柔性数组：它允许在定义结构体时使用一个大小为 0 的数组。这种数组的大小是在运行时动态分配的，而不是在编译时确定的 
} Node;

// 跳表结构
typedef struct {
    int level;//层数 
    Node *header;//头指针 
    int type;
} SkipList;

//三个跳跃表 
typedef struct {
    SkipList *idSorted;//id跳表 
    SkipList *nameSorted;//名字跳表 
    SkipList *averageScoreSorted;//平均数跳表 
} CombinedSkipList;

// 创建新的跳表节点
Node *createNode(int key, Student *student, int level) {
    Node *node = (Node *)malloc(sizeof(Node) + level * sizeof(Node *));
    node->key = key;
    node->student = student;
    return node;
}

// 根据type创建指定类型的跳表
SkipList* createSkipList(int type) {
    SkipList* skipList = (SkipList*)malloc(sizeof(SkipList));
    skipList->level = 1;
    Student* dummyStudent = (Student*)malloc(sizeof(Student)); // 创建一个哨兵节点（头节点） 
    dummyStudent->id = -1;
    strcpy(dummyStudent->name, "Dummy");
    skipList->header = createNode(-1, dummyStudent, MAX_LEVEL); // 哨兵节点的key设置为-1
    for (int i = 0; i < MAX_LEVEL; i++) {
        skipList->header->forward[i] = NULL;
    }
    return skipList;
}

// 向跳表中插入节点(由ID)
void insertElementbyID(SkipList *list, int key, Student *student) {
    Node *update[MAX_LEVEL];
    Node *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {//从上往下 
        while (current->forward[i] != NULL && current->forward[i]->key < key) {//比较本身的数和下一个数 
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    if (current == NULL || current->key != key) {
	//在插入新节点之前确定新节点的层数，并在需要时更新跳表的整体层数和相关指针 
        int newLevel = 1;
        while (rand() < RAND_MAX / 2 && newLevel < MAX_LEVEL) {
            newLevel++;
        }

        if (newLevel > list->level) {
            for (int i = list->level; i < newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(key, student, newLevel);
        //确定的层数将新节点插入到跳表中的各个层级链表中 
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// 向跳表中插入节点(由名字)
void insertElementbyname(SkipList *list, Student *student) {
    Node *update[MAX_LEVEL];
    Node *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->student->name, student->name) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    // 在原有节点为空或学生姓名不等于当前插入学生姓名时执行插入操作
    if (current == NULL || strcmp(current->student->name, student->name) != 0) {
        int newLevel = 1;
        while (rand() < RAND_MAX / 2 && newLevel < MAX_LEVEL) {
            newLevel++;
        }

        if (newLevel > list->level) {
            for (int i = list->level; i < newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(student->id, student, newLevel);
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// 向跳表中插入节点(由分数)
void insertElementbyscore(SkipList *list, Student *student) {
    Node *update[MAX_LEVEL];
    Node *current = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->student->average_score < student->average_score) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    // 在原有节点为空或学生的平均分数不等于当前插入学生的平均分数时执行插入操作
    if (current == NULL || current->student->average_score >= student->average_score) {
        int newLevel = 1;
        while (rand() < RAND_MAX / 2 && newLevel < MAX_LEVEL) {
            newLevel++;
        }

        if (newLevel > list->level) {
            for (int i = list->level; i < newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(student->id, student, newLevel);
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// 读取文本文件中的学生信息并插入到跳表中(id
void readStudentDataid(const char *fileName, SkipList *skipList) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", fileName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student *student = (Student *)malloc(sizeof(Student));
        if (sscanf(line, "%d,%49[^,],%9[^,],%49[^,],%lf,%lf,%lf,%lf",
                   &student->id, student->name, student->gender, student->classes,
                   &student->score_1, &student->score_2, &student->score_3, &student->average_score) == 8) {
            insertElementbyID(skipList, student->id, student); // 将学生数据插入到跳表中
        }
    }
    fclose(file);
}

// 读取文本文件中的学生信息并插入到跳表中(name
void readStudentDataname(const char *fileName, SkipList *skipList) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", fileName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student *student = (Student *)malloc(sizeof(Student));
        if (sscanf(line, "%d,%49[^,],%9[^,],%49[^,],%lf,%lf,%lf,%lf",
                   &student->id, student->name, student->gender, student->classes,
                   &student->score_1, &student->score_2, &student->score_3, &student->average_score) == 8) {
            insertElementbyname(skipList, student); // 将学生数据插入到跳表中
        }
    }
    fclose(file);
}

// 读取文本文件中的学生信息并插入到跳表中(score
void readStudentDatascore(const char *fileName, SkipList *skipList) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", fileName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Student *student = (Student *)malloc(sizeof(Student));
        if (sscanf(line, "%d,%49[^,],%9[^,],%49[^,],%lf,%lf,%lf,%lf",
                   &student->id, student->name, student->gender, student->classes,
                   &student->score_1, &student->score_2, &student->score_3, &student->average_score) == 8) {
            insertElementbyscore(skipList, student); // 将学生数据插入到跳表中
        }
    }
    fclose(file);
}

// 在跳表中按姓名查找节点(查ID)
Node *findElementByID(SkipList *list, int id) {
    Node *current = list->header;
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->student->id < id) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != NULL && current->student->id == id) {//直到查到目标id 
        return current;
    } else {
        return NULL;
    }
}

// 在跳表中按姓名查找节点(查名字)
Node *findElementByName(SkipList *list, const char *name) {
    Node *current = list->header;
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->student->name, name) < 0) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != NULL && strcmp(current->student->name, name)==0) {
        return current;
    } else {
        return NULL;
    }
}

//（遍历查找得到所有相同的分数的人） 
void findStudentsWithSameAverage(SkipList *list, double averageScore) {
    Node *current = list->header;
    int found = 0;
    char resultString[10000]; // 用于存储结果的字符串
    strcpy(resultString, "学生信息：\n");

    // 从最高层开始查找具有相同平均值的学生节点
    for (int i = list->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->student->average_score < averageScore) {
            current = current->forward[i];
        }
        if (current->forward[i] != NULL && current->forward[i]->student->average_score == averageScore) {
            Node *temp = current->forward[i];
            while (temp != NULL && temp->student->average_score == averageScore) {
                char tempString[200]; // 临时存储单个学生信息的字符串
                snprintf(tempString, sizeof(tempString), "学号：%d\n姓名：%s\n性别：%s\n班级：%s\n分数1：%.1lf\n分数2：%.1lf\n分数3：%.1lf\n平均成绩：%.1lf\n", 
                        temp->key, temp->student->name, temp->student->gender, temp->student->classes,
                        temp->student->score_1, temp->student->score_2, temp->student->score_3, temp->student->average_score);
                strncat(resultString, tempString, sizeof(resultString) - strlen(resultString) - 1); // 使用strncat()确保不会超出结果字符串的界限
                temp = temp->forward[0];
                found = 1;
            }
            break; // 结束外层循环
        }
    }
    if (found) {
        printf("%s", resultString); // 打印所有相同平均值学生的信息
    } else {
        printf("未找到具有平均值为 %.1lf 的学生信息\n", averageScore);
    }
}

// 打印跳表
void printSkipList(SkipList *list) {
    for (int level = list->level - 1; level >= 0; level--) {
        printf("Level %d: ", level);
        Node *current = list->header->forward[level];
        while (current != NULL) {
            printf("%d, %s, %s, %s, %.1lf, %.1lf, %.1lf, %.1lf\n", current->key, current->student->name,current->student->gender, current->student->classes,
                   current->student->score_1, current->student->score_2, current->student->score_3, current->student->average_score);
            current = current->forward[level];
        }
        printf("NULL\n");
    }
}

// 销毁跳表
void destroySkipList(SkipList *list) {
    Node *current = list->header->forward[0];
    while (current != NULL) {
        Node *temp = current;
        current = current->forward[0];
        free(temp->student); // 释放学生信息内存
        free(temp); // 释放节点内存
    }
    free(list->header); // 释放哨兵节点
    free(list); // 释放跳表结构内存
}


int main() {
	
    CombinedSkipList combinedSkipList;
    
    int judge = 1;
    while (judge == 1) {
        int type;
        printf("请输入查询类型（1=学号/2=姓名/3=成绩）: ");
        scanf("%d", &type);
        srand((unsigned)time(NULL)); // 随机数 

        if (type == 1) {
		    combinedSkipList.idSorted = createSkipList(1);
		
		    // 从文件中读取学生信息并插入到跳表中
		    readStudentDataid("ID排序的成绩单.txt", combinedSkipList.idSorted); 
		    
		    // 打印跳表
		    //printSkipList(combinedSkipList.idSorted);
		    
		    // 查询学生信息
		    int queryID;
		    printf("请输入要查询的学生ID：");
		    scanf("%d", &queryID);
		
		    // 在跳表中按ID查找学生
		    Node *result = findElementByID(combinedSkipList.idSorted, queryID);
		    if (result != NULL) {
		        printf("找到了学生信息：\n");
		        printf("学号：%d\n姓名：%s\n性别：%s\n班级：%s\n分数1：%.1lf\n分数2：%.1lf\n分数3：%.1lf\n平均成绩：%.1lf\n", 
		               result->student->id, result->student->name, result->student->gender, result->student->classes,
		               result->student->score_1, result->student->score_2, result->student->score_3, result->student->average_score);
		    } else {
		        printf("没有找到指定ID的学生信息。\n");
		    }
		
		    // 用于释放内存的代码（如果需要）
		    destroySkipList(combinedSkipList.idSorted);
		            
        } 
		else if (type == 2) {
        	
		    combinedSkipList.nameSorted = createSkipList(2);
		    
		    readStudentDataname("名字排序的成绩单.txt", combinedSkipList.nameSorted); // 从文件中读取学生信息并插入到跳表中
		    //printSkipList(combinedSkipList.nameSorted);
		    
		    // 查询学生信息
		    char queryname[50];
		    printf("请输入要查询的学生名字：");
		    scanf("%49s", queryname);
		    
		    Node *result = findElementByName(combinedSkipList.nameSorted, queryname); // 在跳表中按姓名查找学生
		    if (result != NULL) {
		        printf("找到了学生信息：\n");
		        printf("学号：%d\n姓名：%s\n性别：%s\n班级：%s\n分数1：%.1lf\n分数2：%.1lf\n分数3：%.1lf\n平均成绩：%.1lf\n", result->key, result->student->name,result->student->gender, result->student->classes,
		                   result->student->score_1, result->student->score_2, result->student->score_3, result->student->average_score);
		    } else {
		        printf("没有找到指定姓名的学生信息。\n");
		    }
		
		    destroySkipList(combinedSkipList.nameSorted); // 释放跳表结构内存

            
        }                  
		else if (type == 3) {
        	
		    combinedSkipList.averageScoreSorted = createSkipList(3); // 创建一个新的跳表
		
		    // 从文件中读取学生信息并插入到跳表中
		    readStudentDatascore("平均值排序的成绩单.txt", combinedSkipList.averageScoreSorted);
		    
		    // 打印跳表
		    //printSkipList(combinedSkipList.averageScoreSorted);
		
		    // 查询学生信息
		    double queryScore;
		    printf("请输入要查询的学生平均分数：");
		    scanf("%lf", &queryScore);
		
		    findStudentsWithSameAverage(combinedSkipList.averageScoreSorted, queryScore);
		
		    // 销毁跳表
		    destroySkipList(combinedSkipList.averageScoreSorted);
            
        } 
		else {
            printf("查询类型错误\n");
        }

        printf("是否继续查询？（1=是/0=否）：");
        scanf("%d", &judge);
    }
    return 0;
}
