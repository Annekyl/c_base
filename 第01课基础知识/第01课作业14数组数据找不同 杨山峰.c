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
    printf("����1������2����ͬ�������ǣ�");
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            if (list1[i] == list2[j])
                printf("%d\t", list1[i]);
        }
    }
    printf("\n����1�ж�����2û�е������ǣ�");
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
    printf("\n����2�ж�����1û�е������ǣ�");
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