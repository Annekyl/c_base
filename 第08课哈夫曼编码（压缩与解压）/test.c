//任务1：编程求解“三国演义”文档的权重文件的哈夫曼编码
//思路： 读取权重文件里的数字，存到数组里面（相当于创造权重数组）
//创建结构体类型为权重、父结点、左孩子、右孩子
//对哈夫曼树初始化，创建2*n-1个结构体，地址给ps，再根据数组把树初始化
//然后获取最大值最小值的下标，继续完成下面的哈夫曼树
//根据哈夫曼树构建编码

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>//用里面的isdigit函数

//创建结构体
typedef struct Node {
    char name[3];
    int weight;//结点权重
    int parent;//父结点号
    int lchild;//左孩子号
    int rchild;//右孩子号
} *stack;//同时创建了一个结构体类型的指针


//
int open(int leaf_weight[], FILE *fp1, FILE *fp2, char hanzi[][3]) {
    char ch;
    int number = 0, i = 0;
    if (NULL == fp1) //以返回值fp1判断是否打开成功，如果为NULL表示失败
    {
        printf("Failed to open the file1 !\n");
        exit(0); //终止程序，stdlib .h头文件中
    }
    if (NULL == fp2) {
        printf("Failed to open the file2 !\n");
        exit(0);//终止程序，stdlib .h头文件中
    }
    while (!feof(fp1))//文件结束：返回非0值；文件未结束：返回0值
    {
        ch = fgetc(fp1);//获取一个字符
        if (ch < 0 || ch == 92 || ch == 39)//包括汉字和换行和空格
        {
            hanzi[i][0] = ch;
            hanzi[i][1] = fgetc(fp1);
            hanzi[i][2] = '\0';
//			printf("%s\n",hanzi[i]);
//			ch=fgetc(fp1);//获取一个字符
        } else if (ch == 34 || ch == 45)//如果是英文的单引号或者是短横
        {
            hanzi[i][0] = ch;
            hanzi[i][1] = '\0';
        } else {
            if (isdigit(ch)) {
                while (isdigit(ch)) {
                    number = number * 10 + ch - '0';//得到一个字符的权重
                    ch = fgetc(fp1);
                }
            }
        }
        if (number != 0) {
            leaf_weight[i] = number;
            i++;
            number = 0;//单次读取完毕后归0
        }
    }
    return i;//得到权重数组和数组元素个数
}

//寻找最小值和次小值的下标函数
void compare(int *s1, int *s2, stack ps, int n) {
    int min1 = 9999999, min2 = 9999999, i;//首先把这两个赋值一个比较大的数值，方面下面的比较,这里一定要够大，因为真的还有那么大

    //获取最小值的下标
    for (i = 0; i < 2 * n - 1; i++) {
        if ((ps + i)->weight != 0 && (ps + i)->parent == -1)//如果当前权重不为NULL，并且父结点为NULL，就是孤结点
        {
            if (min1 > (ps + i)->weight) {
                *s1 = i;//获取下标
                min1 = (ps + i)->weight;//每次比较后获取较小值，进行下一次比较
            }
        }
    }
    //获取次小值的下标
    for (i = 0; i < 2 * n - 1; i++) {
        if ((ps + i)->weight != 0 && (ps + i)->parent == -1)//如果当前权重不为NULL，并且父结点为NULL，就是孤结点
        {
            if (min2 > (ps + i)->weight && i != *s1) {
                *s2 = i;//获取下标
                min2 = (ps + i)->weight;//每次比较后获取较小值，进行下一次比较
            }
        }
    }
//	printf("此次最小两个数的下标为：%d,%d\n", *s1,*s2);
}


