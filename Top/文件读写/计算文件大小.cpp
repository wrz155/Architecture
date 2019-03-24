int GetFileSize(char *path)
{
	FILE *pf;//文件指针
	pf = fopen(path, "r");//读取的模式打开
	if (pf == NULL)
	{
		return -1;//代表获取失败
	}
	else
	{
		fseek(pf, 0, SEEK_END);//到文件末尾
		int num = ftell(pf);//文件开头到当前位置有多少个字节
		fclose(pf);//关闭文件
		return num;
	}
}