#include <stdio.h>
#include <stdlib.h>

int main01(void)
{
    FILE *p = fopen("D:\\temp\\a.txt", "w");
    while(1)
    {
        char buf[100] = { 0 };
        scanf("%s", buf);
        if (strcmp(buf, "exit") == 0)
            break;
        fprintf(p, "%s\n", buf);
        fflush(p);//fflush将缓冲区的内容立刻写入文件
        //优势是，不会因为停电，或者电脑死机等故障导致缓冲区的内容丢失
        //不好的，硬盘读写次数增加，导致程序效率低下，同时硬盘寿命变短
        //修改配置文件的时候，有时候会使用，或者做一些不经常修改的数据，但很重要数据，那么用fflush
    }
    fclose(p);
    return 0;
}

int main()
{
    //remove("D:\\temp\\b.txt");//删除d:\temp\b.txt
    rename("D:\\temp\\c.txt", "D:\\temp\\a.txt");//将指定文件改名
    return 0;
}

