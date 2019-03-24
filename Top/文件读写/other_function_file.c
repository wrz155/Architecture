#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void file_function_rename(void)
{
	//将指定文件改名
	rename("D:\\temp\\c.txt", "D:\\temp\\a.txt");
}

void file_function_remove(void)
{
	//删除d:\temp\b.txt
	remove("D:\\temp\\b.txt");
}

void file_function_fseek(void)
{
	FILE *p = fopen("D:\\temp\\a.txt", "rb");
	fseek(p, 0, SEEK_END);						//偏移到文件最后
}