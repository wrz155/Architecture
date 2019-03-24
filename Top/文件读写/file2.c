#include <stdio.h>

int main01(void)
{
    FILE *p = fopen("D:\\temp\\a.txt", "r");//如果文件打开，那么fopen返回打开的文件指针，如果失败，返回NULL
    if (p == NULL)
    {
        printf("file open fail\n");
    }
	else
    {
        printf("file open success\n");
        fclose(p);
    }
    printf("end\n");
    return 0;
}

int main02()
{
    FILE *p = fopen("D:\\temp\\a.txt", "a");//用追加的方式打开文件
    //“a"的含义是，如果文件不存在，那么就创建这个文件，如果文件存在，就在文件结尾处开始追加
    if (p == NULL)
    {
        printf("file open fail\n");
    }else
    {
        fputs("hello", p);
        fclose(p);
    }
    printf("end\n");
    return 0;
}

int main()
{
//    char c = '\r';
//    printf("%x\n", c);
//    return 0;
    FILE *p = fopen("D:\\temp\\a.txt", "w");//用文本文件方式写文件
    //“a"的含义是，如果文件不存在，那么就创建这个文件，如果文件存在，就在文件结尾处开始追加
    if (p == NULL)
    {
        printf("file open fail\n");
    }else
    {
        fputs("hell\n", p);
        fputs("world\n", p);
        fclose(p);
    }
    printf("end\n");
    return 0;
}

