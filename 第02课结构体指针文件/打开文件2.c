#include <stdio.h>

int main() {
    FILE *file;
    char line[100];

    // ��Ҫ��ȡ��txt�ļ�
    file = fopen("�ɼ�.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return 1;
    }

    // ���ж�ȡ�ı�����
    while (fgets(line, sizeof(line), file)) {
        // ����ÿһ���ı����ݣ�����ֱ�����
        printf("%s", line);
    }

    // �ر��ļ�
    fclose(file);

    return 0;
}
