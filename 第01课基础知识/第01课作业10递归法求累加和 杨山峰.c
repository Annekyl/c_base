//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"
int add(int n) {
    if (n == 1)
        return 1;
    else
        return n + add(n - 1);
}

int main() {
    int max = 100;
    printf("1��100���ۼӺ�Ϊ%d\n", add(max));
    return 0;
}