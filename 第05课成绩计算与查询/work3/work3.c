//
// Created by 30694 on 2024/1/24.
//
#include "stdio.h"
#include "string.h"

#define MAX_FILENAME_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_NUM_STUDENTS 500

// ѧ���ṹ��
typedef struct {
    int order;  // ���
    int num;  // ѧ��
    char name[MAX_NAME_LENGTH];  // ����
    char gender[5];  // �Ա�
    char class[20];  // �༶
    int grade1;
    int grade2;
    int grade3;
    int average_grade;
} Student;


// ��ѯѧ���ɼ�����
void searchStudentScore(Student students[], int numStudents) {
    int searchId;
    char searchName[MAX_NAME_LENGTH];
    int found = 0;
    int option;
    printf("��ѡ���ѯ��ʽ:\n1.ѧ��\n2.����");
    scanf("%d", &option);
    if (option == 1) {
        printf("������ѧ�ţ�");
        scanf("%d", &searchId);
    } else if (option == 2) {
        printf("������������");
        scanf("%s", searchName);
    }

    // ����ѧ�����飬����ƥ���ѧ����Ϣ
    for (int i = 0; i < numStudents; i++) {
        if ((option == 1 && students[i].num == searchId) ||
            (option == 2 && strcmp(students[i].name, searchName) == 0)) {
            printf("���\tѧ��\t\t����\t�Ա�\t�༶\t\t����ת��\t�����ת��\t��ֵ����߼�����\tƽ���ɼ�\n");
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
        printf("δ�ҵ�ƥ���ѧ����Ϣ��\n");
    }
}

int main() {
    // �������
    Student students[MAX_NUM_STUDENTS];  // ѧ���ṹ��
    FILE *file;  // �ļ�ָ��
    int numStudents = 0;  // �ڼ���ѧ��

    // �ļ���
    char newFilenames[3][MAX_FILENAME_LENGTH] = {
            "new_598854.txt",
            "new_598856.txt",
            "new_598858.txt"
    };

    // ��ȡ�����ļ���д��ṹ����
    for (int i = 0; i < 3; ++i) {
        // д��ģʽ���ļ�
        file = fopen(newFilenames[i], "r");

        // ���Ϊ�գ���������
        if (file == NULL) {
            printf("�޷����ļ�: %s\n", newFilenames[i]);
            return 1;
        }
        char line[MAX_NAME_LENGTH + 10];

        while (fgets(line, sizeof(line), file) != NULL) {
            // ���������ͳɼ�
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

            // ��ӵ��ṹ��������
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
        printf("�Ƿ������ѯ 1.����\t2.����");
        scanf("%d", &n);
    }
}