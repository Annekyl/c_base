//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"
#include "stdbool.h"
bool judge(int n){
    if(n<2) return false;
    for(int i=2;i<n;i++){
        if(n%i==0) return false;
    }
    return true;
}

int main(){
    int n;
    printf("请输入你要判断是否为素数的整数");
    scanf_s("%d",&n);
    if(judge(n))
        printf("%d是素数",n);
    else
        printf("%d不是素数",n);
    return 0;
}