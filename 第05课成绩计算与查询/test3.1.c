#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// 学生结构体
typedef struct {
    int student_id;
    char name[MAX_NAME_LENGTH];
    float score;
} Student;

// 查询学生成绩函数
void searchStudentScore(Student students[], int numStudents, int option) {
    int searchId;
    char searchName[MAX_NAME_LENGTH];
    int found = 0;

    printf("请输入要查询的学生信息：\n");
    if (option == 1) {
        printf("请输入学号：");
        scanf("%d", &searchId);
    } else if (option == 2) {
        printf("请输入姓名：");
        scanf("%s", searchName);
    }

    // 遍历学生数组，查找匹配的学生信息
    for (int i = 0; i < numStudents; i++) {
        if ((option == 1 && students[i].student_id == searchId) ||
            (option == 2 && strcmp(students[i].name, searchName) == 0)) {
            printf("学号：%d\n", students[i].student_id);
            printf("姓名：%s\n", students[i].name);
            printf("成绩：%.2f\n", students[i].score);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到匹配的学生信息。\n");
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents;

    // 假设已有学生数据，这里只是示例，可以根据实际情况修改
    numStudents = 3;
    students[0].student_id = 1;
    strcpy(students[0].name, "张三");
    students[0].score = 90.5;

    students[1].student_id = 2;
    strcpy(students[1].name, "李四");
    students[1].score = 85.0;

    students[2].student_id = 3;
    strcpy(students[2].name, "王五");
    students[2].score = 92.0;

    int choice;
    int continueFlag = 1;

    while (continueFlag) {
        printf("\n主菜单\n");
        printf("1. 按学号查询任一同学成绩\n");
        printf("2. 按姓名查询任一同学成绩\n");
        printf("3. 退出\n");
        printf("请选择操作：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchStudentScore(students, numStudents, 1);
                break;

            case 2:
                searchStudentScore(students, numStudents, 2);
                break;

            case 3:
                continueFlag = 0;
                break;

            default:
                printf("无效的选择，请重新输入。\n");
                break;
        }
    }

    return 0;
}
