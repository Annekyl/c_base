//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

float absolute(float n) {
    if (n < 0.0f) {
        return -n;
    } else
        return n;
}

int main() {
    float n;
    printf("请输入你要求绝对值的数字");
    scanf_s("%f", &n);
    printf("绝对值为:%f", absolute(n));
    return 0;
}