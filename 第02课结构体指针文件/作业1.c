//
// Created by 30694 on 2024/1/19.
//
#include <stdio.h>
#include "stdlib.h"

#define LEN sizeof(struct Student)
struct Student {
    int order;  //序号
    int number;  //学号
    char name[20];  //姓名
    int grade;  //成绩
    struct Student *next;
};

int n;

struct Student *creat() {
    // 定义变量
    FILE *file;
    char line[100];
    struct Student *head = NULL;
    struct Student *p1, *p2;
    n = 0;

    // 打开txt文件
    file = fopen("成绩.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return (head);
    }

    //逐行读取学生数据并创建链表
    p1 = p2 = (struct Student *) malloc(LEN);//p2用于保留前一个学生，p1用于开辟新空间
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %d %s %d", &p1->order, &p1->number, &p1->name, &p1->grade);
        n = n + 1;
        if (n == 1)head = p1;
        else p2->next = p1;
        p2 = p1;
        p1 = (struct Student *) malloc(LEN);
    }
    p2->next = NULL;
    fclose(file);
    return (head);
}

int main() {
    // 定义变量
    float total_num = 0;  //总人数
    float total_grade = 0;  //总成绩
    float average_grade;  //平均成绩
    int max_grade;
    char max_name[20];
    int max_number;
    int min_grade;
    char min_name[20];
    int min_number;
    struct Student *pt;
    struct Student *current;
    int a=0;
    //获取学生链表
    pt = creat();

    //读取学生链表
    current = pt;
    while (current != NULL) {
        a++;
        if(a==1){
            max_grade=current->grade;
            max_number=current->number;
            for (int i = 0; i < 20; ++i) max_name[i]=current->name[i];
            min_grade=current->grade;
            min_number=current->number;
            for (int i = 0; i < 20; ++i) min_name[i]=current->name[i];

        }
        if(max_grade<current->grade){
            max_grade=current->grade;
            max_number=current->number;
            for (int i = 0; i < 20; ++i) max_name[i]=current->name[i];
        }
        if(min_grade>current->grade){
            min_grade=current->grade;
            min_number=current->number;
            for (int i = 0; i < 20; ++i) min_name[i]=current->name[i];
        }
        total_num++;
        total_grade += current->grade;

        current = current->next;
    }

    average_grade = total_grade / total_num;
    printf("平均成绩为：%f\n",average_grade);
    printf("最高分:%d,姓名:%s,学号:%d\n",max_grade,max_name,max_number);
    printf("最低分:%d,姓名:%s,学号:%d\n",min_grade,min_name,min_number);

    return 0;
}