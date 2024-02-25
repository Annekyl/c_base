#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file;
    file = fopen("成绩.txt", "r"); // 打开文本文件
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) { // 如果是字母，跳过
            continue;
        } else if (isdigit(ch)) { // 如果是数字，输出
            printf("数字: %c\n", ch);
        } else if ((unsigned char)ch > 127) { // 如果是汉字，输出
            printf("汉字: %c\n", ch);
        }
    }

    fclose(file); // 关闭文件

    return 0;
}
