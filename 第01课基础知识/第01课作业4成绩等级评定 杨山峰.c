//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

void evaluate(int score) {
    if (score < 0)
        printf("��Ч�ɼ�");
    else if (score < 60)
        printf("������");
    else if (score < 70)
        printf("����");
    else if (score < 80)
        printf("һ��");
    else if (score < 90)
        printf("����");
    else if (score <= 100)
        printf("����");
    else
        printf("��Ч�ɼ�");
}

int main() {
    int score;
    printf("��������ĳɼ���");
    scanf_s("%d", &score);
    evaluate(score);
    return 0;
}