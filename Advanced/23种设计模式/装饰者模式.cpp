/*
@ 装饰（ Decorator ）模式又叫做包装模式。
	通过一种对客户端透明的方式来扩展对象的功能，是继承关系的一个替换方案。
	装饰模式就是把要添加的附加功能分别放在单独的类中，并让这个类包含它要装饰的对象，
	当需要执行时，客户端就可以有选择地、按顺序地使用装饰功能包装对象。

@ 适用于：
	装饰者模式（Decorator?Pattern）动态的给一个对象添加一些额外的职责。就增加功能来说，此模式比生成子类更为灵活。
*/

#include <iostream>
using namespace std;

class Car
{
public:
	virtual void show() = 0;
};

class RunCar : public Car
{
public:
	virtual void show()
	{
		cout << "可以跑" << endl;
	}
protected:
private:
};


class SwimCarDirector : public Car
{
public:
	SwimCarDirector(Car *car)
	{
		m_car = car;
	}
	void swim()
	{
		cout << "可以游" << endl;
	}
	virtual void show()
	{
		m_car->show();
		swim();
	}
protected:
private:
	Car *m_car;
};

class  FlyCarDirector : public Car
{
public:
	FlyCarDirector(Car *car)
	{
		m_car = car;
	}
	void fly()
	{
		cout << "可以飞" << endl;
	}
	virtual void show()
	{
		m_car->show();
		fly();
	}

private:
	Car *m_car;
};

void main()
{
	Car * mycar = NULL;
	mycar = new RunCar;
	printf("-----000\n");
	mycar->show();

	printf("-----aaa\n");

	FlyCarDirector *flycar = new FlyCarDirector(mycar);
	flycar->show();

	printf("-----bbb\n");
	SwimCarDirector *swimcar = new SwimCarDirector(flycar);
	swimcar->show();

	delete swimcar;
	delete flycar;
	delete mycar;

	system("pause");
	return;
}