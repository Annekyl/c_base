//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

int main() {
    char str[100];
    int sum = 0;
    printf("�����봿Ӣ���ַ���");
    fgets(str,sizeof(str),stdin);
    for (int i = 0; str[i]!='\0'; i++) {
        sum+=(int)str[i];
    }
    printf("ASCII��ֵ֮��Ϊ��%d", sum);
    return 0;
}

