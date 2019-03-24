#include <stdio.h>

int main01(void)
{
    FILE *p = fopen("D:\\temp\\a.txt", "r");
    if (p == NULL)
    {
        printf("error\n");
    }else
    {

        char c = 0;
        while( (c = getc(p)) != EOF)//EOF代表文件最后的一个结束标示
        {
            //c = getc(p);//一次只读取一个字符
            printf("%c", c);
        }
        fclose(p);
    }
    return 0;
}

int main02(void)//写一个字符
{
    FILE *p = fopen("D:\\temp\\a.txt", "w");
    if (p == NULL)
    {
        printf("error\n");
    }else
    {
        putc('a', p);
        putc('b', p);
        putc('c', p);
        fclose(p);
    }
    return 0;
}

#define SEC 5

int main03(void)//加密
{
    FILE *p = fopen("D:\\temp\\a.txt", "r");
    FILE *p1 = fopen("D:\\temp\\b.txt", "w");
    if (p == NULL)
    {
        printf("error\n");
    }else
    {

        char c = 0;
        while( (c = getc(p)) != EOF)//EOF代表文件最后的一个结束标示
        {
            c += SEC;
            putc(c, p1);
        }
        fclose(p);
        fclose(p1);
    }
    return 0;
}

int main(void)//解密
{
    FILE *p = fopen("D:\\temp\\b.txt", "r");
    FILE *p1 = fopen("D:\\temp\\c.txt", "w");
    if (p == NULL)
    {
        printf("error\n");
    }else
    {

        char c = 0;
        while( (c = getc(p)) != EOF)//EOF代表文件最后的一个结束标示
        {
            c -= SEC;
            putc(c, p1);
        }
        fclose(p);
        fclose(p1);
    }
    return 0;
}

