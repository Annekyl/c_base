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
    printf("��������Ҫ�ж��Ƿ�Ϊ����������");
    scanf_s("%d",&n);
    if(judge(n))
        printf("%d������",n);
    else
        printf("%d��������",n);
    return 0;
}