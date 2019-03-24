#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "itcast_comm.h"
//#include "memwatch.h"
#include "itcastlog.h"

/*
下面定义了一套socket客户端发送报文接受报文的api接口
请写出这套接口api的调用方法
*/

/*
1 先把基本框架实现 版本管理
2 内存泄露检查
3 日志
4 版本优化
*/
//开发底层库（开发接口），提供的是一种机制 ，而不是某种具体的策略。

//动态库变成框架 
//1 第三方业务入口传进来（回调函数的入口地址传进来）

//2 加密 解密 业务模型抽象
//实现 动态库 加密解密业务模型抽象
typedef int (*EncData)(unsigned char *inData,int inDataLen,unsigned char *outData,int *outDataLen,void *Ref, int RefLen);
typedef int (*DecData)(unsigned char *inData,int inDataLen,unsigned char *outData,int *outDataLen,void *Ref, int RefLen);



typedef struct _SCK_HANDLE {
	char	version[16];
	char	serverip[16];
	int		serverport;
	unsigned char *	buf ;
	int				buflen;

	//wangbaoming 20140404 add
	EncData                  myEncDataFunc;
	void					*encRef;
	int						encRefLen;

	DecData                   myDecDataFunc;
	void					*decRef;
	int						decRefLen;


}SCK_HANDLE;




//客户端初始化
ITCAST_FUNC_EXPORT(int)
cltSocketInit(void **handle) //5day after
{
	SCK_HANDLE		*sh = NULL;
	int				rv = 0;

	ITCAST_LOG(__FILE__, __LINE__,LogLevel[1], rv,"func cltSocketInit() Begin");

	if (handle == NULL)
	{
		rv = -1;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketInit(): check handle == NULL [%d]", rv);
		return rv;
	}
	//分配内存并初始化
	sh = (SCK_HANDLE *)malloc(sizeof(SCK_HANDLE));
	if (sh == NULL)
	{
		rv = -2;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketInit(): malloc err [%d]", rv);
		return rv;
	}
	memset(sh, 0, sizeof(SCK_HANDLE));

	//域赋值
	strcpy(sh->version, "0.0.1");
	strcpy(sh->serverip, "192.168.0.211");
	sh->serverport = 8888;

	//传出
	*handle = sh;

	ITCAST_LOG(__FILE__, __LINE__,LogLevel[1], rv,"func cltSocketInit() End");

	return rv;
}

//客户端发报文
ITCAST_FUNC_EXPORT(int)
cltSocketSend(void *handle, unsigned char *buf,  int buflen)
{
	int				rv = 0;
	SCK_HANDLE		*sh = NULL;

	if (handle == NULL)
	{
		rv = -4;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend(): check handle == NULL [%d]", rv);
		return rv;
	}
	if (buf == NULL || buflen<=0)
	{
		rv = -5;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend(): (buf == NULL || len<=0) [%d]", rv);
		return rv;
	}
	sh = (SCK_HANDLE *)handle;
	//如果有加密回调函数，则执行回调
	if (sh->myEncDataFunc != NULL)
	{
		sh->buf = (unsigned char *)malloc(sizeof(char)*(buflen+128));
		if (sh->buf == NULL)
		{
			return rv;
		}

		rv = sh->myEncDataFunc(buf, buflen, sh->buf, &(sh->buflen), sh->encRef, sh->encRefLen);
		if (rv != 0)
		{
			ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend(): (sh->myEncDataFunc [%d]", rv);
			return rv;
		}
	}
	else
	{
		sh->buf = (unsigned char *)malloc(sizeof(char)*buflen);
		if (sh->buf == NULL)
		{
			rv = -6;
			ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend() buflen:%d)", buflen);
			ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend() check (handle->buf == NULL)) [%d]", rv);
			return rv;
		}

		//把发送的报文数据，存储 handle 上下文之中
		memcpy(sh->buf, buf, buflen);
		sh->buflen = buflen;
	}
	return rv;
}
ITCAST_FUNC_EXPORT(int)
cltSocketSend_enc(void *handle, unsigned char *buf,  int buflen, EncData encDataCallbakFunc, void *ref, int refLen)
{
	int				rv = 0;
	SCK_HANDLE		*sh = NULL;

	if (handle == NULL)
	{
		rv = -4;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend(): check handle == NULL [%d]", rv);
		return rv;
	}
	if (buf == NULL || buflen<=0)
	{
		rv = -5;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend(): (buf == NULL || len<=0) [%d]", rv);
		return rv;
	}
	sh = (SCK_HANDLE *)handle;
	//如果有加密回调函数，则执行回调
	if (sh->myEncDataFunc != NULL)
	{
		sh->buf = (unsigned char *)malloc(sizeof(char)*(buflen+128));
		if (sh->buf == NULL)
		{
			return rv;
		}

		rv = encDataCallbakFunc(buf, buflen, sh->buf, &(sh->buflen), ref, refLen);
		if (rv != 0)
		{
			ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend(): (sh->myEncDataFunc [%d]", rv);
			return rv;
		}
	}
	else
	{
		sh->buf = (unsigned char *)malloc(sizeof(char)*buflen);
		if (sh->buf == NULL)
		{
			rv = -6;
			ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend() buflen:%d)", buflen);
			ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend() check (handle->buf == NULL)) [%d]", rv);
			return rv;
		}

		//把发送的报文数据，存储 handle 上下文之中
		memcpy(sh->buf, buf, buflen);
		sh->buflen = buflen;
	}
	return rv;
}
//客户端收报文
ITCAST_FUNC_EXPORT(int)
cltSocketRev(void *handle, unsigned char *buf, int *buflen)
{
	int			rv = 0;
	SCK_HANDLE	*sh = NULL;

	if (handle == NULL)
	{
		rv = -4;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketRev: check handle == NULL [%d]", rv);
		return rv;
	}
	if (buflen == NULL)
	{
		rv = -5;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketRev: (buflen == NULL) [%d]", rv);
		return rv;
	}

	sh = (SCK_HANDLE *)handle;

	//赋值 把上下文中的数据，copy到buf空间中
	//支持二次调用，第一次调用求长度 第二次调用可以把数据copy buf中
	if (buf != NULL)
	{
		memcpy(buf, sh->buf, sh->buflen);
		//buf[ci->buflen] = '\0';
	}
	*buflen = sh->buflen;

	return rv;
}
//客户端释放资源
ITCAST_FUNC_EXPORT(int)
cltSocketDestory(void *handle)
{
	SCK_HANDLE *sh = NULL;
	sh = handle; 
	if (sh != NULL)
	{
		if (sh->encRef != NULL)  free(sh->encRef);
		if (sh->decRef != NULL)  free(sh->decRef);
		if (sh->buf != NULL) free(sh->buf);
		free(sh);
	}
	return 0;
}

