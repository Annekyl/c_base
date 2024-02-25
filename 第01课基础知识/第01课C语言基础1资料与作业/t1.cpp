#include <stdio.h>
#include <stdbool.h>


int main()
{
	int s,a,b,c;
	for (s=100;s<=999;s++)
	{
		c=s%10;
		b=(s/10)%10;
		a=s/100;
		//printf("%d,%d,%d,%d\n",s,a,b,c);
		if(s==a*a*a+b*b*b+c*c*c)
			printf("%d是水仙花数\n",s);
	}

	return 0;
}

