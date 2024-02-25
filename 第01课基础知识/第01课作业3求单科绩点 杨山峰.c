#include <stdio.h>

float calculateGPA(float score) {
    if (score < 60)
        return 0.0f;
    else {
        return (score - 50) / 10.0f;
    }
}

int main() {
    float score;
    printf("请输入成绩：");
    scanf_s("%f", &score);

    float gpa = calculateGPA(score);
    printf("绩点为：%.1f\n", gpa);

    return 0;
}
