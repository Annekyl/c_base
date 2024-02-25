#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct student {
	int xu;
	char id[30];
	char name[50];
	char gender[5];
	char class[50];
	int score1;
	int score2;
	int score3;
	int average_score;
	struct student* next;//����������һԪ��
	struct student* under;//�����²�����
};


struct student read(FILE* file) {//��һ������
	struct student Stu;//����һ��ѧ��
	memset(&Stu, 0, sizeof(struct student));//���ṹ������������Ϊ�㣬 ���㴦��ȱ����Ա
	char ch[100];
	fgets(ch, 100, file);
	sscanf(ch, "%d %s %s %s %s %d %d %d", &Stu.xu, &Stu.id, Stu.name, Stu.gender, Stu.class, &Stu.score1, &Stu.score2, &Stu.score3);
	Stu.average_score = (Stu.score1 + Stu.score2 + Stu.score3) / 3;//ƽ���ɼ�
	return Stu;
}

struct student* p;//д�������ָ��
int j = 0;//��¼ѧ������
FILE* open(const char file_name[], char x[]) {
	FILE* file;
	file = NULL;
	file = fopen(file_name, x);
	if (file == NULL) {
		printf("���ļ�ʧ��\n");
	}
	else {
		printf("���ļ��ɹ�\n");
	}
	return file;
}

struct student* daoru(FILE* file) {
	struct student* head = NULL;
	struct student* p1, * p2;
	p1 = NULL;
	p2 = NULL;
	while (!feof(file)) {
		if (j == 0) {//��������ͷ
			p1 = (struct student*)malloc(sizeof(struct student));
			*p1 = read(file);//Ϊ����ֵ
			p1->under = NULL;//���²���Ϊ����Ϊ����ѭ���ĳ���
			head = p1;//����ͷָ��
			p2 = p1;
			j++;
			continue;
		}	
		p1 = (struct student*)malloc(sizeof(struct student));
		*p1 = read(file);
		p2->next = p1;
		p2 = p1;
		j++;
	}
	p2->next = NULL;
	p2 = NULL;
	p1 = NULL;
	return head;
}
struct student* write_list(struct student* head) {//�����������
	int ls = j;//��¼�²������Ԫ�ص�����, ���, �������, �²������ӽ�����ֹͣ
	struct student *p1 = head;
	struct student *p2 = p1;//��̬�����ϲ�����
	struct student* p3 = NULL;
	int x;
	srand(time(0));
	while (ls > 2) {//���ڶ���ֹͣ
		ls = 0;//����Ԫ��������ֵ
		p2 = head;//���¸߶�
		p1 = (struct student*)malloc(sizeof(struct student));
		*p1 = *head;//����ͷ������
		p1->under = p2;

		p2  = p2 -> next;//��������
		head = p1;//�ı����
		p3 = p1;//�ϲ�ڵ�
		ls++;
		while (p2 ->next != NULL) {
			x = rand() % 2;//����0��1
			if (x > 0) {//�����ϴ�����
				p1 = (struct student*)malloc(sizeof(struct student));
				*p1 = *p2;//��ֵ
				p1->under = p2;
				p3->next = p1;
				p3 = p1;
				ls++;
			}
			p2 = p2->next;
		}
	p1 = (struct student*)malloc(sizeof(struct student));
	*p1 = *p2;
	p1->under = p2;
	p3->next = p1;
	ls++;
	}
	return head;
}
void kaichang(void) {
	printf("��ӭ����ѧ����Ϣ��ѯϵͳ\n");
	printf("Ŀǰ�Ѵ洢%d��ѧ����Ϣ\n", j);
}
FILE* inser(const char x[], char a[]) {
	FILE* file;
	char ch[100];
	file = open(x, a);
	return file;
}
int id_seek(struct student *head, char ch[]) {
	struct student* p1;
	p1 = head;
	struct student* p2;
	p2 = head;
	struct student* p3;
	p3 = head;
	int x = 0;
	if (strcmp(ch, p1->id) < 0) {
		printf("��ѧ��������\n");
		return 0;
	}
	while (p1 != NULL) {
		p2 = p1;
		x = 0;
		while (p2 != NULL) {

			if(strcmp(ch, p2->id)  ==  0) {
				printf("ѧ��      ����   �Ա� ������    ����ת�� �����ת�� ��ֵ����߼����� ƽ����\n");
				printf("%s %s %s   %s %d       %d         %d               %d\n", p2->id, p2->name, p2->gender, p2->class, p2->score1, p2->score2, p2->score3, p2->average_score);
				return 1;
			}
			if (strcmp(ch, p2->id) < 0) {
				//printf("%s %s %s   %s %d       %d         %d               %d\n", p2->id, p2->name, p2->gender, p2->class, p2->score1, p2->score2, p2->score3, p2->average_score);
				break;
			}
			if(x > 1)
			   p1 = p1->next;//��������Ŀ������
			p2 = p2->next;
			x++;
		}
		p1 = p1->under;
	}
	printf("��ѧ��������\n");
	return 0;
}
void clear(struct student* head) {
	struct student* ps = head;
	while(ps != NULL){
		struct student* st = ps;
		ps = ps->under;
		while (st != NULL)
		{
			struct student* ts = st;
			st = st->next;
			free(ts);
		}
		st = ps;
	}
	printf("�ڴ�������\n");
}
int main() {
	FILE* file = inser("filee.txt", "r");
	read(file);
	char ch[100];
	struct student *head = daoru(file);//������Ͳ������
	fclose(file);
	file = NULL;//�ÿ�ָ��
	head = write_list(head);
	kaichang();
	printf("������ѧ��ѧ�Ž��в�ѯ/����exit�˳�\n");
	scanf("%s", ch);
	while (strcmp(ch, "exit") != 0) {
		id_seek(head, ch);
		scanf("%s", ch);
	}
	clear(head);//�����̬���ڴ�
	return 0;
}
