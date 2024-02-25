//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

int main() {
    int ls1[4][3] = {{1,  2,  3},
                     {4,  5,  6},
                     {7,  8,  9},
                     {10, 11, 12}};
    int ls2[3][4];
    int len1 = sizeof(ls1) / sizeof(ls1[0]);
    int len2 = sizeof(ls1[0]) / sizeof(int);
    for (int i = 0; i < len2; i++) {
        for (int j = 0; j < len1; j++) {
            ls2[i][j] = ls1[j][i];
            printf("%d\t", ls2[i][j]);
        }
        printf("\n");
    }
    return 0;
}