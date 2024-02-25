#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "wchar.h"

#define MAX_NAME_LENGTH 50  // ѧ����������
#define MAX_NUM_STUDENTS 400  // ѧ���ṹ������

struct Student {
    int num;  // ѧ��
    char name[MAX_NAME_LENGTH];  // ����
    char gender[5];  // �Ա�
    char class[20];  // �༶
    float grade1;
    float grade2;
    float grade3;
    float average_grade;
};

struct Student students[MAX_NUM_STUDENTS];  // ѧ���ṹ������
int numStudents = 0;  // ʵ��ѧ������

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

// ��ѧ������
void SortByNumber() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].num > students[j + 1].num) {
                // ����λ��
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// ����������
void SortByName() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                // ����λ��
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// ��ƽ���ɼ�����
void SortByAverageGrade() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].average_grade > students[j + 1].average_grade) {
                // ����λ��
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            } else if (students[j].average_grade == students[j + 1].average_grade) {
                // ƽ���ɼ���ͬ������ѧ������
                if (students[j].num > students[j + 1].num) {
                    // ����λ��
                    struct Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
    }
}

// ���ѧ����Ϣ
void printStudentInfo(int index) {
    printf("ѧ��\t����\t\t�Ա�\t�༶\t\t����ת��\t�����ת��\t��ֵ����߼�����\tƽ���ɼ�\n");
    printf("%d\t%s\t%s\t%s\t%.0f\t\t%.0f\t\t%.0f\t\t\t%.2f\n",
           students[index].num,
           students[index].name, students[index].gender, students[index].class,
           students[index].grade1, students[index].grade2, students[index].grade3,
           students[index].average_grade);
}

// �������Եݹ��ѯѧ��
int SearchRecursive(void* target, int left, int right, int (*cmp)(const struct Student*, const void*)) {
    /*
    target��ָ��Ŀ����Ϣ��ָ��
    left����Ҫ��ѯ��������˵�
    right����Ҫ��ѯ�������Ҷ˵�
    cmp��һ������ָ�룬ָ��ȽϺ���
     */
    if (left > right) {
        return -1;
    }

    int mid = (left + right) / 2;
    if (cmp(students+mid, target) == 0) {  // ָ������
        return mid;
    } else if (cmp(students+mid, target) < 0) {
        return SearchRecursive(target, mid + 1, right, cmp);
    } else {
        return SearchRecursive(target, left, mid - 1, cmp);
    }
}

// �ȽϺ�������ѧ��
int cmpByNumber(const struct Student* s, const void* targetNum) {
    return s->num - *((int*)targetNum);
}

// �ȽϺ�����������
int cmpByName(const struct Student* s, const void* targetName) {
    return strcmp(s->name, (const char*)targetName);
}

// �ȽϺ�������ƽ���ɼ�
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
            return mid;  // �ҵ�Ŀ�������������±�
        } else if (cmpResult < 0) {
            left = mid + 1;  // Ŀ���������Ұ벿�֣���С������Χ
        } else {
            right = mid - 1;  // Ŀ����������벿�֣���С������Χ
        }
    }

    return -1;  // û���ҵ�Ŀ������������ -1
}

// ѡ����ҷ���
void SelectSearchRecursive() {
    int select;
    printf("��ѡ���ѯ��ʽ��1.ѧ��\t2.����\t3.ƽ���ɼ�\t");
    scanf("%d", &select);

    switch (select) {
        case 1: {
            int targetNum;
            printf("������Ҫ��ѯ��ѧ�ţ�");
            scanf("%d", &targetNum);
            int index = SearchRecursive(&targetNum, 0, numStudents - 1, cmpByNumber);
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
                printf("û���ҵ���������Ӧ��ѧ�����ݡ�\n");
            }
            break;
        }
        case 3: {
            float targetAverageGrade;
            printf("������ƽ���ɼ���");
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
                printf("û���ҵ���ƽ���ɼ���Ӧ��ѧ�����ݡ�\n");
            }
            break;
        }
        default:
            printf("�������");
    }

    int n;
    printf("�Ƿ������ѯ��1.����\t2.������");
    scanf("%d", &n);
    if (n == 1) {
        SelectSearchRecursive();
    }
}

int main() {
    ReadScore();
    SelectSearchRecursive();  // ��ʼ��ѯ
    return 0;
}
