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
    printf("��������Ҫ�����ֵ������");
    scanf_s("%f", &n);
    printf("����ֵΪ:%f", absolute(n));
    return 0;
}