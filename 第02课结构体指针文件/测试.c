//
// Created by 30694 on 2024/1/19.
//

#include <stdio.h>
#include "stdlib.h"

#define LEN sizeof(struct Student)
struct Student {
    int order;  //���
    int number;  //ѧ��
    char name[12];  //����
    int grade;  //�ɼ�
    struct Student *next;
};

int n;

struct Student *creat() {
    // �������
    FILE *file;
    char line[100];
    struct Student *head = NULL;
    struct Student *p1, *p2;
    n = 0;

    // ��txt�ļ�
    file = fopen("�ɼ�.txt","r");
    if(file == NULL){
        printf("�޷����ļ�\n");
        return(head);
    }

    //���ж�ȡѧ�����ݲ���������
    p1 = p2 = (struct Student *) malloc(LEN);//p2���ڱ���ǰһ��ѧ����p1���ڿ����¿ռ�
    while (fgets(line, sizeof(line),file)) {
        sscanf_s(line,"%d %d %s %d", &p1->order, &p1->number, p1->name, &p1->grade);
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

    printf("���\tѧ��\t����\t�ɼ�\n");
    while (current != NULL) {
        printf("%d\t%d\t%s\t%d\n", current->order, current->number, current->name, current->grade);
        current = current->next;
    }
}

int main() {
    struct Student *pt;
    pt=creat();

    return 0;
}