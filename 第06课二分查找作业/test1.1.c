//
// Created by 30694 on 2024/1/25.
//
//
// Created by 30694 on 2024/1/25.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_NAME_LENGTH 50  // ѧ����������
#define MAX_NUM_STUDENTS 400  // ѧ���ṹ������

// ѧ���ṹ��
typedef struct {
    int num;  // ѧ��
    char name[MAX_NAME_LENGTH];  // ����
    char gender[5];  // �Ա�
    char class[20];  // �༶
    int grade1;
    int grade2;
    int grade3;
    int average_grade;
} Student;

Student students[MAX_NUM_STUDENTS];  // ѧ���ṹ������
int numStudents = 0;  // ѧ������

void ReadScore() {
    FILE *file;  // �ļ�ָ��

    // ��ԭ�ɼ��ļ�
    file = fopen("score.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�: %s\n", "score.txt");
        exit(1);
    }

    // ��ѧ�����ݴ�������
    char line[MAX_NAME_LENGTH + 10];
    while (fgets(line, sizeof(line), file) != NULL) {
        // ���������ͳɼ�
        int num;
        char name[MAX_NAME_LENGTH];
        char gender[5];
        char class[20];
        int grade1;
        int grade2;
        int grade3;
        sscanf(line, "%d %s %s %s %d %d %d",
               &num, name, gender, class, &grade1, &grade2, &grade3);

        // ��ӵ��ṹ��������
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

// ����ѧ������
void SortByNumber() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].num > students[j + 1].num) {
                // ����λ��
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// ������������
void SortByName() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                // ����λ��
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// ����ƽ���ɼ�����
void SortByAverageGrade() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].average_grade > students[j + 1].average_grade) {
                // ����λ��
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    ReadScore();  // ��ȡѧ������

    // ����ѧ������
    SortByNumber();
    // ��ӡ������ѧ������
    for (int i = 0; i < numStudents; i++) {
        printf("ѧ�ţ�%d��������%s\n", students[i].num, students[i].name);
    }

    // ������������
    SortByName();
    // ��ӡ������ѧ������
    for (int i = 0; i < numStudents; i++) {
        printf("ѧ�ţ�%d��������%s��ƽ���ɼ���%d\n", students[i].num, students[i].name, students[i].average_grade);
    }

    // ����ƽ���ɼ�����
    SortByAverageGrade();
    for (int i = 0; i < numStudents; i++) {
        printf("ѧ�ţ�%d��������%s��ƽ���ɼ���%d\n", students[i].num, students[i].name, students[i].average_grade);
    }

    return 0;
}