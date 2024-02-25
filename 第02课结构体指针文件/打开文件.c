#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, ""); // 设置本地化环境

    FILE *file; // 文件指针
    wchar_t filename[] = L"成绩.txt"; // 文件名
    wint_t ch;

    // 打开文件
    file = _wfopen(filename, L"r");

    // 检查文件是否成功打开
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    // 逐个字符读取文件内容并显示
    while ((ch = fgetwc(file)) != WEOF) {
        wprintf(L"%lc", ch);
    }

    // 关闭文件
    fclose(file);

    return 0;
}
