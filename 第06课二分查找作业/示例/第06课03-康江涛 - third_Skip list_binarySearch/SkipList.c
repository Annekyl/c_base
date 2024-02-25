#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
      char num1[10];  // 序号
      int num2;  // 学号
      char name[20]; // 名字.
      char sex[5];   //性别
      char class[20]; // 班级
      int score1;  //成绩一
      int score2;  // 成绩二
      int score3;  // 成绩三
      int average_score;    // 平均成绩
      struct Node *next;   // 链表指针
};

struct SkipList{
    struct Node * everylist[20];
   // int index;
};
int n;

struct SkipList * createSkipList(struct Node *students,int line_num){
    int i = line_num; // 记录行数
    int j=0; // 记录存储的是第几层
    struct SkipList * skiplist;
    skiplist = (struct SkipList *)malloc(sizeof(struct SkipList));
    skiplist->everylist[0] = students; //跳表第一个数据是在我们的最底层
    struct Node * temp = (struct Node*)malloc(sizeof(struct Node));
    temp = students;
    //printf("temp->next%s,temp->next->next%s\n",temp->next->name,temp->next->next->name);
    //printList(temp);
    
    while(i>=3){
        j++;
        i = i/2;  // 每次都除2就是让我们的跳表每一层数据都减半
        int now = i;
        struct Node *head;  // 链表头
        struct Node *p2;  // 用来循环创建链表
        p2 =(struct Node*)malloc(sizeof(struct Node));
        //p1 = temp;
        //printList(p1);
        head = NULL;
        while(temp->next != NULL && now > 0){
            struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
            memcpy(newNode,temp,sizeof(struct Node));
            if(now == i) head = newNode;
            else p2->next = newNode;
            p2 = newNode;
            temp = temp->next->next;
            //printList(head);
            now--;
        }
        temp = head;
        skiplist->everylist[j] = temp;
    }
    return skiplist;
}

// 打印链表
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d-%s-%s-%s-%d-%d-%d-%d\n",current->num2,current->name,current->sex,current->class,current->score1,current->score2,current->score3,current->average_score);
        current = current->next;
    }
    printf("NULL\n");
}

struct Node* Read(int target,const char *file_path){
    char data_array[100][50]; // 用来存储文件中一行中逗号分隔的数据
    int index = 0;  // 索引用来辅助文件中的数据放到data列表
    const char delimiters[] = ","; // 将数据用逗号分隔开
    int just =0 ; //判断读取到的行数
    char buffer[256]; // 装读取到文件的数据
    struct Node *content = (struct Node*)malloc(sizeof(struct Node)); //定义一个结构体

    FILE *file = fopen(file_path,"r+"); // 文件指针
    if(file ==NULL){
        perror("Error opening file");
    }  // 判断文件是否读取成功
    while(fgets(buffer,sizeof(buffer),file) != NULL){  // 一行一行读取文件
        just++;  
        if(just==target){  // 判断是否是目标行
            char *token = strtok((char*)buffer,delimiters); // 使用这个将数据按逗号分隔开
            while(token != NULL){  // 
                strcpy(data_array[index],token);
                index++;
                token = strtok(NULL,delimiters);  // 将逗号分隔开的数据存储到data中
            }
        }
    }
   // printf("data:%s",data_array[1]);
    strcpy(content->num1,data_array[0]);
    int i =atoi(data_array[1]);
    content->num2 = i;
    //printf("data2:%s",data_array[1]);
    strcpy(content->name,data_array[2]);
    strcpy(content->sex,data_array[3]);
    strcpy(content->class,data_array[4]);
    int a,b,c,d;
    a = atoi(data_array[5]);
    content->score1 = a;
    b = atoi(data_array[6]);
    content->score2 = b;
    c = atoi(data_array[7]);
    content->score3 = c;
    d = atoi(data_array[8]);
    content->average_score = d;
    fclose(file);
    return content;  // 返回节点
}


struct Node *create(const char *file_path,int line_num){
    struct Node *head;  // 链表头
    struct Node *p1,*p2;  // 用来循环创建链表
    n = 2 ; // 因为第一行是空行所以从2开始
    p1 = p2 =(struct Node*)malloc(sizeof(struct Node));
    p1 = Read(n,file_path); // p1赋值
    head=NULL;
    // 创建链表的操作.
    while(n<=line_num){
        //printf("%d",n);
        n++;
        if(n == 3)head = p1;
            else p2->next = p1;
        p2 = p1;
        p1 = (struct Node *)malloc(sizeof(struct Node));
        p1 = Read(n,file_path);
        p1->next = NULL;
    }
    return (head);
}

