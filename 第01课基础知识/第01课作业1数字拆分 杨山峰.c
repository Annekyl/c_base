//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

int main() {
    int n;
    int a, b, c, d;
    scanf_s("%d", &n);
    a = n / 1000;
    b = n / 100 % 10;
    c = n / 10 % 10;
    d = n % 10;
    printf("%d\n", a + b + c + d);
    return 0;

}