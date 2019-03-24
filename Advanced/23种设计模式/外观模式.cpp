/*
@ Fa?ade
	为调用方, 定义简单的调用接口。
@ Clients
	调用者。通过Facade接口调用提供某功能的内部类群。
@ Packages
	功能提供者。指提供功能的类群（模块或子系统）
@ 适用于：
	为子系统中统一一套接口，让子系统更加容易使用。
*/


#include <iostream>
using namespace std;

class SubSystemA
{
public:
	void doThing()
	{
		cout << "SubSystemA run" << endl;
	}
};

class SubSystemB
{
public:
	void doThing()
	{
		cout << "SubSystemB run" << endl;
	}
};

class SubSystemC
{
public:
	void doThing()
	{
		cout << "SubSystemC run" << endl;
	}
};


class Facade
{
public:
	Facade()
	{
		sysA = new SubSystemA;
		sysB = new SubSystemB;
		sysC = new SubSystemC;
	}
	~Facade()
	{
		delete sysA;
		delete sysB;
		delete sysC;
	}
public:
	void doThing()
	{
		sysA->doThing();
		sysB->doThing();
		sysC->doThing();
	}
protected:
private:
	SubSystemA *sysA;
	SubSystemB *sysB;
	SubSystemC *sysC;
};

// 不同的使用方法
void main1801()
{
	SubSystemA *sysA = new SubSystemA;
	SubSystemB *sysB = new SubSystemB;
	SubSystemC *sysC = new SubSystemC;

	sysA->doThing();
	sysB->doThing();
	sysC->doThing();

	delete sysA;
	delete sysB;
	delete sysC;

	return;
}

void main1802()
{
	Facade *f = new Facade;
	f->doThing();
	delete f;

}

void main()
{
	//main1801();
	main1802();
	system("pause");
}