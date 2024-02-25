//https://blog.csdn.net/BLADCS/article/details/104933170
#include<stdio.h>
#include<stdlib.h>

typedef struct Node *list;
struct Node
{
	char data[1000];
	int pointer;
};

void Push(list s,char c)
{
	s->pointer++;
	s->data[s->pointer]=c;
}

char Pop(list s)
{
	if (s->pointer==-1)
		return 0;
	s->pointer--;
	return s->data[s->pointer+1];
}

int main()
{
	char str[20];
	int str_p=0;
	char ch;
	list ps;
	ps=(list)malloc(sizeof(struct Node));
	ps->pointer=-1;
	gets(str);
	
	while(str[str_p]!='\0')
	{
		ch=str[str_p];
		Push(ps,ch);
	}
	//system("pause");
	return 0;
}
