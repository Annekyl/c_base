//
// Created by 30694 on 2024/1/24.
//
#include "stdio.h"
#include "string.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_NUM_STUDENTS 500

// 学生结构体
typedef struct {
    int order;  // 序号
    int num;  // 学号
    char name[MAX_NAME_LENGTH];  // 姓名
    char gender[5];  // 性别
    char class[20];  // 班级
    int grade1;
    int grade2;
    int grade3;
    int average_grade;
} Student;


// 查询学生成绩函数
void searchStudentScore(Student students[], int numStudents) {
    int searchId;
    char searchName[MAX_NAME_LENGTH];
    int found = 0;
    int option;
    printf("请选择查询方式:\n1.学号\n2.姓名");
    scanf("%d", &option);
    if (option == 1) {
        printf("请输入学号：");
        scanf("%d", &searchId);
    } else if (option == 2) {
        printf("请输入姓名：");
        scanf("%s", searchName);
    }

    // 遍历学生数组，查找匹配的学生信息
    for (int i = 0; i < numStudents; i++) {
        if ((option == 1 && students[i].num == searchId) ||
            (option == 2 && strcmp(students[i].name, searchName) == 0)) {
            printf("序号\t学号\t\t姓名\t性别\t班级\t\t进制转换\t多进制转换\t数值表达逻辑代数\t平均成绩\n");
            printf("%d\t%d\t%s\t%s\t%s\t%d\t\t%d\t\t%d\t\t\t%d\n",
                   students[i].order, students[i].num,
                   students[i].name, students[i].gender, students[i].class,
                   students[i].grade1, students[i].grade2, students[i].grade3,
                   students[i].average_grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到匹配的学生信息。\n");
    }
}

int main() {
    // 定义变量
    Student students[MAX_NUM_STUDENTS];  // 学生结构体
    FILE *file;  // 文件指针
    int numStudents = 0;  // 第几个学生

    // 文件名
    char newFilenames[3][MAX_FILENAME_LENGTH] = {
            "new_598854.txt",
            "new_598856.txt",
            "new_598858.txt"
    };

    // 读取三个文件，写入结构体中
    for (int i = 0; i < 3; ++i) {
        // 写读模式打开文件
        file = fopen(newFilenames[i], "r");

        // 如果为空，结束程序
        if (file == NULL) {
            printf("无法打开文件: %s\n", newFilenames[i]);
            return 1;
        }
        char line[MAX_NAME_LENGTH + 10];

        while (fgets(line, sizeof(line), file) != NULL) {
            // 解析姓名和成绩
            int order;
            int num;
            char name[MAX_NAME_LENGTH];
            char gender[5];
            char class[20];
            int grade1;
            int grade2;
            int grade3;
            sscanf(line, "%d %d %s %s %s %d %d %d",
                   &order, &num, name, gender, class, &grade1, &grade2, &grade3);

            // 添加到结构体数组中
            students[numStudents].order = order;
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

    int n=1;
    while (n==1) {
        searchStudentScore(students, numStudents);
        printf("是否继续查询 1.继续\t2.结束");
        scanf("%d", &n);
    }
}