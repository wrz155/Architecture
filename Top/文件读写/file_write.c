/*
	常用的文件写函数的基本使用方法
		fwrite()
		putc()
		fputs()
		fprintf()
		fflush()
			/*
				fflush将缓冲区的内容立刻写入文件
				优势是，不会因为停电，或者电脑死机等故障导致缓冲区的内容丢失
				不好的，硬盘读写次数增加，导致程序效率低下，同时硬盘寿命变短
				修改配置文件的时候，有时候会使用，或者做一些不经常修改的数据，但很重要数据，那么用fflush
			*/
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

struct student
{
	char name[100];
	int age;
};

struct student st1 = { "刘德华", 31 };

struct student st5[5] =
{
	{ "刘德华", 31 },
	{ "刘德华", 32 },
	{ "刘德华", 33 },
	{ "刘德华", 34 },
	{ "刘德华", 35 },
};

char str[1024] = { 0 };

void write_struct_to_file_fwrite(void)
{
	FILE *p = fopen("a.dat", "wb");
		
	// 第一种，一个结构体一个结构体的写
	for (int i = 0; i < 5; i++)
	{
		fwrite(&st1, sizeof(struct student), 1, p);
	}

	// 第二种，整个结构体数组写入
	fwrite(&st5, sizeof(struct student), 5, p);

	fclose(p);
}

void write_str_to_file_fputs(void)//写文件
{
	//	"w"意思就是如果文件不存在，就建立一个，如果文件存在就覆盖
	FILE *p = fopen("a.txt", "w");
	fputs(str, p);
	fclose(p);
}

void write_char_to_file_putc(void)
{
	FILE *p = fopen("a.txt", "w");
	if (NULL == p)
	{
		printf("error\n");
		return;
	}
	else
	{
		putc('a', p);
		putc('b', p);
		putc('c', p);
		fclose(p);
	}
}

void write_str_to_file_fprintf(void)
{
	FILE *p = fopen("a.txt", "w");
	fprintf(p, "%s\n", str);
	fclose(p);
}


void write_immediately_to_file_fflush(void)
{
	FILE *p = fopen("a.txt", "w");
	fprintf(p, "%s\n", str);
	fflush(p);		
	fclose(p);
}