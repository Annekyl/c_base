#include <stdio.h>
#include <malloc.h>//加载malloc()函数库
#define LEN sizeof(struct Student) //确定Student 结构体长度

struct Student//结构体
{
    int num;//序号
    unsigned int student_num;//学号
    char name[5];//姓名
    int grade;//成绩
    struct Student *next;//结构体指针
};

int n;
int grades[162]={0};

struct Student* create(){
    FILE *fp;
    char words[35];//35长度的单元格装一行的内容
    struct Student *head,*p1,*p2;// struct Student的指针
    n=0;
    fp= fopen("D:\编程学习\实验室\C语言\课程\第02课结构体指针文件\成绩.txt","r");//打开文件
    fgets(words,35,fp);
    p1=p2=(struct Student*)malloc(LEN);//动态储存区地址
    head=NULL;
    if( sscanf(words, "%d\t%u\t%7s\t%d", &p1->num, &p1->student_num, p1->name, &p1->grade)==4)
    {
//        sscanf(words, "%d\t%u\t%7s\t%d", &p1->num, &p1->student_num, p1->name, &p1->grade);//name字符串组本身就是地址，无&
        printf("%d\t%u\t%s\t%d\n", p1->num, p1->student_num, p1->name, p1->grade);
        grades[n]=p1->grade;
    }
    do{
        n++;
        if(n==1)head=p1;
        else p2->next=p1;
        p2=p1;
        p1=(struct Student*)malloc(LEN);//开辟新的储存区
        fgets(words,30,fp);
        if( sscanf(words, "%d\t%u\t%7s\t%d", &p1->num, &p1->student_num, p1->name, &p1->grade)==4)
        {
            printf("%d\t%u\t%s\t%d\n", p1->num, p1->student_num, p1->name, p1->grade);
            grades[n]=p1->grade;
        }
    }while(p2->num!=162);
    p2->next=NULL;
    fclose(fp);//关闭文件
    return (head);

};
void print2(struct Student *head)
{
    struct Student *p1;
    unsigned int sum=0;
    p1=head;
    if (p1!=NULL)
    {
        do{
            sum+=p1->grade;
            if(p1->grade==grades[0])
            {
                printf("最高分：学号：%u\n\t姓名：%s\n\t成绩：%d", p1->student_num, p1->name, p1->grade);
                printf("\n");
            }
            if(p1->grade==grades[161])
            {
                printf("最低分：学号：%u\n\t姓名：%s\n\t成绩：%d", p1->student_num, p1->name, p1->grade);
                printf("\n");
            }
            p1=p1->next;
        }while(p1!=NULL);
        printf("平均分：%.2f",(float)sum/162);
        printf("\n");
    }
};

int compare(int ls[])
{
    int length = 0;
    int i,j,x1,x2,s=0;
    length = 162;
    for(i=0;i<length-1;i++)//7次
    {
        for(j=0;j<length-1-i;j++)//每次从第一项开始
        {
            if(ls[j]<ls[j+1])//如果前一项比后一项小
            {
                x2=x2+1;
                x1=ls[j];
                ls[j]=ls[j+1];
                ls[j+1]=x1;
            }
        }

    }
//    for(s=0;s<length;s++)//打印数组
//    {
//        printf("%d,",ls[s]);
//    }
    return 0;
};
int main() {
    struct Student *pt;
    pt=create();//第一个表的地址
    compare(grades);
    print2(pt);
}
