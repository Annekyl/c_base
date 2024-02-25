//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"
#include <stdbool.h>

bool sxhs(int n) {
    int a, b, c;
    a = n / 100; //百位
    b = n % 100 / 10;//十位
    c = n % 10;    //个位
    if (a * a * a + b * b * b + c * c * c == n)
        return true;
    else
        return false;
}

int main() {
    for (int i = 100; i < 1000; i++) {
        if (sxhs(i)) {
            printf("%d is narcissistic number\n", i);
        }
    }
}
