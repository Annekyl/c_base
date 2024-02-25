//
// Created by 30694 on 2024/1/25.
//
//
// Created by 30694 on 2024/1/25.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_NAME_LENGTH 50  // 学生姓名长度
#define MAX_NUM_STUDENTS 400  // 学生结构体数量

// 学生结构体
typedef struct {
    int num;  // 学号
    char name[MAX_NAME_LENGTH];  // 姓名
    char gender[5];  // 性别
    char class[20];  // 班级
    int grade1;
    int grade2;
    int grade3;
    int average_grade;
} Student;

Student students[MAX_NUM_STUDENTS];  // 学生结构体数组
int numStudents = 0;  // 学生数量

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
        int grade1;
        int grade2;
        int grade3;
        sscanf(line, "%d %s %s %s %d %d %d",
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

// 按照学号排序
void SortByNumber() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].num > students[j + 1].num) {
                // 交换位置
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 按照姓名排序
void SortByName() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                // 交换位置
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 按照平均成绩排序
void SortByAverageGrade() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].average_grade > students[j + 1].average_grade) {
                // 交换位置
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    ReadScore();  // 读取学生数据

    // 按照学号排序
    SortByNumber();
    // 打印排序后的学生数据
    for (int i = 0; i < numStudents; i++) {
        printf("学号：%d，姓名：%s\n", students[i].num, students[i].name);
    }

    // 按照姓名排序
    SortByName();
    // 打印排序后的学生数据
    for (int i = 0; i < numStudents; i++) {
        printf("学号：%d，姓名：%s，平均成绩：%d\n", students[i].num, students[i].name, students[i].average_grade);
    }

    // 按照平均成绩排序
    SortByAverageGrade();
    for (int i = 0; i < numStudents; i++) {
        printf("学号：%d，姓名：%s，平均成绩：%d\n", students[i].num, students[i].name, students[i].average_grade);
    }

    return 0;
}