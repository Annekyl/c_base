#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
struct Student{
    int num;//序号
    int st_num;//学号
    char name[20];//姓名
    char sex[20];//性别
    char class[30];//行政班
    int grade1;//
    int grade2;//
    int grade3;//
    int average;//平均
    int leval;//索引等级

};
struct Sp_student{//表单
    struct Student st;
    struct Sp_student* p[];
};


bool SL[373];//是否分配内存
bool print=false;//表头打印
struct Student students[373];//数组排序用
struct Student x;
struct Sp_student *sp_students[373];//指针数组构建跳表用
int n=0;

char word_0[9][25]={{"序号"},{"学号"},{"姓名"},{"性别"},{"行政班"},{"进制转换"},{"多进制转换"},{"数值表达逻辑代数"},{"平均分"}};//表头
char E[100];//键盘获取数据
int k;//学号

int sl[6]={1,5,10,20,40,80};//跳表分级
void SL_0(int s){//初始化
    for(int i=0;i<s;i++){
        SL[i]=false;
    }
}
void SL_Leval(int s){//确定每张表的索引层级
    for(int i=0;i<s;i++){
        students[i].leval=0;
        for(int y=0;y<6;y++) {
            if (i % sl[y] == 0) {
                students[i].leval += 1;
            }
        }
    }
}

void Malloc(int j){//管理内存分配
    if(!SL[j]){
        sp_students[j]= (struct Sp_student*)malloc(sizeof (struct Sp_student)+students[j].leval*sizeof (struct Student*));
        sp_students[j]->st=students[j];
        SL[j]=true;//已经分配内存
    }
    else{
        return;
    }
}

void Print(struct Sp_student*p) {//打印输出
    if(!print){//表头只打印一次
        printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
               word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
        print=true;
    }
    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", p->st.num,
           p->st.st_num, p->st.name, p->st.sex, p->st.class,
           p->st.grade1, p->st.grade2, p->st.grade3,
           p->st.average);
}
void StructLSCreate(char *str) {//读取文本构建数组
    char words[200];//单行数据存放
    FILE *fp = fopen(str, "r");//打开文件
    while (fgets(words, 200, fp) != NULL) {//单行读取
//        printf("%s",words);
        if (sscanf(words, "%d %d %s %s %s %d %d %d %d", &students[n].num, &students[n].st_num,//读取格式化数据
                   students[n].name, students[n].sex, students[n].class, &students[n].grade1, &students[n].grade2,
                   &students[n].grade3, &students[n].average) == 9) {
            students[n].leval=0;
//            printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[n].num,students[n].st_num,students[n].name,students[n].sex,students[n].class,students[n].grade1,students[n].grade2,students[n].grade3,students[n].average);
            n++;
        }
//        else{
//            printf("%s",words);
//        }
    }
//    printf("\n%d\n",n);
    fclose(fp);
}
void Compare1(int l) {//数组按学号排序
    int f;
    for (int i = 0; i < l; i++) {//l=372
        f = i;
        for (int j = i + 1; j < l+1; j++) {//l+1=373
            if (students[f].st_num > students[j].st_num)
                f = j;
        }
        x = students[i];
        students[i] = students[f];
        students[f] = x;
    }
    SL_Leval(l);
//    for(int i=0;i<373;i++){
//        printf("%d，%d，%s，%s，%s，%d，%d，%d，%d，%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average,students[i].leval);
//    }
}

