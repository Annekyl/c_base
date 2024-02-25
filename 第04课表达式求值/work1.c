//
// Created by 30694 on 2024/1/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 栈的实现
typedef struct {
    int *data;          // 栈的数据数组
    int capacity;       // 栈的容量
    int top;            // 栈顶指针
} Stack;

// 初始化栈
void initStack(Stack *stack, int capacity) {
    stack->data = (int *)malloc(sizeof(int) * capacity);
    stack->capacity = capacity;
    stack->top = -1;   // 初始化栈顶指针为-1，表示栈为空
}

// 释放栈
void freeStack(Stack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->capacity = 0;
    stack->top = -1;
}

// 判断栈是否为空
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

// 判断栈是否已满
bool isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// 入栈
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("栈所装数据已满\n");
        exit(1);
    }
    stack->data[++stack->top] = value;   // 将元素放入栈顶，并将栈顶指针加1
}

// 出栈
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("栈数据为空\n");
        exit(1);
    }
    return stack->data[stack->top--];    // 返回栈顶元素，并将栈顶指针减1
}

// 获取栈顶元素
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("栈数据为空\n");
        exit(1);
    }
    return stack->data[stack->top];      // 返回栈顶元素
}

// 判断字符是否为数字
bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

// 获取运算符优先级
int getPriority(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

// 将中缀表达式转换为后缀表达式
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;  // 创建一个栈
    initStack(&stack, strlen(infix));  // strlen用于获取所输入的中缀表达式的长度
    int len = strlen(infix);  // 保存中缀表达式的长度
    int j = 0;

    // 循环处理每一个字符
    for (int i = 0; i < len; i++) {
        char c = infix[i];

        if (isDigit(c)) {
            // 如果是数字，找到连续的数字字符并合并成一个数字
            int num = c - '0';  // 通过ASCII码值相减,将字符c转换成整数
            while (i + 1 < len && isDigit(infix[i + 1])) {
                num = num * 10 + (infix[i + 1] - '0');
                i++;
            }
            // 将数字输出到后缀表达式中，并在数字后面添加 #
            sprintf(postfix + j, "%d", num);
            j += strlen(postfix + j);
            postfix[j++] = '#';
        } else if (c == '(') {
            // 如果是左括号，入栈
            push(&stack, c);
        } else if (c == ')') {
            // 如果是右括号，将栈中的运算符弹出并输出到后缀表达式中，直到遇到左括号
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            // 遇到左括号后，直接将左括号从栈中去除
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack);
            } else {
                printf("括号不匹配\n");
                exit(1);
            }
        } else {
            // 如果是运算符，将栈中优先级大于等于该运算符的运算符弹出并输出到后缀表达式中，然后将当前运算符入栈
            while (!isEmpty(&stack) && peek(&stack) != '(' && getPriority(peek(&stack)) >= getPriority(c)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, c);
        }
    }

    // 将栈中剩余的运算符弹出并输出到后缀表达式中
    while (!isEmpty(&stack)) {
        if (peek(&stack) == '(') {
            printf("括号不匹配\n");
            exit(1);
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';   // 在后缀表达式的末尾添加字符串结束符
}

// 计算后缀表达式的值
int evaluatePostfix(char *postfix) {
    Stack stack;  // 创建栈结构体
    initStack(&stack, strlen(postfix));  // 初始化栈
    int len = strlen(postfix);  //字符串长度
    // 遍历字符串
    for (int i = 0; i < len; i++) {
        char c = postfix[i];

        if (isDigit(c)) {
            // 如果是数字，找到连续的数字字符并合并成一个数字
            int num = c - '0';  // 将字符变量转换成数字变量
            while (i + 1 < len && isDigit(postfix[i + 1])) {
                num = num * 10 + (postfix[i + 1] - '0');
                i++;
            }
            push(&stack, num);  // 入栈
        } else if (c == '#') {
            // 如果是数字字符后面的 # 符号，忽略它
            continue;
        } else {
            // 如果是运算符，弹出栈顶的两个数字进行计算，并将计算结果压入栈中
            int op2 = pop(&stack);
            int op1 = pop(&stack);
            int result;
            switch (c) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
                default:
                    printf("无效运算符\n");
                    exit(1);
            }
            push(&stack, result);  // 将结果入栈
        }
    }

    // 栈中剩余的元素就是表达式的值
    int result = pop(&stack);

    if (!isEmpty(&stack)) {
        printf("表达式无效\n");
        exit(1);
    }

    return result;
}

int main() {
    char infix[100];
    printf("请输入中缀表达式: \n");
    scanf("%s", infix);

    char postfix[100];
    infixToPostfix(infix, postfix);
    printf("转换为后缀表达式的结果为: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("运算结果为: %d\n", result);

    return 0;
}
