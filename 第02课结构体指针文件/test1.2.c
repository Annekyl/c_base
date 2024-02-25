//
// Created by 30694 on 2024/1/19.
//
#include <stdio.h>
#include "stdlib.h"

#define LEN sizeof(struct Student)
struct Student {
    int order;  //序号
    int number;  //学号
    char name[12];  //姓名
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
    file = fopen("成绩.txt","r");
    if(file == NULL){
        printf("无法打开文件\n");
        return(head);
    }

    //逐行读取学生数据并创建链表
    p1 = p2 = (struct Student *) malloc(LEN);//p2用于保留前一个学生，p1用于开辟新空间
    while (fgets(line, sizeof(line),file)) {
        sscanf_s(line,"%d %d %s %d", &p1->order, &p1->number, &p1->name, &p1->grade);
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

void printList(struct Student *head) {
    struct Student *current = head;

    printf("序号\t学号\t姓名\t成绩\n");
    while (current != NULL) {
        printf("%d\t%d\t%s\t%d\n", current->order, current->number, current->name, current->grade);
        current = current->next;
    }
}

int main() {
    struct Student *pt;
    pt=creat();
    printList(pt);
    return 0;
}