//创建哈夫曼树初始化并填好
stack create(int leaf_weight[], char hanzi[][3], int n, stack ps, int *s1, int *s2) {
    int i;
    ps = (stack) malloc((2 * n - 1) * sizeof(struct Node));//创建2*n-1个结点
    //对哈夫曼树进行初始化
    for (i = 0; i < 2 * n - 1; i++) {
        ps[i].parent = ps[i].lchild = ps[i].rchild = -1;//初始化为-1
        if (i < n)//小于n时就赋值结点权重
        {
            ps[i].weight = leaf_weight[i];//把结点权重都存到数组里
            ps[i].name[0] = hanzi[i][0];
            ps[i].name[1] = hanzi[i][1];
            ps[i].name[2] = hanzi[i][2];
//			printf("ps[i].zifu:%s\n",ps[i].zifu);
        } else//大于0的都初始化为0
        {
            ps[i].weight = 0;
        }
    }
    for (i = n; i < 2 * n - 1; i++) {
        compare(s1, s2, ps, n);
        (ps + i)->weight = (ps + *s1)->weight + (ps + *s2)->weight;//该节点的权重=两个儿子的权重之和
        ps[*s2].parent = ps[*s1].parent = i;//儿子的父结点是该节点
        ps[i].lchild = *s1;//左儿子*s1
        ps[i].rchild = *s2;//右儿子*s2
    }
//	for(i=0;i<2*n-1;i++)
//	{
//		printf("第%d个结点权重、父结点号、左孩子号、右孩子号:\t%d\t%d\t%d\t%d\n",i,ps[i].weight,ps[i].parent,ps[i].lchild,ps[i].rchild);
//	}
    return ps;
}


//构建哈夫曼编码
char **coding(char **HufCode, int n, stack ps) {
    int i, flag, c, pp;
    char *tmp = (char *) malloc(n * sizeof(char));    //分配求当前编码的工作空间,节点的编码数不会超过结点总数
    HufCode = (char **) malloc(n * sizeof(char *));
    tmp[n - 1] = '\0';//从右向左逐位存放编码，首先存放编码结束符
    for (i = 0; i < n; i++)        //求n个叶子结点对应的哈夫曼编码
    {
        flag = n - 1;        //初始化编码位指针。每求出一个编码位，将存放在tmp[flag]中
        //从叶子到根结点求编码
        for (c = i, pp = ps[i].parent; pp != -1; c = pp, pp = ps[pp].parent) {
            if (ps[pp].lchild == c)
                tmp[--flag] = '0';  //左分支标0 ,从右到左的顺序编码入数组内
            else
                tmp[--flag] = '1';  //右分支标1
        }

        HufCode[i] = (char *) malloc((n - flag) * sizeof(char));//为第i个编码创建空间
        strcpy(HufCode[i], &tmp[flag]);//这里怎么使用的不太明白
//        printf("当前权重为：%s,保存的编码为：%s\n",ps[i].zifu,HufCode[i]);
    }
    free(tmp);
    return HufCode;        //释放临时空间
}

void display(char **HufCode, stack ps, FILE *fp2, int n)  //将编码文件写进去
{
    int i;
    for (i = 0; i < n; i++) {
        fprintf(fp2, "%s\t%s\n", (ps + i)->name, HufCode[i]);//写入数量
    }
}

int main() {
    int n, i, s1, s2;
    stack ps;
    char **HufCode;        //这个指针指向一个指针数组（元素个数=叶子个数），
    //数组中的每个元素指向一个动态字符串空间（装有最后的哈夫曼编码）
    int leaf_weight[4008];//叶子结点权重数组,一开始不定义大小就运行一段时间就报错了
    char hanzi[4008][3];
    FILE *fp1, *fp2;//定义两个文件指针变量fp1和fp2
    fp1 = fopen("权重.txt", "r"); //以只读模式打开文件
    fp2 = fopen("sgCode.txt", "w"); //以写入的模式打开文件f2 .txt
    n = open(leaf_weight, fp1, fp2, hanzi);//获取了数组个数，数组本身就是地址，不用返回
    ps = create(leaf_weight, hanzi, n, ps, &s1, &s2);
    HufCode = coding(HufCode, n, ps);
    display(HufCode, ps, fp2, n);  //将编码文件写进去

//	printf("n:%d\n",n);
//	n=sizeof(leaf_weight)/sizeof(leaf_weight[0]);//求数组的元素个数
//	ps=operate(n,ps,&s1,&s2,leaf_weight);
//	coding(HufCode,n,ps);//构建哈夫曼编码的函数
    free(ps);//释放空间
    return 0;
}

