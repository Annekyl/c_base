//
// Created by 30694 on 2024/2/18.
//
#include <stdlib.h>
#include <stdio.h>


// 获取文件内容
int getfilecontent(char *content) {
    FILE *file = fopen("./1.txt", "r"); // 打开名为"1.txt"的文件，以只读方式
    char buff[1024];
    fread(buff, 1024, 1, file); // 从文件中读取数据到缓冲区buff中
    fclose(file); // 关闭文件
    int j = 0;
    for (int i = 0; i < 1024; i++) {
        if (buff[i] == '\0') { // 如果读取到空字符'\0'，表示字符串结束
            content[j++] = '\0'; // 在content数组末尾添加一个空字符作为字符串结束标志
            break;
        }
        if (buff[i] == '\n') {
            continue; // 忽略换行符
        }
        content[j++] = buff[i]; // 将读取到的非换行字符复制到content数组中
    }
    return j - 1; // 返回字符串长度（不包括末尾的空字符）
}

// 二进制处理
void binarydeal(char *x, int s) {
    FILE *file = fopen("./2.txt", "wb"); // 打开名为"2.txt"的文件，以二进制写入方式
    int l = 8 - s % 8; // 计算补位所需的位数
    l %= 8;
    s += l; // 补位后的长度
    unsigned char buff;
    for (int i = l; i > 0; i--) {
        x += '0'; // 在x字符串前面补位0
    }
    int charlen = s; // 当前字符的位数
    int data = 0; // 存储转换后的二进制数据
    for (int i = 0; i < s; i++) {
        data *= 2; // 将data左移一位（相当于乘以2）
        if (x[i] == '1') {
            data++; // 如果x[i]为'1'，则将data加1
        }
        charlen--; // 当前字符的位数减1
        if (charlen % 8 == 0) { // 如果当前字符的位数是8的倍数（即一个字节的长度）
            buff = data; // 将data赋值给buff，即一个字节的二进制数据
            printf("%d ", buff);
            fputc(buff, file); // 将buff写入文件中
            data = 0; // 重置data为0，准备处理下一个字节
        }
    }
    fclose(file); // 关闭文件
}

// 解码
void mydecode() {
    FILE *file = fopen("./2.txt", "rb"); // 打开名为"2.txt"的文件，以二进制读取方式
    unsigned char buff[1024];
    fread(buff, 1024, 1, file); // 从文件中读取二进制数据到缓冲区buff中
    fclose(file); // 关闭文件
    FILE *file_w = fopen("./3.txt", "wb"); // 打开名为"3.txt"的文件，以二进制写入方式
    int a = 0;
    int lenth = 0;
    int b[8]; // 存储每个字节的二进制数据
    while (buff[lenth] != '\0') { // 循环读取缓冲区中的数据直到遇到空字符'\0'
        a = buff[lenth++];
        for (int i = 7; i > -1; i--) { // 将一个字节的二进制数据转换为数组b中的元素
            b[i] = a % 2; // 取a除以2的余数，即二进制位的值
            a /= 2; // 将a除以2，相当于右移一位
        }
        for (int i = 0; i < 8; i++) { // 将数组b中的二进制数据写入文件
            printf("%d", b[i]);
            fprintf(file_w, "%d", b[i]);
        }
    }
    fclose(file_w); // 关闭文件
}

int main() {
    char content[1024];
    int sum = getfilecontent(content); // 获取文件内容并返回长度
    printf(content);
    printf("\n");
    binarydeal(content, sum); // 处理文件内容并转换为二进制数据
    printf("\n");
    mydecode(); // 解码二进制数据并写入文件
    return 0;
}
