//
// Created by 30694 on 2024/1/25.
//
//
// Created by 30694 on 2024/1/24.
//
#include "stdio.h"
#include "string.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_NUM_STUDENTS 200

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


int main() {
    char filenames[3][MAX_FILENAME_LENGTH] = {
            "598854.txt",
            "598856.txt",
            "598858.txt"
    };

    char newFilenames[3][MAX_FILENAME_LENGTH] = {
            "new2_598854.txt",
            "new2_598856.txt",
            "new2_598858.txt"
    };

    FILE *file;
    FILE *newFile;
    Student students[MAX_NUM_STUDENTS];

    // 处理每个文本文件
    for (int i = 0; i < 3; i++) {
        // 打开原文件
        file = fopen(filenames[i], "r");
        if (file == NULL) {
            printf("无法打开文件: %s\n", filenames[i]);
            return 1;
        }

        // 创建新文件
        newFile = fopen(newFilenames[i], "w");
        if (newFile == NULL) {
            printf("无法创建文件: %s\n", newFilenames[i]);
            fclose(file);
            return 1;
        }
        int numStudents = 0;
        char line[MAX_NAME_LENGTH + 10];

        // 逐行读取原文件
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


        // 将结果写入新文件
        for (int j = 0; j < numStudents; j++) {
            fprintf(newFile, "%d %s %s %s %d %d %d %d\n",
                    students[j].num, students[j].name,
                    students[j].gender, students[j].class,
                    students[j].grade1, students[j].grade2, students[j].grade3,
                    students[j].average_grade);
        }

        // 关闭文件
        fclose(file);
        fclose(newFile);
    }
}