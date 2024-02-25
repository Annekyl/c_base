//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

int main() {
    int list1[] = {12, 40, 10, 9, 8, -1, 21, -6};
    int list2[] = {12, 7, 10, 9, 88, 1, 21, -6};
    int found;
    int len1 = sizeof(list1) / sizeof(int);
    int len2 = sizeof(list2) / sizeof(int);
    printf("数组1和数组2中相同的数据是：");
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            if (list1[i] == list2[j])
                printf("%d\t", list1[i]);
        }
    }
    printf("\n数组1有而数组2没有的数据是：");
    for (int i = 0; i < len1; ++i) {
        found = 0;
        for (int j = 0; j < len2; ++j) {
            if (list1[i] == list2[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0)
            printf("%d\t", list1[i]);
    }
    printf("\n数组2有而数组1没有的数据是：");
    for (int i = 0; i < len2; ++i){
        found = 0;
        for (int j = 0; j < len1; ++j) {
            if (list2[i] == list1[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0)
            printf("%d\t", list2[i]);
    }
    return 0;
}