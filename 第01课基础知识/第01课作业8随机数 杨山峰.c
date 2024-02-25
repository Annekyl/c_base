//
// Created by Anne on 2023/12/3.
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
    srand((unsigned) time(NULL));
    int list[10];
    int a = 100, b = 0;
    for (int i = 0; i < 10; ++i) {
        list[i] = rand() % 100 + 1;
        printf("%d\t", list[i]);
    }
    for (int i = 0; i < 10; ++i) {
        if (list[i] < a)
            a = list[i];
        if (list[i] > b)
            b = list[i];
    }
    printf("最小的数为%d\n", a);
    printf("最大的数为%d\n", b);
    return 0;
}