#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file;
    file = fopen("�ɼ�.txt", "r"); // ���ı��ļ�
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) { // �������ĸ������
            continue;
        } else if (isdigit(ch)) { // ��������֣����
            printf("����: %c\n", ch);
        } else if ((unsigned char)ch > 127) { // ����Ǻ��֣����
            printf("����: %c\n", ch);
        }
    }

    fclose(file); // �ر��ļ�

    return 0;
}
