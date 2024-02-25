#include <stdio.h>

int main() {
    FILE *file;
    char line[100];

    // 打开要读取的txt文件
    file = fopen("成绩.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    // 逐行读取文本内容
    while (fgets(line, sizeof(line), file)) {
        // 处理每一行文本内容，这里直接输出
        printf("%s", line);
    }

    // 关闭文件
    fclose(file);

    return 0;
}
