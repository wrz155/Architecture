/*
@ Visitor模式也叫访问者模式，是行为模式之一，它分离对象的数据和行为，
	使用Visitor模式，可以不修改已有类的情况下，增加新的操作角色和职责。

@ 抽象访问者（Visitor）角色：声明了一个或者多个访问操作，形成所有的具体元素角色必须实现的接口。
@ 具体访问者（ConcreteVisitor）角色：实现抽象访问者角色所声明的接口，也就是抽象访问者所声明的各个访问操作。
@ 抽象节点（Element）角色：声明一个接受操作，接受一个访问者对象作为一个参量。
@ 具体节点（ConcreteElement）角色：实现了抽象元素所规定的接受操作。
@ 结构对象（ObiectStructure）角色：有如下的一些责任，可以遍历结构中的所有元素；如果需要，提供一个高层次的接口让访问者对象可以访问每一个元素；如果需要，可以设计成一个复合对象或者一个聚集，如列（List）或集合（Set）。

@ 适用于：
	把数据结构 和 作用于数据结构上的操作 进行解耦合;
	适用于数据结构比较稳定的场合
@ 访问者模式总结：
	访问者模式优点是增加新的操作很容易，因为增加新的操作就意味着增加一个新的访问者。访问者模式将有关的行为集中到一个访问者对象中。
	那访问者模式的缺点是是增加新的数据结构变得困难了

*/


#include <iostream>
#include <list>
using namespace std;

// Visitor  ParkElement

class ParkElement;

class Visitor
{
public:
	virtual void visit(ParkElement *parkelement) = 0;
};

class ParkElement
{
public:
	virtual void accept(Visitor *visit) = 0;
};

class  ParkA : public ParkElement
{
public:
	virtual void accept(Visitor *v)
	{
		v->visit(this); //公园接受访问者访问 让访问者做操作
	}
};


class  ParkB : public ParkElement
{
public:
	virtual void accept(Visitor *v)
	{
		v->visit(this); //公园接受访问者访问 让访问者做操作
	}

};

//整个公园 
class Park : public ParkElement
{
public:
	Park()
	{
		m_list.clear();
	}
	void setParkElement(ParkElement *pe)
	{
		m_list.push_back(pe);
	}

public:
	virtual void accept(Visitor *v)
	{
		//v->visit(this); //公园接受访问者访问 让访问者做操作

		for (list<ParkElement *>::iterator it = m_list.begin(); it != m_list.end(); it++)
		{
			(*it)->accept(v);  //公园A 公园B 接受 管理者v访问
		}
	}

private:
	list<ParkElement *> m_list; //公园的每一部分  //应该让公园的每一个部分 都让 管理者访问
};

class VisitorA : public Visitor
{
public:
	virtual void visit(ParkElement *parkelement)
	{
		cout << "清洁工A 完成 公园A部分的 打扫 " << endl; //parkelement->getName();
	}
};

class VisitorB : public Visitor
{
public:
	virtual void visit(ParkElement *parkelement)
	{
		cout << "清洁工B 完成 公园B部分的 打扫 " << endl; //parkelement->getName();
	}
};

class ManagerVisitor : public Visitor

{
public:
	virtual void visit(ParkElement *parkelement)
	{
		cout << "管理者 访问公园 的 各个部分 " << endl; //parkelement->getName();
	}
};

void main27_01()
{
	Visitor *vA = new  VisitorA;
	Visitor *vB = new  VisitorB;

	ParkA *parkA = new ParkA;
	ParkB *parkB = new ParkB;

	//
	parkA->accept(vA);
	parkB->accept(vB);

	delete vA;
	delete vB;
	delete parkA;
	delete parkB;
}

void main27_02()
{
	Visitor *vManager = new  ManagerVisitor;
	Park *park = new Park;

	ParkElement *parkA = new ParkA;
	ParkElement *parkB = new ParkB;

	park->setParkElement(parkA);
	park->setParkElement(parkB);

	//整个公园 接受 管理者访问
	park->accept(vManager);

	delete parkA;
	delete parkB;
	delete park;
	delete vManager;
}

void main()
{
	//main27_01();
	main27_02();
	cout << "hello..." << endl;
	system("pause");
	return;
}