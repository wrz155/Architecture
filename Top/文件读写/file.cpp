#include <stdio.h>
#include <string.h>

int main01(void)//写文件
{
	char s[1024] = { 0 };

	//	"w"意思就是如果文件不存在，就建立一个，如果文件存在就覆盖
	FILE *p = fopen("D:\\temp\\a.txt", "w");

	while (1)
	{
		memset(s, 0, sizeof(s));
		//scanf("%s", s);
		gets_s(s);
		if (strcmp(s, "exit") == 0)
		{
			break;
		}

		int len = strlen(s);
		s[len] = '\n';
		fputs(s, p);
	}

	fclose(p);
	return 0;
}

int main02()
{
	char s[1024] = { 0 };
	FILE *p = fopen("D:\\temp\\main.c", "r");

	//feof(p);//如果已经到了文件结尾，函数返回真
	while (!feof(p))//如果没有到文件结尾，那么就一直循环
	{
		memset(s, 0, sizeof(s));
		fgets(s, sizeof(s), p);//第一个参数是一个内存地址，第二个参数是这块内存的大小，第三个参数是fopen返回的文件指针
		printf("%s", s);
	}
	fclose(p);
	return 0;
}

void code(char *s)
{
	while (*s)
	{
		(*s)++;
		s++;
	}
}

void decode(char *s)
{
	while (*s)
	{
		(*s)--;
		s++;
	}
}

int main03()//加密
{
	char s[1024] = { 0 };
	FILE *p = fopen("D:\\temp\\a.txt", "r");//用读的方式打开一个文件
	FILE *p1 = fopen("D:\\temp\\b.txt", "w");//用写的方式打开一个文件

	//feof(p);//如果已经到了文件结尾，函数返回真
	while (!feof(p))//如果没有到文件结尾，那么就一直循环
	{
		memset(s, 0, sizeof(s));
		fgets(s, sizeof(s), p);//第一个参数是一个内存地址，第二个参数是这块内存的大小，第三个参数是fopen返回的文件指针
		code(s);//
		fputs(s, p1);
	}
	fclose(p);
	fclose(p1);
	return 0;
}

int main()//解密
{
	char s[1024] = { 0 };
	FILE *p = fopen("D:\\temp\\b.txt", "r");//用读的方式打开一个文件
	FILE *p1 = fopen("D:\\temp\\c.txt", "w");//用写的方式打开一个文件
	//feof(p);//如果已经到了文件结尾，函数返回真
	while (!feof(p))//如果没有到文件结尾，那么就一直循环
	{
		memset(s, 0, sizeof(s));
		fgets(s, sizeof(s), p);//第一个参数是一个内存地址，第二个参数是这块内存的大小，第三个参数是fopen返回的文件指针
		decode(s);//
		fputs(s, p1);
	}
	fclose(p);
	fclose(p1);
	return 0;
}



