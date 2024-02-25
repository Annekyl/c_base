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

struct Student *createLinkedList()//��̬���� +��ȡ�ı��ļ� 
{
	//���ļ� 
    FILE *file;
	file = fopen("�ɼ�.txt", "r");
    if (file == NULL)
    {
        printf("�޷����ļ�\n");
        return NULL;
    }
    /* 
    //��ʾ�ı��ļ���������� 
    char word;
    while ((word = fgetc(file)) != EOF)//���ַ���ȡ�ļ����ݣ�֪���ļ���β 
    { 
		printf("%c", word);
	}
	*/ 
	struct Student *head = NULL; 
	char line[100];  //���ڴ����ļ��е�ÿһ�� 
	
    while (fgets(line, 100, file) != NULL)//���ж�ȡ�ļ����� 
	{
		struct Student *newNode;
        newNode = (struct Student *)malloc(LEN);  //�����µ�Ԫ 
        
        if (newNode == NULL)
        {
        	printf("�ڴ����ʧ��\n");
        	return NULL;
		}
		
        if(sscanf(line, "%ld %s %f", &newNode->num, newNode->name, &newNode->score) == 3)
    	//sscanf�����ַ���line���水��ʽ��ȡ�����������ַ��������������������������ڱ����С�
    	{
    		newNode->next = head;
        	head = newNode;   
		} 
		else
        {
            free(newNode); //�ͷ�û�ɹ����䲢��������Ľ���ڴ�
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
    printf("��ƽ���ɼ��ǣ�%.1f\n", totalAverage);
}

void print(struct Student *student)
{
	if (student == NULL)
	{
		printf("����Ϊ��\n");
		return;
	}
	
    struct Student *current = student;
    float maxScore = current->score;  // ������߷�
	float minScore = current->score;  // ������ͷ� 
	
    while (current != NULL)
    {
        if (current->score > maxScore)  //����߷� 
        {
            maxScore = current->score;
        }
        if (current->score < minScore)  //����ͷ� 
        {
            minScore = current->score;
        }
        current = current->next;
    }
    
	//����߷ֺ���ͷֵ�ѧ�� 
	current = student;
	while(current != NULL)
	{
		if (current->score == maxScore)
		{
			// ��ӡ�ɼ���ߵ�ѧ����Ϣ
	    	printf("�ɼ���ߵ�ѧ���У�%s\n", current->name);
	    	printf("ѧ�ţ�%ld\n������%s\n�ɼ���%.1f\n", current->num, current->name, current->score);
		}
		
		if (current->score == minScore)	
	    {
	    	// ��ӡ�ɼ���͵�ѧ����Ϣ
	    	printf("�ɼ���͵�ѧ���У�%s\n", current->name);
	    	printf("ѧ�ţ�%ld\n������%s\n�ɼ���%.1f\n", current->num, current->name, current->score);
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
