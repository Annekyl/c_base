#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct Student) 

struct Student
{
    long num;
    char name[20];
    float score;
    float aver;
    struct Student *next;
};

struct Student *createLinkedList()//动态链表 +读取文本文件 
{
	//打开文件 
    FILE *file;
	file = fopen("成绩.txt", "r");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return NULL;
    }
    /* 
    //显示文本文件里面的内容 
    char word;
    while ((word = fgetc(file)) != EOF)//逐字符读取文件内容，知道文件结尾 
    { 
		printf("%c", word);
	}
	*/ 
	struct Student *head = NULL; 
	char line[100];  //用于储存文件中的每一行 
	
    while (fgets(line, 100, file) != NULL)//逐行读取文件内容 
	{
		struct Student *newNode;
        newNode = (struct Student *)malloc(LEN);  //开辟新单元 
        
        if (newNode == NULL)
        {
        	printf("内存分配失败\n");
        	return NULL;
		}
		
        if(sscanf(line, "%ld %s %f", &newNode->num, newNode->name, &newNode->score) == 3)
    	//sscanf是在字符串line里面按格式读取长型整数、字符串、浮点数三个参数并储存在变量中。
    	{
    		newNode->next = head;
        	head = newNode;   
		} 
		else
        {
            free(newNode); //释放没成功分配并加入链表的结点内存
            break;
        }
    }
    fclose(file);
    return head;
}

void freeLinkedList(struct Student *head)
{
	struct Student *current = head;
	
	while(current != NULL)
	{
		struct Student *temp = current;
		current = current->next;
		free(temp); 
	}
}

void calculateTotalAverage(struct Student *head)
{
	float sum = 0;
	int count = 0;
	struct Student *current = head;
	
	while(current !=NULL)
	{
		sum += current->score;
		count++;
		current = current->next;
	}
	float totalAverage = sum / count;
    printf("总平均成绩是：%.1f\n", totalAverage);
}

void print(struct Student *student)
{
	if (student == NULL)
	{
		printf("链表为空\n");
		return;
	}
	
    struct Student *current = student;
    float maxScore = current->score;  // 定义最高分
	float minScore = current->score;  // 定义最低分 
	
    while (current != NULL)
    {
        if (current->score > maxScore)  //找最高分 
        {
            maxScore = current->score;
        }
        if (current->score < minScore)  //找最低分 
        {
            minScore = current->score;
        }
        current = current->next;
    }
    
	//找最高分和最低分的学生 
	current = student;
	while(current != NULL)
	{
		if (current->score == maxScore)
		{
			// 打印成绩最高的学生信息
	    	printf("成绩最高的学生有：%s\n", current->name);
	    	printf("学号：%ld\n姓名：%s\n成绩：%.1f\n", current->num, current->name, current->score);
		}
		
		if (current->score == minScore)	
	    {
	    	// 打印成绩最低的学生信息
	    	printf("成绩最低的学生有：%s\n", current->name);
	    	printf("学号：%ld\n姓名：%s\n成绩：%.1f\n", current->num, current->name, current->score);
		}
		
		current = current->next;
	}
}

int main()
{
    struct Student *head = createLinkedList();
    if (head == NULL)
    {
        return 1;
    }
    print(head);
    calculateTotalAverage(head);
    freeLinkedList(head);
    return 0;
}
