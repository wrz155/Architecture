#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 111111 //最大记录数

struct dict
{
	char *key;//词条
	char *content;//词条对应的翻译
};

//打开字典文件，并读取文件内容
int open_dict(struct dict **p, const char *dict_filename)
{
	FILE *pfile = fopen(dict_filename, "r");
	if (pfile == NULL)
		return 0;//打开文件失败，函数返回

	*p = (struct dict *)malloc(sizeof(struct dict) * MAX);//固定分配MAX大小内存
	memset(*p, 0, sizeof(struct dict) * MAX);//将分配内存初始化为0
	struct dict *pD = *p;//pD指向数组p的首地址

	char buf[1024] = { 0 };
	size_t len = 0;
	int i = 0;//计数器
	while (!feof(pfile))//循环读取文件，直到文件末尾
	{
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);//读取文件一行
		len = strlen(buf);//得到读取到字符串长度
		if (len > 0)
		{
			pD[i].key = (char *)malloc(len);//根据字符串长度分配内存
			memset(pD[i].key, 0, len);
			strcpy(pD[i].key, &buf[1]);//将读取到的内容拷贝到key中
		}

		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);
		len = strlen(buf);
		if (len > 0)
		{
			pD[i].content = (char *)malloc(len);
			memset(pD[i].content, 0, len);
			strcpy(pD[i].content, &buf[6]);
		}

		i++;//计数器加1
	}
	fclose(pfile);//关闭字典文件

	return i;//返回读取到的字典词条数
}

//根据关键字key,在字典中查找内容
int search_dict(const struct dict *p, int size, const char *key, char *content)
{
	int i = 0;
	for (i = 0; i < size; i++)//遍历字典
	{
		if ((p[i].key == NULL) || (p[i].content == NULL))
			continue;

		if (strncmp(p[i].key, key, strlen(key)) == 0)
		{
			strcpy(content, p[i].content);
			return 1;//找到符合条件记录，返回1
		}
	}
	return 0;//没有找到符合条件记录，返回0
}

//释放内存
void free_dict(struct dict *p, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)//循环释放key与content成员内存
	{
		if (p[i].key)
			free(p[i].key);
		if (p[i].content)
			free(p[i].content);
	}
	free(p);//释放p内存
}


int main(int argc, char *args[])
{
	if (argc < 2)
	{
		printf("usage: %s dict-filename\n", args[0]);
		return 0;//参数不足，程序退出
	}
	long start_ms = 0;//记录函数执行的开始时间
	long end_ms = 0;//记录函数执行的结束时间
	struct dict *p = NULL;
	start_ms = clock();//记录函数执行的开始时间，单位：毫秒
	int size = open_dict(&p, args[1]);//根据命令行第一个参数做为字典文件名，打开字典文件
	if (size == 0)
		return 0;//打开字典文件失败，程序退出

	end_ms = clock();//得到系统当前时间，单位：毫秒
	printf("open_dict used %ld ms\n", end_ms - start_ms);//打印函数执行时间，单位：毫秒

	char key[1024];
	char content[1024];
	while (1)
	{
		memset(key, 0, sizeof(key));
		memset(content, 0, sizeof(content));
		scanf("%s", key);//从键盘得到用户输入
		if (strncmp(key, "command=exit", 12) == 0)
			break;
		start_ms = clock();
		if (search_dict(p, size, key, content))//根据用户输入，在字典中检索
		{
			printf("%s", content);
		} else
		{
			printf("not found\n");
		}
		end_ms = clock();
		printf("search_dict used %ld ms\n", end_ms - start_ms);//打印函数执行时间，单位：毫秒
	}

	start_ms = clock();
	free_dict(p, size);
	end_ms = clock();
	printf("free_dict used %ld ms\n", end_ms - start_ms);//打印函数执行时间，单位：毫秒
	return 0;
}
