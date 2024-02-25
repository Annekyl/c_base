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
    float grade1;
    float grade2;
    float grade3;
    float average_grade;
} Student;

Student students[MAX_NUM_STUDENTS];  // ѧ���ṹ������
int numStudents = 0;  // ѧ������

// ��ȡ����
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
        float grade1;
        float grade2;
        float grade3;
        sscanf(line, "%d %s %s %s %f %f %f",
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
            } else if (students[j].average_grade == students[j + 1].average_grade) {
                // ƽ���ɼ���ͬ������ѧ������
                if (students[j].num > students[j + 1].num) {
                    // ����λ��
                    Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
    }
}

// ����ѧ�Ų�ѯѧ��
int SearchByNumber(int targetNum) {
    SortByNumber();
    int left = 0;
    int right = numStudents - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].num == targetNum) {
            return mid;  // �ҵ�Ŀ��ѧ�ţ������±�
        } else if (students[mid].num < targetNum) {
            left = mid + 1;  // Ŀ��ѧ�����Ұ벿�֣���С������Χ
        } else {
            right = mid - 1;  // Ŀ��ѧ������벿�֣���С������Χ
        }
    }

    return -1;  // û���ҵ�Ŀ��ѧ�ţ����� -1
}

// ����������ѯѧ��
int SearchByName(char *targetName) {
    SortByName();
    int left = 0;
    int right = numStudents - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmpResult = strcmp(students[mid].name, targetName);
        if (cmpResult == 0) {
            return mid;  // �ҵ�Ŀ�������������±�
        } else if (cmpResult < 0) {
            left = mid + 1;  // Ŀ���������Ұ벿�֣���С������Χ
        } else {
            right = mid - 1;  // Ŀ����������벿�֣���С������Χ
        }
    }

    return -1;  // û���ҵ�Ŀ������������ -1
}

// ����ƽ���ɼ���ѯ
int SearchByAverageGrade(float targetGrade) {
    SortByAverageGrade();
    int left = 0;
    int right = numStudents - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].average_grade == targetGrade) {
            return mid;  // �ҵ�Ŀ��ƽ���ɼ��������±�
        } else if (students[mid].average_grade < targetGrade) {
            left = mid + 1;  // Ŀ��ƽ���ɼ����Ұ벿�֣���С������Χ
        } else {
            right = mid - 1;  // Ŀ��ƽ���ɼ�����벿�֣���С������Χ
        }
    }

    return -1;  // û���ҵ�Ŀ��ƽ���ɼ������� -1
}

// ��ӡѧ����Ϣ
void printStudentInfo(int index) {
    printf("ѧ��\t\t����\t�Ա�\t�༶\t\t����ת��\t�����ת��\t��ֵ����߼�����\tƽ���ɼ�\n");
    printf("%d\t%s\t%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t\t\t%.2f\n",
           students[index].num,
           students[index].name, students[index].gender, students[index].class,
           students[index].grade1, students[index].grade2, students[index].grade3,
           students[index].average_grade);
}

// ѡ����ҷ���
void SelectSearch() {
    int select;
    printf("��ѡ���ѯ��ʽ��1.ѧ��\t2.����\t3.ƽ���ɼ�\t");
    scanf("%d", &select);

    switch (select) {
        case 1: {
            int targetNum;
            printf("������Ҫ��ѯ��ѧ��");
            scanf("%d", &targetNum);
            int index = SearchByNumber(targetNum);
            if (index != -1) {
                printStudentInfo(index);
            } else {
                printf("û���ҵ���ѧ�Ŷ�Ӧ��ѧ�����ݡ�\n");
            }
            break;
        }
        case 2: {
            char targetName[20];
            printf("������ѧ��������");
            scanf("%s", targetName);
            int index = SearchByName(targetName);
            if (index != -1) {
                printStudentInfo(index);
            } else {
                printf("û���ҵ���ѧ�Ŷ�Ӧ��ѧ�����ݡ�\n");
            }
            break;
        }
        case 3: {
            float targetAverageGrade;
            printf("������ƽ���ɼ���");
            scanf("%f", &targetAverageGrade);
            int index = SearchByAverageGrade(targetAverageGrade);
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
                printf("û���ҵ���ѧ�Ŷ�Ӧ��ѧ�����ݡ�\n");
            }
            break;
        }
        default:
            printf("�������");
    }

    int n;
    printf("�Ƿ������ѯ 1.����\t2.����");
    scanf("%d", &n);
    if (n == 1) {
        SelectSearch();
    }
}

int main() {
    ReadScore();  // ��ȡѧ������
    SelectSearch();  // ��ʼ��ѯ
    return 0;
}

