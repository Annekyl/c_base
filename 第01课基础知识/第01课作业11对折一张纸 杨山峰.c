//
// Created by Anne on 2023/12/3.
//
#include <stdio.h>

int duizhe(float n) {
    int num = 0;
    while (n < 8848.18 * 1000) {
        n = n * 2;
        num++;
    }
    return num;
}

int main() {
    float n = 0.1;
    printf("%d", duizhe(n));
    return 0;
}