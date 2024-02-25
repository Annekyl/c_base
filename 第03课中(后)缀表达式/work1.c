#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ջ��ʵ��
typedef struct {
    int *data;          // ջ����������
    int capacity;       // ջ������
    int top;            // ջ��ָ��
} Stack;

// ��ʼ��ջ
void initStack(Stack *stack, int capacity) {
    stack->data = (int *) malloc(sizeof(int) * capacity);
    stack->capacity = capacity;
    stack->top = -1;   // ��ʼ��ջ��ָ��Ϊ-1����ʾջΪ��
}

// �ж�ջ�Ƿ�Ϊ��
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

// �ж�ջ�Ƿ�����
bool isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// ��ջ
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("ջ��װ��������\n");
        exit(1);
    }
    stack->data[++stack->top] = value;   // ��Ԫ�ط���ջ��������ջ��ָ���1
}

// ��ջ
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("ջ����Ϊ��\n");
        exit(1);
    }
    return stack->data[stack->top--];    // ����ջ��Ԫ�أ�����ջ��ָ���1
}

// ��ȡջ��Ԫ��
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("ջ����Ϊ��\n");
        exit(1);
    }
    return stack->data[stack->top];      // ����ջ��Ԫ��
}

// �ж��ַ��Ƿ�Ϊ����
bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

// ��ȡ��������ȼ�
int getPriority(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

// ����׺���ʽת��Ϊ��׺���ʽ
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;  // ����һ��ջ
    initStack(&stack, strlen(infix));  // strlen���ڻ�ȡ���������׺���ʽ�ĳ���
    int len = strlen(infix);  // ������׺���ʽ�ĳ���
    int j = 0;

    // ѭ������ÿһ���ַ�
    for (int i = 0; i < len; i++) {
        char c = infix[i];

        if (isDigit(c)) {
            // ��������֣��ҵ������������ַ����ϲ���һ������
            int num = c - '0';  // ͨ��ASCII��ֵ���,���ַ�cת��������
            while (i + 1 < len && isDigit(infix[i + 1])) {
                num = num * 10 + (infix[i + 1] - '0');
                i++;
            }
            // �������������׺���ʽ�У��������ֺ������ #
            sprintf(postfix + j, "%d", num);
            j += strlen(postfix + j);
            postfix[j++] = '#';
        } else if (c == '(') {
            // ����������ţ���ջ
            push(&stack, c);
        } else if (c == ')') {
            // ����������ţ���ջ�е�������������������׺���ʽ�У�ֱ������������
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            // ���������ź�ֱ�ӽ������Ŵ�ջ��ȥ��
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack);
            } else {
                printf("���Ų�ƥ��\n");
                exit(1);
            }
        } else {
            // ��������������ջ�����ȼ����ڵ��ڸ��������������������������׺���ʽ�У�Ȼ�󽫵�ǰ�������ջ
            while (!isEmpty(&stack) && peek(&stack) != '(' && getPriority(peek(&stack)) >= getPriority(c)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, c);
        }
    }

    // ��ջ��ʣ���������������������׺���ʽ��
    while (!isEmpty(&stack)) {
        if (peek(&stack) == '(') {
            printf("���Ų�ƥ��\n");
            exit(1);
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';   // �ں�׺���ʽ��ĩβ����ַ���������
}

int main() {
    char infix[100];
    printf("��������׺���ʽ: \n");
    scanf("%s", infix);

    char postfix[100];
    infixToPostfix(infix, postfix);
    printf("ת��Ϊ��׺���ʽ�Ľ��Ϊ: %s\n", postfix);

    return 0;
}
