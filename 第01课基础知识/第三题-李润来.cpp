#include <stdio.h>

float score(int s)
{    
    if (s < 60)
        return 0;
    else
        return (s - 50) / 10.0;
}

int main() 
{
    int s;
    float a;
    
    while (1) {
        printf("��������ĳɼ�:");
        scanf("%d", &s);
        a = score(s);
        printf("��ĵ��Ƽ���Ϊ%.1f\n", a); 
        
        if (s < 0)
            printf("��Ч����");
            
    }
    
    return 0;  
}
