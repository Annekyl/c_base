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
    printf("������ɼ���");
    scanf_s("%f", &score);

    float gpa = calculateGPA(score);
    printf("����Ϊ��%.1f\n", gpa);

    return 0;
}
