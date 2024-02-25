#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int num;
    int left;
    int right;
    int parent;
    char name[3];
}Node;  // 定义结构体指针

void input(int num[],int *length){
    int i;
    for(i=0;i<=100;i++){
        scanf("%d",&num[i]);
        (*length)++;
        if(num[i]==0) break;
    }
}

void output(int num[],int length){
    int i;
    for(i=0;i<length;i++) printf("%d ",num[i]);
    printf("\n");
}

void bubble_sort(int num[],int length){
    int i,j,low,low_position;
    for(i=0;i<length;i++){
        low=num[i];
        low_position=i;
        for(j=i+1;j<length;j++){
            if(low>num[j]){
                low=num[j];
                low_position=j;
            }
        }
        num[low_position]=num[i];
        num[i]=low;
    }
    output(num,length);
}

void createNode(int num,int left,int right,int parent,Node*p){
    p->left=left;
    p->num=num;
    p->right=right;
    p->parent=parent;
}

void printfNode(Node * p){
    printf("num:%d,left:%d,right:%d,parent:%d\n",p->num,p->left,p->right,p->parent);
}

void createHuffmantree(int num[],int length,Node *ps[]){
    int i,j;
    int current_num,current_left,current_right,current_parent;
    // 第一步先创建n个只有一个num的二叉树
    for(i=1;i<length;i++){
        createNode(num[i],0,0,0,ps[i-1]);
        //printfNode(ps[i-1]);
    }
    // 第二步逐渐创建出来新的节点换掉原来的节点
    // 方法就是用数组中的最小的两个创建出来新节点 总共创建n-1个
    createNode(num[1]+num[2],num[1],num[2],num[2+3]+num[1]+num[2],ps[length-1]);
    //printfNode(ps[length-1]); //创建第一个新节点 左右孩子都是原数组中的所以单拎出来创建
    createNode(num[3]+num[4],num[3],num[4],num[3]+num[4]+num[4+2],ps[length]);
    //printfNode(ps[length]); // 第二个新节点和第一个是同理 自己创建
    // 接下来就是使用循环创建后面的节点
    for(i=length+1;i<2*length-4;i++){
        j=i-length-1;
        current_num=num[j+5]+ps[i-2]->num;
        if((i-length+1)%2==0){
            current_left=ps[i-2]->num;
            current_right=num[j+5];
        } else {
            current_right=ps[i-2]->num;
            current_left=num[j+5];
        }
        current_parent=current_num+num[j+2+5];
        createNode(current_num,current_left,current_right,current_parent,ps[i]);
        // printfNode(ps[i]);
    }
    // 后三个节点也会不一样
    // 倒数第二，三个是因为父节点的超出数组范围而不正确
    ps[2*length-6]->parent = ps[2*length-5]->num + ps[2*length-6]->num;
    ps[2*length-5]->parent = ps[2*length-5]->num + ps[2*length-6]->num;
    // printfNode(ps[2*length-6]);
    // printfNode(ps[2*length-5]);
    // 最后一个节点
    createNode(ps[2*length-6]->num+ps[2*length-5]->num,ps[2*length-6]->num,ps[2*length-5]->num,0,ps[2*length-4]);
    // 打印出我们的全部节点 连接起来就可以构造出哈夫曼树
    for(i=2*length-4;i>=length-1;i--){
        printfNode(ps[i]);
    }
}

int main(){
    int num[100],length=0,i;
    input(num,&length);
    output(num,length);
    bubble_sort(num,length);

    Node *ps[2*length-1];
    for(i=0;i<2*length-1;i++) ps[i]=(Node*)malloc(sizeof(Node)); //为每一个ps中的节点分配空间
    createHuffmantree(num,length,ps);
    return 0;
}