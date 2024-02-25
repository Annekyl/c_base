//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"


int main() {
    int a, b;
    int num = 0;
    int list[] = {12, 40, 10, 9, 8, -1, 21, -6};
    int len = sizeof(list) / sizeof(int);  //统计数组中元素的数量
    for (int i = 0; i < len; ++i) {
        for (int j = i; j < len; ++j) {
            if (list[i] > list[j]) {
                a = list[i];
                b = list[j];
                list[i] = b;
                list[j] = a;
                num += 1;
            }
        }
    }
    for (int i = 0; i < len; ++i) {
        printf("%d\t", list[i]);
    }
    printf("\n共交换%d次", num);
    return 0;
}