#include<stdio.h>
#include<stdlib.h>

struct  dangdang
{
	char email[30];
	char name[30];
	char addr[100];
	int num;
	int bignum;
	char tel[20];
	char phone[20];
	double RMB;
} dbdd[4] =
{
	{ "gutingyanmaomao@hotmail.com", "顾婷艳", "上海市汇成五村55号103室", 131, 3, "64247341", "13817188037", 12.30 },
	{ "hongyueliu@263.net", "刘红玥", "学清路逸成东苑6号楼4单元602室", 111, 1, "82420196", "13501057351", 49.80 },
	{ "740031305@qq.com", "何英杰", "杭州电子科技大学（下沙校区）会计学院", 133, 1901, "0108888", "15869027536", 22.50 },
	{ "qiujx930@163.com", "裘佳欣", "普育东路30号304室", 131, 3, "", " 13585662411", 14.00 }
};

void main321()
{
	for (struct dangdang *p = dbdd; p < dbdd + 4; p++)
	{
		printf("\nname=%s,addr=%s,phone=%s", p->name, p->addr, p->phone);
		printf("\nname=%s,addr=%s,phone=%s", (*p).name, (*p).addr, (*p).phone);
	}

	getchar();

}






void main23()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	for (int *p = a; p < a + 5; p++)
		//p++根据类型自增，一次增加四个字节，轮询内存地址
	{
		printf("\n%d,%x", *p, p);
	}




	system("pause");
}