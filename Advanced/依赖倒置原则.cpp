/*
依赖倒置原则出发点：相对于细节的多变性，抽象的东西要稳定的多。
以抽象为基础搭建起来的架构比以细节为基础搭建起来的架构要稳定的多。
通过抽象（抽象类或接口）使各个类或模块的实现彼此独立，不相互影响，实现模块间的松耦合。
使用接口或者抽象类的目的是制定好规范和契约，而不去涉及任何具体的操作，把展现细节的任务交给他们的实现类去完成。这也是开闭原则的基础。

依赖倒置原则的三种实现方式:
(1).通过构造函数传递依赖对象；
		比如在构造函数中的需要传递的参数是抽象类或接口的方式实现。
(2).通过setter方法传递依赖对象；
		即在我们设置的set方法中的参数为抽象类或接口，来实现传递依赖对象。
(3).接口声明实现依赖对象，也叫接口注入；
       即在函数声明中参数为抽象类或接口，来实现传递依赖对象，从而达到直接使用依赖对象的目的。
       可总结为接口传递，构造方法传递和setter方法传递。
	   依赖倒置原则的核心就是要我们面向接口编程，理解了面向接口编程，也就理解了依赖倒置；

依赖倒置原则使用总结：
	(1).低层模块尽量都要有抽象类或接口，或者两者都有。
	(2).变量的声明类型尽量是抽象类或接口。
	(3).使用继承时遵循里氏替换原则。

*/
#include <iostream>
using namespace std;

//让 Computer框架  和 具体的厂商 进行接耦合

class  HardDisk
{
public:
	virtual void work() = 0;
};

class  Memory
{
public:
	virtual void work() = 0;
};

class  Cpu
{
public:
	virtual void work() = 0;
};

class Computer
{
public:
	Computer(HardDisk *handdisk, Memory *memory, Cpu *cpu)
	{
		m_handdisk = handdisk;
		m_memory = memory;
		m_cpu = cpu;
	}
	// HardDisk
	// Memory
	// Cpu
public:
	void work()
	{
		m_handdisk->work();
		m_memory->work();
		m_cpu->work();
	}
protected:
private:
	HardDisk *m_handdisk;
	Memory *m_memory;
	Cpu *m_cpu;
};


class  InterCpu : public Cpu
{
public:
	void work()
	{
		cout << "我是iterl cpu 我工作良好" << endl;
	}
};


class  XSDisk : public HardDisk
{
public:
	void work()
	{
		cout << "我是西数硬盘 工作良好" << endl;
	}
};

class  JSDMem : public Memory
{
public:
	void work()
	{
		cout << "JSDMem 工作良好" << endl;
	}
};

void main()
{
	HardDisk * harddisk = NULL;
	Memory * memory = NULL;
	Cpu * cpu = NULL;

	harddisk = new XSDisk;
	memory  = new JSDMem;
	cpu = new InterCpu;

	Computer *mycomputer = new Computer(harddisk ,memory,  cpu);

	mycomputer->work();

	delete mycomputer;
	delete cpu;
	delete memory;
	delete harddisk;

	cout<<"hello..."<<endl;
	system("pause");
	return ;
}