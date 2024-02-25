//
// Created by 30694 on 2024/1/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 100
#define MAX_NUM_STUDENTS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} Student;

void replaceSpacesWithZero(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = '0';
        }
        i++;
    }
}

void calculateAverageScore(Student *students, int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        int sum = 0;
        for (int j = 0; j < numStudents; j++) {
            sum += students[j].score;
        }
        students[i].score = sum / numStudents;
    }
}

int main() {
    char filenames[3][MAX_FILENAME_LENGTH] = {
            "598854.txt",
            "598856.txt",
            "598858.txt"
    };

    char newFilenames[3][MAX_FILENAME_LENGTH] = {
            "new_598854.txt",
            "new_598856.txt",
            "new_598858.txt"
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
            char name[MAX_NAME_LENGTH];
            int score;
            sscanf(line, "%s %d", name, &score);

            // 替换空格为0
            replaceSpacesWithZero(name);

            // 添加到结构体数组中
            strcpy(students[numStudents].name, name);
            students[numStudents].score = score;
            numStudents++;
        }

        // 计算平均成绩
        calculateAverageScore(students, numStudents);

        // 将结果写入新文件
        for (int j = 0; j < numStudents; j++) {
            fprintf(newFile, "%s %d\n", students[j].name, students[j].score);
        }

        // 关闭文件
        fclose(file);
        fclose(newFile);
    }

    printf("操作完成\n");

    return 0;
}
