#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 100

struct student
{
	int num;
	char name[MAX_NAME_SIZE];
	char sex[2];
	int age;
};





void fileputchar()
{
	FILE  *fp = fopen("E:\\file.txt", "w");
	if (fp == NULL)
	{
		printf("file open error");
		exit(0);
	}
	else
	{
		char ch = 'q';
		while ((ch = getchar()) != EOF)
		{
			fputc(ch, fp);
		}


		fclose(fp);
	}

}
void filegetchar()
{
	FILE  *fp = fopen("E:\\file.txt", "r");
	if (fp == NULL)
	{
		printf("file open error");
		exit(0);
	}
	else
	{
		char ch;
		while ((ch = fgetc(fp)) != EOF)
		{
			putchar(ch);
		}


		fclose(fp);
	}
}

void fileputstring()
{
	FILE  *fp = fopen("E:\\file.txt", "a");
	if (fp == NULL)
	{
		printf("file open error");
		exit(0);
	}
	else
	{
		char ch[100] = { 0 };
		scanf("%s", ch);
		fputs(ch, fp);


		fclose(fp);
	}
}

void filegetstring()
{
	FILE  *fp = fopen("E:\\file.txt", "r");
	if (fp == NULL)
	{
		printf("file open error");
		exit(0);
	}
	else
	{
		char ch[100];
		while (fgets(ch, 100, fp) != NULL)
		{
			printf("%s", ch);
		}


		fclose(fp);
	}
}

void filewrite()
{
	FILE  *fp = fopen("E:\\file.txt", "w");
	if (fp == NULL)
	{
		printf("file open error");
		exit(0);
	}

	struct student studentInfo = { 0 };
	scanf("%d %s %s %d", &studentInfo.num, &studentInfo.name, &studentInfo.sex, &studentInfo.age);
	
	fwrite(&studentInfo, sizeof(student), 1, fp);


	fclose(fp);
	
}


void fileprintf()
{
	FILE  *fp = fopen("E:\\file.txt", "w");
	if (fp == NULL)
	{
		printf("file open error");
		exit(0);
	}

	struct student studentInfo = { 0 };
	scanf("%d %s %s %d", &studentInfo.num, &studentInfo.name, &studentInfo.sex, &studentInfo.age);

	fprintf(fp, "编号：%d\n姓名:%s\n性别:%s\n年龄:%d\n", &studentInfo.num, &studentInfo.name, &studentInfo.sex, &studentInfo.age);


	fclose(fp);

}
int main()
{
	fileputchar();
	filegetchar();
	getchar();
	return 0;
}