/////////////////第二套api实现/////////////////////////////////////////////////


//客户端初始化
ITCAST_FUNC_EXPORT(int)
cltSocketInit2(void **handle) //5day after
{
	SCK_HANDLE		*sh = NULL;
	int				rv = 0;

	ITCAST_LOG(__FILE__, __LINE__,LogLevel[1], rv,"func cltSocketInit2() Begin");

	if (handle == NULL)
	{
		rv = -1;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketInit2(): check handle == NULL [%d]", rv);
		return rv;
	}
	//分配内存并初始化
	sh = (SCK_HANDLE *)malloc(sizeof(SCK_HANDLE));
	if (sh == NULL)
	{
		rv = -2;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketInit2(): malloc err [%d]", rv);
		return rv;
	}
	memset(sh, 0, sizeof(SCK_HANDLE));

	//域赋值
	strcpy(sh->version, "0.0.1");
	strcpy(sh->serverip, "192.168.0.211");
	sh->serverport = 8888;

	//传出
	*handle = sh;

	ITCAST_LOG(__FILE__, __LINE__,LogLevel[1], rv,"func cltSocketInit2() End");

	return rv;
}

//客户端发报文
ITCAST_FUNC_EXPORT(int)
cltSocketSend2(void *handle, unsigned char *buf,  int buflen)
{
	int				rv = 0;
	SCK_HANDLE		*sh = NULL;

	if (handle == NULL)
	{
		rv = -4;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend2(): check handle == NULL [%d]", rv);
		return rv;
	}
	if (buf == NULL || buflen<=0)
	{
		rv = -5;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend2(): (buf == NULL || len<=0) [%d]", rv);
		return rv;
	}

	sh = (SCK_HANDLE *)handle;
	sh->buf = (unsigned char *)malloc(sizeof(char)*buflen);
	if (sh->buf == NULL)
	{
		rv = -6;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend2() buflen:%d)", buflen);
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketSend2() check (handle->buf == NULL)) [%d]", rv);
		return rv;
	}

	//把发送的报文数据，存储 handle 上下文之中
	memcpy(sh->buf, buf, buflen);
	sh->buflen = buflen;

	return rv;
}
//客户端收报文
ITCAST_FUNC_EXPORT(int)
cltSocketRev2(void *handle, unsigned char **buf, int *buflen)
{
	int			rv = 0;
	SCK_HANDLE	*sh = NULL;

	if (handle == NULL)
	{
		rv = -4;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketRev2: check handle == NULL [%d]", rv);
		return rv;
	}
	if (buflen == NULL)
	{
		rv = -5;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketRev2: (buflen == NULL) [%d]", rv);
		return rv;
	}
	sh = (SCK_HANDLE *)handle;


	//分配内存数据传出
	*buf = (char *)malloc(sh->buflen);
	if (*buf == NULL)
	{
		rv = -6;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketRev2: (buflen == NULL) [%d]", rv);
		return rv;
	}
	memcpy(*buf, sh->buf, sh->buflen);

	*buflen = sh->buflen;

	return rv;
}

ITCAST_FUNC_EXPORT(int)
cltSocketRev2_Free(unsigned char **buf)
{
	int rv = 0;
	unsigned char * tmp = *buf;
	if (buf == NULL)
	{
		rv = -7;
		ITCAST_LOG(__FILE__, __LINE__,LogLevel[4], rv,"func cltSocketRev2: (buflen == NULL) [%d]", rv);
		return rv;
	}
	if (tmp != NULL)
	{
		free(tmp);
	}
	*buf = NULL;
	return 0;
}

//客户端释放资源
ITCAST_FUNC_EXPORT(int)
cltSocketDestory2(void **handle)
{
	SCK_HANDLE *sh = NULL;
	sh = *handle; 
	if (sh != NULL)
	{
		free(sh->buf);
		free(sh);
	}
	*handle = NULL;
	return 0;
}


ITCAST_FUNC_EXPORT(int)
clitSocket_SetEncFunc(void *handle, EncData encDataCallbak, void *ref, int refLen)
{
	
	SCK_HANDLE *sh = NULL;
	sh = (SCK_HANDLE *)handle;
	sh->myEncDataFunc  = encDataCallbak;

	if (refLen > 0)
	{
		sh->encRef = (void *)malloc(refLen);
		if (sh->encRef  == NULL)
		{
			return -1;
		}
		memcpy(sh->encRef, ref, refLen);
		sh->encRefLen = refLen;
	}

	return 0;
}


