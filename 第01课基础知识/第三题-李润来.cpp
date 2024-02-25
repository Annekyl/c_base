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
        printf("请输入你的成绩:");
        scanf("%d", &s);
        a = score(s);
        printf("你的单科绩点为%.1f\n", a); 
        
        if (s < 0)
            printf("无效输入");
            
    }
    
    return 0;  
}