// 插入排序，按照节点数据从小到大排序
void insertSort_num2(struct Node** head) {
    struct Node *sorted, *unsorted, *temp;

    sorted = NULL;
    unsorted = *head;

    while (unsorted != NULL) {
        temp = unsorted;
        unsorted = unsorted->next;

        if (sorted == NULL || sorted->num2 > temp->num2) {
            // 如果排序链表为空，或者当前节点的数据小于已排序链表的头节点
            temp->next = sorted;
            sorted = temp;
        } else {
            // 在已排序链表中找到适当位置插入
            struct Node* current = sorted;
            while (current->next != NULL && current->next->num2 < temp->num2) {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }

    *head = sorted;
}

void insertSort_average_score(struct Node** head) {
    struct Node *sorted, *unsorted, *temp;

    sorted = NULL;
    unsorted = *head;

    while (unsorted != NULL) {
        temp = unsorted;
        unsorted = unsorted->next;

        if (sorted == NULL || sorted->average_score > temp->average_score) {
            // 如果排序链表为空，或者当前节点的数据小于已排序链表的头节点
            temp->next = sorted;
            sorted = temp;
        } else {
            // 在已排序链表中找到适当位置插入
            struct Node* current = sorted;
            while (current->next != NULL && current->next->average_score < temp->average_score) {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }

    *head = sorted;
}

void insertSort_name(struct Node** head) {
    struct Node *sorted, *unsorted, *temp;

    sorted = NULL;
    unsorted = *head;

    while (unsorted != NULL) {
        temp = unsorted;
        unsorted = unsorted->next;

        if (sorted == NULL || strcmp(sorted->name,temp->name) > 0) {
            // 如果排序链表为空，或者当前节点的数据小于已排序链表的头节点
            temp->next = sorted;
            sorted = temp;
        } else {
            // 在已排序链表中找到适当位置插入
            struct Node* current = sorted;
            while (current->next != NULL && strcmp(current->next->name,temp->name) < 0) {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
    *head = sorted;
}

struct Node * binary_search_num2(struct SkipList * skiplist, int input){
    int i = 7; // 跳表层数
    //printList(skiplist->everylist[i]);
    struct Node * empty = {0};
    while(i>=0){
        struct Node* current = skiplist->everylist[i];
        //printList(current);
        while(current != NULL){
            if(current->num2 == input) return current;
            else if(current->num2 < input) current = current->next;
            else if(current->num2 > input) break; 
            }
        i--;
    }
    return empty;
}

struct Node * binary_search_average_score(struct SkipList * skiplist, int input){
    int i = 7; // 跳表层数
    //printList(skiplist->everylist[i]);
    struct Node * empty = {0};
    while(i>=0){
        struct Node* current = skiplist->everylist[i];
        //printList(current);
        while(current != NULL){
            if(current->average_score == input) return current;
            else if(current->average_score < input) current = current->next;
            else if(current->average_score > input) break; 
            }
        i--;
    }
    return empty;
}

struct Node * binary_search_name(struct SkipList * skiplist, char input[]){
    int i = 7; // 跳表层数
    //printList(skiplist->everylist[i]);
    struct Node * empty = {0};
    while(i>=0){
        struct Node* current = skiplist->everylist[i];
        //printList(current);
        while(current != NULL){
            if(strcmp(current->name,input) == 0) return current;
            else if(strcmp(current->name,input) < 0) current = current->next;
            else if(strcmp(current->name,input) > 0) break; 
            }
        i--;
    }
    return empty;
}

int main() {
    int line_num = 374;
    struct Node * students;
    char file_path[20] ="score.txt";
    students = create(file_path,line_num);
    insertSort_num2(&students);  // 改这个先 insertSort_name ,insertSort_num2(学号),insertSort_average_score
    printList(students);

    struct SkipList * skiplist;
    skiplist = (struct SkipList *)malloc(sizeof(struct SkipList));
    skiplist = createSkipList(students,line_num);
    //printList(skiplist->everylist[7]);

    //这是按照学号排序的过程
    int input;
    printf("请输入学号:");
    scanf("%d",&input);
    struct Node * output;
    output = binary_search_num2(skiplist,input);
    printf("学号:%d,姓名:%s,性别:%s,班级:%s,成绩1:%d,成绩2:%d,成绩3:%d,平均成绩:%d\n",output->num2,output->name,output->sex,output->class,output->score1,output->score2,output->score3,output->average_score);
    return 0;

    // 按照平均成绩
    // int input;
    // printf("请输入要查询的平均成绩:");
    // scanf("%d",&input);
    // struct Node * output;
    // output = binary_search_average_score(skiplist,input);
    // while(students != NULL){
    //     if(students->average_score == output->average_score){
    //         printf("学号:%d,姓名:%s,性别:%s,班级:%s,成绩1:%d,成绩2:%d,成绩3:%d,平均成绩:%d\n",students->num2,students->name,students->sex,students->class,students->score1,students->score2,students->score3,students->average_score);
    //     }
    //     students = students->next;
    // }
    // //printf("学号:%d,姓名:%s,性别:%s,班级:%s,成绩1:%d,成绩2:%d,成绩3:%d,平均成绩:%d\n",output->num2,output->name,output->sex,output->class,output->score1,output->score2,output->score3,output->average_score);
    // return 0;

    // 按照姓名
    // char input[20];
    // printf("输入你要查找的学生的姓名:");
    // scanf("%s",input);
    // struct Node * output;
    // output = binary_search_name(skiplist,input);
    // printf("学号:%d,姓名:%s,性别:%s,班级:%s,成绩1:%d,成绩2:%d,成绩3:%d,平均成绩:%d\n",output->num2,output->name,output->sex,output->class,output->score1,output->score2,output->score3,output->average_score);
    // return 0;
}
