/*
	常用的读取文件函数的基本使用方法
		fgets()
		getc()
		fread()
		fscanf()
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
struct student
{
	char name[100];
	int age;
};

struct student st1 = { 0 };

struct student st5[5] = { 0 };

char c = 0;

int a = 0;
int b = 0;

/*
	feof(p);
		如果已经到了文件结尾，函数返回真
		如果没有到文件结尾，那么就一直循环
*/
void read_str_form_file_fgets(void)
{
	char s[1024] = { 0 };
	FILE *p = fopen("D:\\temp\\a.txt", "r");//用读的方式打开一个文件
	if (NULL == p)
	{
		printf("error\n");
		return;
	}
	else
	{
		while (!feof(p))
		{
			memset(s, 0, sizeof(s));
			fgets(s, sizeof(s), p);		//第一个参数是一个内存地址，第二个参数是这块内存的大小，第三个参数是fopen返回的文件指针
		}
		fclose(p);
	}
}

void read_char_form_file_getc(void)
{
	FILE *p = fopen("a.txt", "r");
	if (p == NULL)
	{
		printf("error\n");
		return;
	}
	else
	{
		while ((c = getc(p)) != EOF)//EOF代表文件最后的一个结束标示
		{
			//c = getc(p);//一次只读取一个字符
			printf("%c", c);
		}
		fclose(p);
	}
}

void read_struct_form_file_fread(void)
{
	// 第一种方法:定义一个结构体变量，每一次就读一个结构体的数据，重复读取
	FILE *p = fopen("a.dat", "rb");
	for (int i = 0; i < 5; i++)
	{
		size_t ret = fread(&st1, sizeof(struct student), 1, p);
		printf("name = %s, age = %d\n", st1.name, st1.age);
	}

	// 第二种方法：定义一个结构体数组，一次读满一个结构体数组
	fread(&st5, sizeof(struct student), 5, p);

	fclose(p);
}

void read_str_form_file_fscanf(void)
{
	FILE *p = fopen("a.txt", "r");
	while (!feof(p))
	{
		//fscanf与scanf用法基本一致，fscanf是从一个文件读取输入，scanf是从键盘读取输入
		fscanf(p, "%d + %d =", &a, &b);
		printf("a = %d, b = %d\n", a, b);
	}
	fclose(p);
	return 0;
}

void read_file_to_memory(void)
{
	clock_t c1 = clock();		//得到系统当前时间，单位：毫秒

	struct stat st = { 0 };		//定义一个结构，名字叫st
	stat("a.txt", &st);			//调用完stat函数之后，a.txt这个文件的相关的信息就保存在了st结构中了
	
	//st.st_size得到文件的大小
	char *array = malloc(st.st_size);//根据文件大小在堆中动态的分配一块内存
	FILE *p = fopen("a.txt", "rb");
	fread(array, sizeof(char), st.st_size, p);//相当于一下把整个文件放入了内存
	fclose(p);

	p = fopen("b.txt", "wb");
	fwrite(array, sizeof(char), st.st_size, p);//将堆中的信息一下都写入文件
	fclose(p);

	clock_t c2 = clock();			//得到系统当前时间，单位：毫秒
	printf("end, %u\n", c2 - c1);	//计算出整个过程耗费的时间
}




