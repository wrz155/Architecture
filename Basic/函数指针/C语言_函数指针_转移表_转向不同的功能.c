//：
/*
	函数指针：
		1：定义函数指针 typedef (*pfun)()
		2：定义消息列表--枚举
		3：写函数列表
		4: 定义映射结构体
		5：定义映射关系（转移表）
		6：测试函数

	如果增加一个功能，须做的步骤如下：
		1：功能实现函数
		2：定义一个消息
		3：映射消息到功能函数
*/


#include <stdio.h>
#include <tchar.h>
#include <filesystem>
#include <stdlib.h>

//定义一个函数指针类型 pFun pFun1;
typedef int(*pFun)(int a, int b, int c, int *out);

int My_Fun_Sum(int a, int b, int c, int *out)
{
	*out = a + b + c;
	return 0;
}

int My_Fun_QSum(int a, int b, int c, int *out)
{
	*out = a * a + b * b + c * c;
	return 0;
}

int My_Fun_SSum(int a, int b, int c, int *out)
{
	*out = a * a*a + b * b*b + c * c*c;
	return 0;
}

typedef enum MSG_TYPE
{
	ACT_SUM = 1,
	ACT_QSUM = 2,
	ACT_SSUM,
	PROJ2_ACT_2,
	ACT_3,

	ACT_INVALID = 0xff, //16进制数字
}MSG_TYPE_E;

typedef struct MY_PROC
{
	int act;
	pFun pAct;
}MY_PROC_S;

MY_PROC_S g_astProc[] =
{
	{ ACT_SUM, My_Fun_Sum },
	{ ACT_QSUM, My_Fun_QSum },
	{ ACT_SSUM, My_Fun_SSum },
	{ ACT_INVALID, NULL },
};
/*
	程序外部，增加功能。
	前提是有一个大数组，往里面填充。
*/
/*
int Register_Proc(int act, pFun fun)
{
	int index = sizeof(g_astProc) / sizeof(MY_PROC_S);
	g_astProc[index].act = act;
	g_astProc[index].pAct = fun;
	
	return 0;
}
*/

int main(int argc, char* argv[])
{
	int i;
	int act;
	int num1;
	int num2;
	int num3;
	int out;

	if (argc < 5)
	{
		return -1;
	}
	act = atoi((char*)argv[1]);
	num1 = atoi((char*)argv[2]);
	num2 = atoi((char*)argv[3]);
	num3 = atoi((char*)argv[4]);
	printf("%d, %d, %d, %d\r\n", act, num1, num2, num3);

	for (i = 0; i < sizeof(g_astProc) / sizeof(MY_PROC_S); i++)
	{
		if (act == g_astProc[i].act)
		{
			g_astProc[i].pAct(num1, num2, num3, &out);
			break;
		}
	}
	printf("%d\r\n", out);
	system("pause");
	return 0;
}

