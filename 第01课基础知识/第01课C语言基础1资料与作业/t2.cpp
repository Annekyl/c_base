#include <stdio.h>
#include <stdbool.h>

bool daff(int s)
{
	int a,b,c;
	c=s%10;
	b=(s/10)%10;
	a=s/100;
	if(s==a*a*a+b*b*b+c*c*c)
		return true;
	else
		return false;
}

int main()
{
	int s,a,b,c;
	for (s=100;s<=999;s++)
	{
		if(daff(s))
			printf("%d��ˮ�ɻ���,����\n",s);
	}

	return 0;
}

