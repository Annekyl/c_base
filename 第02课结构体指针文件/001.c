//
// Created by 30694 on 2024/1/17.
//
#include "stdio.h"

int main() {
    int a = 3;  //值型变量
    float b;
    char c;
    unsigned int m;
    unsigned char n;

    int *p[8];  //地址型变量  指针p[0]
    int **q = &p[0];

    struct stu {  //结构体类型
        int a;
        float b;
        char c;
        int d;
//      int *n;
        struct stu *n;
    };
    struct stu x, w;
    x.a = 88;
    x.c = 'A';
    x.n = &w;

    printf("%d\n", &a);  // &取地址运算

    p = &a;  // 认为p指向了a
    printf("%d\n", p);
    printf("%d\n", &p);

    q = &p;
    printf("%d\n", q);

    printf("%d\n", a);
    *p = 999;  // *取单元运算
    printf("%d\n", a);

    return 0;

}