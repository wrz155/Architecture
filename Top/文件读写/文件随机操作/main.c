#include <stdio.h>
#include <stdlib.h>

/*文件随机读写操作*/
int main(int argc, char** argv[])
{
	/*打开文件*/
	FILE* p_file = NULL;
	if ( (p_file = fopen("g://test.bin","wb") ) == NULL )
	{
		printf("打开文件出错！\n");
		return 1;
	}

	/*写入一些数据*/
	for (int i = 0; i < 100; i++)
	{
		fwrite(&i, sizeof(int), 1, p_file);
	}

	/*关闭文件*/
	fclose(p_file);
	
	/*重新打开文件*/
	p_file = NULL;
	if ((p_file = fopen("g://test.bin", "rb+")) == NULL)
	{
		printf("打开文件出错！\n");
		return 1;
	}

	/*使用随机读函数读取指定位置的数据*/
	/*读取第10个数据*/
	/*偏移量以字节为单位*/
	/*操作顺序：先定位，再操作*/
	fseek( p_file, sizeof(int) * 9, SEEK_SET );
	int tmp;
	fread( &tmp, sizeof(int), 1, p_file );
	printf("读取的数据为：%d\n", tmp);
	
	/*取倒数第十个元素*/
	fseek(p_file, -(int)(sizeof(int) * 10 ), SEEK_END);
	fread(&tmp, sizeof(int), 1, p_file);
	printf("读取的数据为：%d\n", tmp);

	/*从当前位置计算取第三个元素*/
	fseek(p_file, sizeof(int)* 3, SEEK_CUR);
	fread(&tmp, sizeof(int), 1, p_file);
	printf("读取的数据为：%d\n", tmp);

	fseek(p_file, sizeof(int) * 1000, SEEK_SET);
	fwrite(&tmp, sizeof(int),1, p_file);
	/*读取完毕，关闭文件*/
	fclose(p_file);
	system("pause");
	return 0;
}