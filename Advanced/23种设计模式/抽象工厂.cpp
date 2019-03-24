/*
@ 抽象模式
@ 构成：
	1.抽象工厂（Creator）角色 
		抽象工厂模式的核心，包含对多个产品结构的声明，任何工厂类都必须实现这个接口。

	2.具体工厂（ Concrete  Creator）角色
		具体工厂类是抽象工厂的一个实现，负责实例化某个产品族中的产品对象。

	3.抽象（Product）角色
		抽象模式所创建的所有对象的父类，它负责描述所有实例所共有的公共接口。

	4.具体产品（Concrete Product）角色
		抽象模式所创建的具体实例对象

@ 工厂模式与抽象工厂区别：
	工厂模式中的一个具体工厂只能生产一个产品。（要么香蕉、要么苹果）
	抽象工厂中的一个具体工厂可以一下生产一个产品族（里面有很多产品组成）

@ 领悟
	具体产品具有双重属性：北方香蕉;南方苹果
	要把一个属性给抽象工厂；一个属性给具体工厂
*/

#include <iostream>
using namespace std;

class Fruit
{
public:
	virtual void SayName() = 0;
};

class AbstractFactory
{
public:
	virtual Fruit* CreateBanana() = 0;
	virtual Fruit* CreateApple() = 0;
};

class NorthBanana : public Fruit
{
public:
	virtual void SayName()
	{
		cout << "我是北方香蕉" << endl;
	}
};

class NorthApple : public Fruit
{
public:
	virtual void SayName()
	{
		cout << "我是北方苹果" << endl;
	}
};

class SourthBanana : public Fruit
{
public:
	virtual void SayName()
	{
		cout << "我是南方香蕉" << endl;
	}
};

class SourthApple : public Fruit
{
public:
	virtual void SayName()
	{
		cout << "我是南方苹果" << endl;
	}
};

class NorthFacorty : public AbstractFactory
{
	virtual Fruit * CreateBanana()
	{
		return new NorthBanana;
	}
	virtual Fruit * CreateApple()
	{
		return new NorthApple;
	}
};

class SourthFacorty : public AbstractFactory
{
	virtual Fruit * CreateBanana()
	{
		return new SourthBanana;
	}
	virtual Fruit * CreateApple()
	{
		return new SourthApple;
	}
};


void main()
{
	Fruit			*fruit = NULL;
	AbstractFactory *af = NULL;

	///--------------
	af = new SourthFacorty;
	fruit = af->CreateApple();
	fruit->SayName();
	delete fruit;
	fruit = af->CreateBanana();
	fruit->SayName();
	delete fruit;

	///------
	af = new NorthFacorty;
	fruit = af->CreateApple();
	fruit->SayName();
	delete fruit;
	fruit = af->CreateBanana();
	fruit->SayName();
	delete fruit;

	delete af;
	system("pause");
	return;
}