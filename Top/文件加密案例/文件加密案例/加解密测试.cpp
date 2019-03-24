#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "des.h"

/*

//用户使用的函数
int DesEnc(
unsigned char *pInData,
int            nInDataLen,
unsigned char *pOutData,
int           *pOutDataLen);

//用户使用函数des解密
int DesDec(
unsigned char *pInData,
int            nInDataLen,
unsigned char *pOutData,
int           *pOutDataLen);

*/



int main111()
{
	int		ret = 0;
	char *plain = "1232343444";
	int plainlen = strlen(plain);

	char plain2[4096] = {0};
	int plainlen2 = 0;

	unsigned char cryptbuf[4096] = {0};
	int cryptlen = 0;
	//用户使用的函数
	ret =  DesEnc(plain, plainlen, cryptbuf, &cryptlen);
	if (ret != 0)
	{
		printf("func DesEnc() err:%d \n");
		return ret;
	}

	//用户使用函数des解密
	ret =   DesDec(cryptbuf, cryptlen,  plain2, &plainlen2);
	if (ret != 0)
	{
		printf("func DesDec() err:%d \n");
		return ret;
	}

	if (plainlen != plainlen2)
	{
		ret = -2;
		printf("明文长度和解密后的明文长度 不一样 \n");
		return ret;
	}

	if (memcmp(plain2, plain, plainlen) == 0 )
	{
		printf("明文长度和解密后的明文长度 一样 ok \n");
	}
	else
	{
		printf("明文长度和解密后的明文长度 不一样 err \n");
	}

	system("pause");
	return ret ;
}


int FileSymEnc(const char *pfile1, const char *pfile2)
{
	int		ret = 0;
	FILE *fp1 = NULL, *fp2 = NULL;
	unsigned char plain[4096];
	int plainlen = 0;

	unsigned char cryptbuf[4096] = { 0 };
	int cryptlen = 0;

	int tmplen;

	fp1 = fopen(pfile1, "rb");
	if (fp1 == NULL)
	{
		goto END;
	}

	fp2 = fopen(pfile2, "wb");
	if (fp2 == NULL)
	{
		goto END;
	}

	while (!feof(fp1))
	{
		plainlen = fread(plain, 1, 4096, fp1);
		if (feof(fp1))  //读完数据以后，判断是否文件结束
		{
			break;
		}

		//加密==4k的数据
		ret = DesDec_raw(plain, plainlen, cryptbuf, &cryptlen);
		if (ret != 0)
		{
			printf("func DesEnc() err:%d \n", ret);
			goto END;
		}

		tmplen = fwrite(cryptbuf, 1, cryptlen, fp2);
		if (tmplen != cryptlen)
		{
			ret = -3;
			printf("写密文文件失败，请检查是否磁盘已满\n");
			goto END;
		}

		//if (plainlen == 4096)
	}

	//加密小于4k的数据
	ret = DesEnc(plain, plainlen, cryptbuf, &cryptlen);
	if (ret != 0)
	{
		printf("func DesEnc() err:%d \n", ret);
		goto END;
	}

	tmplen = fwrite(cryptbuf, 1, cryptlen, fp2);
	if (cryptlen != tmplen)
	{
		ret = -3;
		printf("写小于4k文件密文失败，请检查是否磁盘已满\n");
		goto END;
	}

END:
	if (fp1 != NULL)
	{
		fclose(fp1);
	}
	if (fp2 != NULL)
	{
		fclose(fp2);
	}
	return 0;
}

void main()
{
	int		ret = 0;
	const char *file1 = "c:/socketclient.dll";
	const char *file2 = "c:/socketclientend.dll";

	//const char *file1 = "c:/22.txt";
	//const char *file2 = "c:/22enc.txt";

	ret = FileSymEnc(file1, file2);
	if (ret != 0)
	{
		printf("func FileSymEnc() err\n ");
		return;
	}

	system("pause");
	return;
}