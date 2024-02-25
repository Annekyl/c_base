#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// ����ջ�ṹ
typedef struct {
    int* data;  // �洢ջԪ�ص�����ָ��
    int top;    // ջ��ָ��
} Stack;

// ��ʼ��ջ
void initStack(Stack* stack) {
    stack->data = (int*)malloc(MAX_SIZE * sizeof(int));  // ����ջԪ��������ڴ�ռ�
    stack->top = -1;  // ��ʼ��ջ��ָ��Ϊ-1����ʾջΪ��
}

// ��ջ
void push(Stack* stack, int value) {
    stack->top++;  // ջ��ָ���һ
    stack->data[stack->top] = value;  // ��Ԫ�ط���ջ��λ��
}

// ��ջ
int pop(Stack* stack) {
    int value = stack->data[stack->top];  // ��ȡջ��Ԫ�ص�ֵ
    stack->top--;  // ջ��ָ���һ
    return value;  // ����ջ��Ԫ�ص�ֵ
}

// �ж��Ƿ�Ϊ������
int isOperator(char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}

// �����沨�����ʽ
int evalRPN(char** tokens, int tokensSize) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; i < tokensSize; i++) {
        if (isOperator(tokens[i])) {
            int num2 = pop(&stack);
            int num1 = pop(&stack);
            int result;

            if (strcmp(tokens[i], "+") == 0) {
                result = num1 + num2;
            } else if (strcmp(tokens[i], "-") == 0) {
                result = num1 - num2;
            } else if (strcmp(tokens[i], "*") == 0) {
                result = num1 * num2;
            } else if (strcmp(tokens[i], "/") == 0) {
                result = num1 / num2;
            }

            push(&stack, result);
        } else {
            push(&stack, atoi(tokens[i]));
        }
    }

    int result = pop(&stack);
    free(stack.data);

    return result;
}

int main() {
    char* tokens[] = {"2", "1", "+", "3", "*"};
    int tokensSize = sizeof(tokens) / sizeof(tokens[0]);

    int result = evalRPN(tokens, tokensSize);
    printf("���Ϊ: %d\n", result);

    return 0;
}
