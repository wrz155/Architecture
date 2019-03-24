#include<stdio.h>
#include<stdlib.h>
//int  *p

//const int *p   限定只能读不可以改，地址可以移动，可以看别人账户
//int const *p

//int * const p  限定不可以查看别人的账户，对自己账户可读可写

//const int * const p 限定只能看自己账户，只能读不可写
//int const * const p 

void main1()
{

	 const int num = 10;
	const int data = 20;//只有初始化的时候可以赋
	//data = 10; const限定了你不能随便修改
	const int *p = &num;//p是指向常量的指针
	p = &num;//const int *p限定权限，限定只能读，不能写
	//*p = 3;
	printf("%d", *p);

	getchar();


}
void  main2()
{
	int num = 10;
	int data = 20;
	int const *p = &num;  //const *p 限定写入的权限。
	p = &data;
	//*p = 3;
	printf("%d", *p);

	getchar();

}

void main3()
{
	int num = 10;
	int data = 20;
	int * const p = &num;
	//p = &data;//限定你吊死在一棵树上
	*p = 13;
	printf("%d", *p);
	getchar();



}

void  main()
{
	int num = 10;
	int data = 20;
	const int * const p = &data;//限定权限，只能看，不可以改，不可以看别人的账户
	//p = &num;
	//*p = 3;




}