void Compare2(int l){//姓名排序
    int f;
    int result;
    setlocale(LC_COLLATE,"zh_CN.GBK");//本地化字符串排序
    for(int i=0;i<l;i++){
        f=i;
        for(int j=i+1;j<l+1;j++){
            result= strcoll(students[f].name,students[j].name);
            if(result>0)//students[f].name>students[j].name
                f=j;
        }
        x=students[i];
        students[i]=students[f];
        students[f]=x;
    }
    SL_Leval(l);
//    for(int i=0;i<373;i++){
//        printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}

void Compare3(int l){//平均分排序
    int f;
    for(int i=0;i<l;i++){
        f=i;
        for(int j=i+1;j<l+1;j++){
            if(students[f].average>students[j].average)
                f=j;
        }
        x=students[i];
        students[i]=students[f];
        students[f]=x;
        students[i].num=i;
    }
    students[l].num=l;
    SL_Leval(l);
//    for(int i=0;i<373;i++){
//        printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}

struct Sp_student* CreateList(int l){//创建六级索引跳表
    for(int i=0;i<6;i++){
        for(int j=0;j<l;j++){//l=372
            if(j%sl[i]==0){
                if(j+sl[i]>l){
                    Malloc(j);//按索引层级分配内存
                    Malloc(l);
                    sp_students[j]->p[i]=sp_students[l];//超出部分接到最后一张表

                }
                else{
                    Malloc(j);
                    Malloc(j+sl[i]);
                    sp_students[j]->p[i]=sp_students[j+sl[i]];
                }
            }
        }
    }
//    for(int i=0;i<6;i++){
//        printf("%s\n",sp_students[0]->p[i]->st.name);
//    }
    return sp_students[0];
}

void FindXue(struct Sp_student*head,struct Sp_student*tail){//跳表学号索引
    struct Sp_student*p=head;
    if(k<head->st.st_num || k>tail->st.st_num){//超出跳表头尾范围
        printf("没找到\n");
        return;
    }
    else{
        for(int i=0;i<6;i++){//六级索引
            while (1){
                if(p->st.st_num==k){//找到
                    print=false;
                    Print(p);
                    return;
                }
                if(p->p[5-i]->st.st_num>k){//下一位大于，降级查找
                    break;
                }
                if(p->p[5-i]->st.st_num<=k){//小于等于切到下一位
                    p=p->p[5-i];
                }
            }
        }
        printf("没找到\n");
        return;
    }
}

void FindName(struct Sp_student*head,struct Sp_student*tail){//姓名
    struct Sp_student*p=head;
    if(strcoll(E,head->st.name)<0|| strcoll(E,tail->st.name)>0){
        printf("没找到~~~\n");
        return;
    }
    else{
        for(int i=0;i<6;i++){
            while (1){
                if(strcoll(p->st.name,E)==0){
                    print=false;
                    Print(p);
                    return;
                }
                if(strcoll((p->p[5-i])->st.name,E)>0){
                    break;
                }

                if(strcoll((p->p[5-i])->st.name,E)<=0){
                    p=p->p[5-i];
                }

            }
        }
        printf("真没找到\n");
        return;
    }

}

void AveForward(int l){//跳表找到第一个平均分，递归查询平均分相同的
    if(students[l-1].average!=students[l].average || l-1<=0){
        return;
    }
    Print(sp_students[l-2]->p[0]);
    AveForward(l-1);
}

void AveBack(int l) {//递归查询平均分相同的
    if (students[l + 1].average != students[l].average || l >= 372) {
        return;
    }
    Print(sp_students[l]->p[0]);
    AveBack(l + 1);
}

void FindAverage(struct Sp_student*head,struct Sp_student*tail){//跳表查询平均分
    struct Sp_student*p=head;
    if(k<head->st.average || k>tail->st.average){
        printf("没找到\n");
        return;
    }
    else{
        for(int i=0;i<6;i++){
            while (1){
                if(p->st.average==k){
                    print=false;
                    Print(p);
                    AveForward(p->st.num);
                    AveBack(p->st.num);
                    return;
                }
                if(p->p[5-i]->st.average>k){
                    break;
                }

                if(p->p[5-i]->st.average<=k){
                    p=p->p[5-i];
                }

            }
        }
        printf("没找到\n");
        return;
    }

}


int main() {
    int r=372;
    struct Sp_student*k1,*k2,*k3,*k4,*k5,*k6;
    StructLSCreate("./Grade.txt");//结构体数组
    //-----------------学号查找初始化
    Compare1(r);
    SL_0(r+1);
    k1=CreateList(r);
    k4=sp_students[r];
    //----------------姓名查找初始化
    Compare2(r);
    SL_0(r+1);
    k2= CreateList(r);
    k5=sp_students[r];
    //---------------平均分查找初始化
    Compare3(r);
    SL_0(r+1);
    k3= CreateList(r);
    k6=sp_students[r];

    while(1){
        printf("1.学号查询 2.姓名查询 3.平均分查询or按e退出\n");//界面
        gets(E);//数据输入
        if(E[0]=='e')
            break;//退出
        else if(E[0]=='1') {
            printf("输入学号查询\n");//界面
            gets(E);//数据输入
            k = atoi(E);
            FindXue(k1,k4);
        }
        else if(E[0]=='2'){
            printf("输入姓名查询\n");
            gets(E);
            FindName(k2,k5);
        }
        else if(E[0]=='3'){
            printf("输入平均分查询\n");
            gets(E);
            k= atoi(E);
            FindAverage(k3,k6);
        }

        else
            printf("错误从新输入\n");
    }

    return 0;
}