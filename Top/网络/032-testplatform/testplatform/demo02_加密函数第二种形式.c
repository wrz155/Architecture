#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "socketclientdll.h"

int myEncData(unsigned char *inData,int inDataLen,unsigned char *outData,int *outDataLen,void *Ref, int RefLen)
{
	memcpy(outData, "111111111111111111111111111111111", 10);
	*outDataLen = 10;
	return 0;
}


int myEncData2(unsigned char *inData,int inDataLen,unsigned char *outData,int *outDataLen,void *Ref, int RefLen)
{
	memcpy(outData, "111111111111111111111111111111111", 10);
	*outDataLen = 10;
	return 0;
}

int myDecData01(unsigned char *inData,int inDataLen,unsigned char *outData,int *outDataLen,void *Ref, int RefLen)
{
	memcpy(outData, "2222222222222222222222222222222", 10);
	*outDataLen = 10;
	return 0;
}


int main()
{
	int				rv = 0;
	void			*handle = NULL;
	unsigned char	buf[2048];
	int				buflen = 0;

	unsigned char	buf2[2048] = {0};
	int				buflen2 = 0;

	strcpy(buf, "aaaaaaaaaaaaaaaaaaaaaaaaafffffffffffffffffffffff");


	buflen = 10;
	rv = cltSocketInit(&handle);
	if (rv != 0)
	{
		printf("func cltSocketInit():%d", rv);
		return rv;
	}
	
	
	/*
	// cvtres.exe
	rv = clitSocket_SetEncFunc(handle, myEncData2, NULL, 0);
	if (rv != 0)
	{
		printf("func cltSocketInit():%d", rv);
		goto End;
	}
	
	*/
	
	
	rv = cltSocketSend(handle, buf,  buflen);
	if (rv != 0)
	{
		printf("func cltSocketSend():%d", rv);
		goto End;
	}
	
	rv = cltSocketSend_enc(handle, buf,  buflen, myEncData2, NULL, 0);
	if (rv != 0)
	{
		printf("func cltSocketSend_enc():%d", rv);
		goto End;
	}
	

	/*
	//设置解密函数入口地址，到框架中
	rv = clitSocket_SetDecFunc(handle, myDecData01, NULL, 0);
	if (rv != 0)
	{
		printf("func cltSocketInit():%d", rv);
		goto End;
	}

	*/

	rv = cltSocketRev(handle, buf2 , &buflen2);
	if (rv != 0)
	{
		printf("func cltSocketRev():%d", rv);
		goto End;
	}
	printf("\n%s", buf2);

End:

	rv = cltSocketDestory(handle);
	if (rv != 0)
	{
		printf("func cltSocketDestory():%d", rv);
		return rv;
	}

	printf("hello....\n");
	
	//system("pause");

	return 0;
}

