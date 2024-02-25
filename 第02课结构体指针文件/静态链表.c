#include <stdio.h>

int main() {
    FILE *file; // 文件指针
    char filename[] = "成绩.txt"; // 文件名
    char ch;

    // 打开文件
    file = fopen(filename, "r");

    // 检查文件是否成功打开
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    // 逐个字符读取文件内容并显示
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    // 关闭文件
    fclose(file);

    return 0;
}
