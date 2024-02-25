#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char *removeDuplicateLetters(char *s) {
    int vis[26], num[26];
    memset(vis, 0, sizeof(vis));  // 字母是否被访问
    memset(num, 0, sizeof(num));  // 相对应的字母有多少个

    int n = strlen(s);  // 一共有多少个字母
    // 统计每个字母出现的次数
    for (int i = 0; i < n; i++) {
        num[s[i] - 'a']++;
    }
    //开辟一块新空间作为栈
    char *stk = malloc(sizeof(char) * 27);  // 26个字母和'/0'
    int stkTop = 0;  // 栈顶指针
    for (int i = 0; i < n; i++) {
        if (!vis[s[i] - 'a']) {  //当前字母未被访问
            while (stkTop > 0 && stk[stkTop - 1] > s[i]) {  // 栈顶指针不为0，并且当前字母ASCII码值小于栈中的最后一个字母
                if (num[stk[stkTop - 1] - 'a'] > 0) {  // 栈中最后一个字母在后面字符串中仍会出现
                    stkTop--;
                    vis[stk[stkTop] - 'a'] = 0;  // 将栈顶字母重新标记为未访问
                } else {
                    break;
                }
            }
            vis[s[i] - 'a'] = 1;  // 将当前字母标记为已访问
            stk[stkTop] = s[i];  // 将当前字母加入栈中
            stkTop++;
        }
        num[s[i] - 'a'] -= 1;
    }
    stk[stkTop] = '\0';  // 作为字符串输出
    return stk;
}

int main() {
    char *a[100];
    char *b;
    scanf("%s", a);
    b = removeDuplicateLetters(a);
    printf("%s",b);
}