/*
@ 简单工厂模式（不属于23种设计模式之中,不符合开闭原则）
@ 定义：
	通过专门定义一个类来负责创建其他类的实例，被创建的实例通常都具有共同的父类。
@ 构成：
	1.工厂（Creator）角色
		简单工厂模式的核心，它负责实现创建所有实例的内部逻辑。工厂类可以被外界直接调用，创建所需的产品对象。
	2.抽象（Product）角色
		抽象类
		简单工厂模式所创建的所有对象的父类，它负责描述所有实例所共有的公共接口。
	3.具体产品（Concrete Product）角色
		对抽象类进行覆写
		简单工厂模式所创建的具体实例对象	

@ 领悟：
	工厂类像是作了一层封装，决定基类指针指向哪个派生类。
	和多态相比，必须自己手动将基类指针指向哪个具体的派生类，有了简单工厂模式就不用了。
*/


#include <iostream>
using namespace std;

//定义抽象类
class Fruit
{
public:
	virtual void getFruit() = 0;

protected:
private:
};

class Banana : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "我是香蕉...." << endl;
	}
protected:
private:
};

class Apple : public Fruit
{
public:
	virtual void getFruit()
	{
		cout << "我是苹果...." << endl;
	}
protected:
private:
};


class Factory
{
public:
	Fruit *create(char *p)
	{

		if (strcmp(p, "banana") == 0)
		{
			return new Banana;
		}
		else if (strcmp(p, "apple") == 0)
		{
			return new Apple;
		}
		else
		{
			printf("不支持\n");
			return NULL;
		}
	}
};


void main()
{
	Factory *f = new Factory;
	Fruit *fruit = NULL;

	//工厂 生产 香蕉
	//返回的是指向派生类的基类指针
	//工厂类像是作了一层封装，决定基类指针指向哪个派生类
	//以前的多态，必须自己手动将基类指针指向哪个具体的派生类，有了简单工厂模式就不用了
	
	fruit = f->create("banana");
	fruit->getFruit();
	delete fruit;


	fruit = f->create("apple");
	fruit->getFruit();
	delete fruit;

	delete f;

	cout << "hello..." << endl;
	getchar();
	return;
}