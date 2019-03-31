/*
@ 工厂模式
@ 构成：
	抽象工厂（Creator）角色
		工厂方法模式的核心，任何工厂类都必须实现这个接口。
	具体工厂（ Concrete  Creator）角色
		具体工厂类是抽象工厂的一个实现，负责实例化产品对象。
	抽象（Product）角色
		工厂方法模式所创建的所有对象的父类，它负责描述所有实例所共有的公共接口。
	具体产品（Concrete Product）角色
		工厂方法模式所创建的具体实例对象

@ 工厂模式与简单工厂模式区别：
	工厂方法模式与简单工厂模式在结构上的不同不是很明显。
	工厂方法类的核心是一个抽象工厂类，而简单工厂模式把核心放在一个具体类上。 
	工厂方法模式之所以有一个别名叫多态性工厂模式是因为具体工厂类都有共同的接口，或者有共同的抽象父类。
	当系统扩展需要添加新的产品对象时，仅仅需要添加一个具体对象以及一个具体工厂对象，原有工厂对象不需要进行任何修改，
	也不需要修改客户端，很好的符合了“开放－封闭”原则。
	而简单工厂模式在添加新产品对象后不得不修改工厂方法，扩展性不好。工厂方法模式退化后可以演变成简单工厂模式。
	
	原来类的代码一点不用动，只需添加2个类，实现覆写函数，即能实现功能，而简单工厂模式需要修改原来类的代码。
@ 领悟：
	实现了client与具体产品、具体工厂之间的解耦和
*/

#include <iostream>
using namespace std;


class Fruit
{
public:
	virtual void  sayname() = 0;
};

class  AbFactory
{
public:
	virtual Fruit *CreateProduct() = 0;
};

class  Banana : public Fruit
{
public:
	void  sayname()
	{
		cout << "我是香蕉" << endl;
	}
};
class BananaFactory :public AbFactory
{
public:
	virtual Fruit *CreateProduct()
	{
		return new Banana;
	}
};

class  Apple : public Fruit
{
public:
	void  sayname()
	{
		cout << "我是 Apple" << endl;
	}
};
class AppleFactory :public AbFactory
{
public:
	virtual Fruit *CreateProduct()
	{
		return new Apple;
	}
};

//////////////////////////////////////////////////////////////////////////
//添加新的产品

class Pear : public Fruit
{
public:
	virtual void sayname()
	{
		cout << "我是 pear" << endl;
	}
protected:
private:
};
class PearFactory : public AbFactory
{
public:
	virtual Fruit *CreateProduct()
	{
		return new Pear;
	}
};



void main()
{
	AbFactory		*factory = NULL;
	Fruit			*fruit = NULL;

	//吃 香蕉
	factory = new BananaFactory;
	fruit = factory->CreateProduct();
	fruit->sayname();

	delete fruit;
	delete factory;

	//Pear 
	factory = new PearFactory;
	fruit = factory->CreateProduct();
	fruit->sayname();

	delete fruit;
	delete factory;


	cout << "hello..." << endl;
	system("pause");
	return;
}