#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct dict
{
	char *key;
	char *content;
	struct dict *next;//指向链表下一个节点的指针
};

//打开字典文件，并读取文件内容
int open_dict(struct dict **p, const char *dict_filename)//open dict.txt,and read dict
{
	FILE *pfile = fopen(dict_filename, "r");//只读方式打开文件
	if (pfile == NULL)
		return 0;//打开文件失败，函数返回

	char buf[2048] = { 0 };
	size_t len = 0;
	int i = 0;//计数器，记录读到到的词条总数

	*p = (struct dict *)malloc(sizeof(struct dict));//分配链表首节点内存
	memset(*p, 0, sizeof(struct dict));

	struct dict *pD = *p;//pD指向链表首地址
	while (!feof(pfile))//循环读取文件，直到文件末尾
	{
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);//读取文件一行
		len = strlen(buf);//得到读取到字符串长度
		if (len > 0)
		{
			pD->key = (char *)malloc(len);//根据字符串长度分配内存
			memset(pD->key, 0, len);
			strcpy(pD->key, &buf[1]);//将读取到的内容拷贝到key中
		}

		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), pfile);
		len = strlen(buf);
		if (len > 0)
		{
			pD->content = (char *)malloc(len);
			memset(pD->content, 0, len);
			strcpy(pD->content, &buf[6]);
		}
		pD->next = (struct dict *)malloc(sizeof(struct dict));//为链表的下一个节点分配内存
		memset(pD->next, 0, sizeof(struct dict));

		pD = pD->next;//将pD指向下一个节点位置
		i++;
	}
	fclose(pfile);//关闭字典文件
	return i;//返回读取到的字典词条数
}

//根据关键字key,在字典中查找内容
int search_dict(const struct dict *p, int size, const char *key, char *content)
{
	const struct dict *pD = p;
	while (pD)//遍历字典
	{
		if ((pD->key) && (pD->content))
		{
			if (strncmp(pD->key, key, strlen(key)) == 0)
			{
				strcpy(content, pD->content);
				return 1;//找到符合条件记录，返回1
			}
		}
		pD = pD->next;//指向链表下一个节点位置
	}
	return 0;//没有找到符合条件记录，返回0
}

//释放链表内存
void free_dict(struct dict *p, int size)
{
	struct dict *pD = p;
	while (pD)
	{
		if (pD->key)//删除链表节点中key成员内存
			free(pD->key);
		if (pD->content)//删除链表节点中content成员内存
			free(pD->content);

		struct dict *tmp = pD->next;//保存链表下一个节点的地址
		free(pD);//删除链表当前节点
		pD = tmp;//p指向下一个节点的位置
	}
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

	start_ms = clock();
	struct dict *p = NULL;
	int size = open_dict(&p, args[1]);//根据命令行第一个参数做为字典文件名，打开字典文件
	if (size == 0)
		return 0;//打开字典文件失败，程序退出

	end_ms = clock();
	printf("open_dict used %ld ms\n", end_ms - start_ms);//打印函数执行时间，单位：毫秒

	char key[2048];
	char content[2048];
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
	};

	start_ms = clock();
	free_dict(p, size);//释放链表内存
	end_ms = clock();
	printf("free_dict used %ld ms\n", end_ms - start_ms);//打印函数执行时间，单位：毫秒
	return 0;
}
