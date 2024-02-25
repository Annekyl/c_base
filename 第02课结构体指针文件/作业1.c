//
// Created by 30694 on 2024/1/19.
//
#include <stdio.h>
#include "stdlib.h"

#define LEN sizeof(struct Student)
struct Student {
    int order;  //���
    int number;  //ѧ��
    char name[20];  //����
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
    file = fopen("�ɼ�.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return (head);
    }

    //���ж�ȡѧ�����ݲ���������
    p1 = p2 = (struct Student *) malloc(LEN);//p2���ڱ���ǰһ��ѧ����p1���ڿ����¿ռ�
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
    // �������
    float total_num = 0;  //������
    float total_grade = 0;  //�ܳɼ�
    float average_grade;  //ƽ���ɼ�
    int max_grade;
    char max_name[20];
    int max_number;
    int min_grade;
    char min_name[20];
    int min_number;
    struct Student *pt;
    struct Student *current;
    int a=0;
    //��ȡѧ������
    pt = creat();

    //��ȡѧ������
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
    printf("ƽ���ɼ�Ϊ��%f\n",average_grade);
    printf("��߷�:%d,����:%s,ѧ��:%d\n",max_grade,max_name,max_number);
    printf("��ͷ�:%d,����:%s,ѧ��:%d\n",min_grade,min_name,min_number);

    return 0;
}