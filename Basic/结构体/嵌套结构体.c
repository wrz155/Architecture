#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//第一种
//结构体内部再次定义一个结构体，但是没有创建结构体的实例
//再次定义的结构体内部的变量，会被当作母结构体的成员变量
struct tianchao
{
	int data;
	char name[100];
	struct  beijing	 
	{
		char str[100];
		int num;
	};
};

//第二种
//结构体内部再次定义一个结构体，创建结构体变量，该变量会直接作为一个成员
struct tianchaoA
{
	int data;
	char name[100];
	struct  beijingA	 
	{
		char str[100];
		int num;
	}b1;	 			//内部定义的第一种方式
	struct  beijingA  b2;  //内部定义的第二种方式

};

void mainA1()
{
	struct tianchao t1;	 //	再次定义的结构体内部的变量，会被当作母结构体的成员变量
	//t1.beijing;
	t1.data = 100;
	t1.num = 99;
	sprintf(t1.name, "goA");
	sprintf(t1.str, "goB");
	printf("%d,%d,%s,%s", t1.data, t1.num, t1.name, t1.str);
	getchar();

}

void mai12123n()
{
	struct tianchaoA  t2;	//创建结构体变量，该变量会直接作为一个成员
	                           //结构体嵌套，用多个点来访问
	t2.b1.num = 100;
	sprintf(t2.b1.str, "ABC");
	printf("%d,%s", t2.b1.num, t2.b1.str);


	t2.b2.num = 100;
	sprintf(t2.b2.str, "ABC");
	printf("\n%d,%s", t2.b2.num, t2.b2.str);
	getchar();

}