//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

int main() {
    int list[] = {12, 40, 10, 9, 8, -1, 21, -6};
    int a, b;
    int num = 0;
    int len = sizeof(list) / sizeof(int);
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (list[j] > list[j + 1]) {
                a = list[j];
                b = list[j + 1];
                list[j] = b;
                list[j+1] = a;
                num++;
            }
        }
    }
    for (int i = 0; i < len; ++i) {
        printf("%d\n", list[i]);
    }
    printf("¹²½»»»%d´Î", num);
    return 0;
}