#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// 定义栈结构
typedef struct {
    int* data;  // 存储栈元素的数组指针
    int top;    // 栈顶指针
} Stack;

// 初始化栈
void initStack(Stack* stack) {
    stack->data = (int*)malloc(MAX_SIZE * sizeof(int));  // 分配栈元素数组的内存空间
    stack->top = -1;  // 初始化栈顶指针为-1，表示栈为空
}

// 入栈
void push(Stack* stack, int value) {
    stack->top++;  // 栈顶指针加一
    stack->data[stack->top] = value;  // 将元素放入栈顶位置
}

// 出栈
int pop(Stack* stack) {
    int value = stack->data[stack->top];  // 获取栈顶元素的值
    stack->top--;  // 栈顶指针减一
    return value;  // 返回栈顶元素的值
}

// 判断是否为操作符
int isOperator(char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}

// 计算逆波兰表达式
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
    printf("结果为: %d\n", result);

    return 0;
}
