//
// Created by Anne on 2023/12/3.
//
#include "stdio.h"

void evaluate(int score) {
    if (score < 0)
        printf("无效成绩");
    else if (score < 60)
        printf("不及格");
    else if (score < 70)
        printf("及格");
    else if (score < 80)
        printf("一般");
    else if (score < 90)
        printf("良好");
    else if (score <= 100)
        printf("优秀");
    else
        printf("无效成绩");
}

int main() {
    int score;
    printf("请输入你的成绩：");
    scanf_s("%d", &score);
    evaluate(score);
    return 0;
}