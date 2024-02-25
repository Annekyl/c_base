#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "wchar.h"

#define MAX_NAME_LENGTH 50  // 学生姓名长度
#define MAX_NUM_STUDENTS 400  // 学生结构体数量

struct Student {
    int num;  // 学号
    char name[MAX_NAME_LENGTH];  // 姓名
    char gender[5];  // 性别。
    char class[20];  // 班级
    float grade1;
    float grade2;
    float grade3;
    float average_grade;
};

struct Student students[MAX_NUM_STUDENTS];  // 学生结构体数组
int numStudents = 0;  // 实际学生数量

// 读取数据
void ReadScore() {
    FILE *file;  // 文件指针

    // 打开原成绩文件
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("无法打开文件: %s\n", "score.txt");
        exit(1);
    }

    // 将学生数据存入数组
    char line[MAX_NAME_LENGTH + 10];
    while (fgets(line, sizeof(line), file) != NULL) {
        // 解析姓名和成绩
        int num;
        char name[MAX_NAME_LENGTH];
        char gender[5];
        char class[20];
        float grade1;
        float grade2;
        float grade3;
        sscanf(line, "%d %s %s %s %f %f %f",
               &num, name, gender, class, &grade1, &grade2, &grade3);

        // 添加到结构体数组中
        students[numStudents].num = num;
        strcpy(students[numStudents].name, name);
        strcpy(students[numStudents].gender, gender);
        strcpy(students[numStudents].class, class);
        students[numStudents].grade1 = grade1;
        students[numStudents].grade2 = grade2;
        students[numStudents].grade3 = grade3;
        students[numStudents].average_grade = (grade1 + grade2 + grade3) / 3;
        numStudents++;
    }
}

// 按学号排序
void SortByNumber() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].num > students[j + 1].num) {
                // 交换位置
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 按姓名排序
void SortByName() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                // 交换位置
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 按平均成绩排序
void SortByAverageGrade() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].average_grade > students[j + 1].average_grade) {
                // 交换位置
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            } else if (students[j].average_grade == students[j + 1].average_grade) {
                // 平均成绩相同，按照学号排序
                if (students[j].num > students[j + 1].num) {
                    // 交换位置
                    struct Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
    }
}

// 输出学生信息
void printStudentInfo(int index) {
    printf("学号\t姓名\t\t性别\t班级\t\t进制转换\t多进制转换\t数值表达逻辑代数\t平均成绩\n");
    printf("%d\t%s\t%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t\t\t%.2f\n",
           students[index].num,
           students[index].name, students[index].gender, students[index].class,
           students[index].grade1, students[index].grade2, students[index].grade3,
           students[index].average_grade);
}

// 按照属性递归查询学生
int SearchRecursive(void* target, int left, int right, int (*cmp)(const struct Student*, const void*)) {
    /*
    target：指向目标信息的指针
    left：需要查询的区间左端点
    right：需要查询的区间右端点
    cmp：一个函数指针，指向比较函数
     */
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;
    if (cmp(students+mid, target) == 0) {  // 指针算术
        return mid;
    } else if (cmp(students+mid, target) < 0) {
        return SearchRecursive(target, mid + 1, right, cmp);
    } else {
        return SearchRecursive(target, left, mid - 1, cmp);
    }
}

// 比较函数：按学号
int cmpByNumber(const struct Student* s, const void* targetNum) {
    return s->num - *((int*)targetNum);
}

// 比较函数：按姓名
int cmpByName(const struct Student* s, const void* targetName) {
    return strcmp(s->name, (const char*)targetName);
}

// 比较函数：按平均成绩
int cmpByAverageGrade(const struct Student* s, const void* targetGrade) {
    if (s->average_grade < *((float*)targetGrade)) {
        return -1;
    } else if (s->average_grade > *((float*)targetGrade)) {
        return 1;
    } else {
        return 0;
    }
}

int SearchByName(char *targetName) {
    SortByName();
    int left = 0;
    int right = numStudents - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmpResult = strcmp(students[mid].name, targetName);
        if (cmpResult == 0) {
            return mid;  // 找到目标姓名，返回下标
        } else if (cmpResult < 0) {
            left = mid + 1;  // 目标姓名在右半部分，缩小搜索范围
        } else {
            right = mid - 1;  // 目标姓名在左半部分，缩小搜索范围
        }
    }

    return -1;  // 没有找到目标姓名，返回 -1
}

// 选择查找方法
void SelectSearchRecursive() {
    int select;
    printf("请选择查询方式：1.学号\t2.姓名\t3.平均成绩\t");
    scanf("%d", &select);

    switch (select) {
        case 1: {
            int targetNum;
            printf("请输入要查询的学号：");
            scanf("%d", &targetNum);
            int index = SearchRecursive(&targetNum, 0, numStudents - 1, cmpByNumber);
            if (index != -1) {
                printStudentInfo(index);
            } else {
                printf("没有找到该学号对应的学生数据。\n");
            }
            break;
        }
        case 2: {
            char targetName[20];
            printf("请输入学生姓名：");
            scanf("%s", targetName);
            int index = SearchByName(targetName);
            if (index != -1) {
                printStudentInfo(index);
            } else {
                printf("没有找到该姓名对应的学生数据。\n");
            }
            break;
        }
        case 3: {
            float targetAverageGrade;
            printf("请输入平均成绩：");
            scanf("%f", &targetAverageGrade);
            int index = SearchRecursive(&targetAverageGrade, 0, numStudents - 1, cmpByAverageGrade);
            if (index != -1) {
                printStudentInfo(index);
                for (int found = 0; found < numStudents; ++found) {
                    if (students[found].average_grade == students[index].average_grade) {
                        printf("%d\t%s\t%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t\t\t%.2f\n",
                               students[found].num,
                               students[found].name, students[found].gender, students[found].class,
                               students[found].grade1, students[found].grade2, students[found].grade3,
                               students[found].average_grade);
                    }
                }
            } else {
                printf("没有找到该平均成绩对应的学生数据。\n");
            }
            break;
        }
        default:
            printf("输入错误！");
    }

    int n;
    printf("是否继续查询？1.继续\t2.结束：");
    scanf("%d", &n);
    if (n == 1) {
        SelectSearchRecursive();
    }
}

int main() {
    ReadScore();
    SelectSearchRecursive();  // 开始查询
    return 0;
}
