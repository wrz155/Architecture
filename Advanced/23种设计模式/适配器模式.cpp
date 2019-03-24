/*
@ Adapter模式也叫适配器模式，是构造型模式之一，通过Adapter模式可以改变已有类（或外部类）的接口形式。
@ 适用于：
	是将一个类的接口转换成客户希望的另外一个接口。使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
*/


#include <iostream>
using namespace std;

// Current18 
// Current220
// Adapter 

class  Current18v
{
public:
	virtual void useCurrent18v() = 0;
};

class  Current220v
{
public:
	void useCurrent220v()
	{
		cout << "我是220v 欢迎使用" << endl;
	}
};

class Adapter : public Current18v
{
public:
	Adapter(Current220v *current)
	{
		m_current = current;
	}
	virtual void useCurrent18v()
	{
		cout << "适配器 适配 220v ";
		m_current->useCurrent220v();
	}
protected:
private:
	Current220v *m_current;
};


void main()
{
	Current220v		*current220v = NULL;
	Adapter			*adapter = NULL;

	current220v = new Current220v;
	adapter = new Adapter(current220v);
	adapter->useCurrent18v();

	delete current220v;
	delete adapter;

	cout << "hello..." << endl;
	system("pause");
	return;
}