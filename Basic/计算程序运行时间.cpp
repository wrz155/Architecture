#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void test1()
	{
		time_t start, end;
		double res = 0;
		time(&start);//获取时间，传递给start
		volatile int i;
		for (i = 0; i < 3000000000; i++)//volatile强制每次从内存读取
		{
			res += i;
		}
		printf("\n%f", res);
		time(&end);//获取结束时间
		printf("\nvolatile消耗时间%fs", difftime(end, start));
	}
	system("pause");
}

void test2()
{
	time_t start, end;
	double res = 0;
	time(&start);//获取时间，传递给start
	int i;
	for ( i = 0; i < 3000000000; i++)//i在CPU寄存器保证速度
	{
		res += i;
	}
	printf("%f", res);
	time(&end);//获取结束时间
	printf("\n消耗时间%fs", difftime(end, start));
	system("pause");
}