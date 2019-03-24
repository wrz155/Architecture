
#include <iostream>
using namespace std;

/*
多态成立的三个条件 
	1)要有继承  
	2)虚函数重写  
	3)父类指针指向子类对象 
*/
class Parent
{
public:
	Parent(int a = 0)
	{
		this->a_ = a;
	}

	virtual void print()  //1 动手脚  写virtal关键字 会特殊处理 //虚函数表
	{
		cout<<"my is parent  1"<<endl;
	}
	virtual void print2()  //1 动手脚  写virtal关键字 会特殊处理 //虚函数表
	{
		cout << "my is parent  2" << endl;
	}
private:
	int a_;
};

class Child : public Parent
{
public:
	Child(int a = 0, int b = 0) :Parent(a)
	{
		this->b_ = b;
	}

	virtual void print()
	{
		cout<<"my is son"<<endl;
	}
private:
	int b_;
};

//有多态发生  //2 动手脚  
//效果:传来子类对 执行子类的print函数 传来父类对执行父类的print函数 
//C++编译器根本不需要区分是子类对象 还是父类对象
//父类对象和子类对象分步有vptr指针 , ==>虚函数表===>函数的入口地址
//迟绑定 (运行时的时候,c++编译器才去判断)
void HowToPlay(Parent *base)
{
	base->print(); 
}

int mian()
{
	//3 动手脚 提前布局  
	//用类定义对象的时候 C++编译器会在对象中添加一个vptr指针 
	//子类里面也有一个vptr指针
	Parent	p1; 
	Child	c1; 

	HowToPlay(&p1);
	HowToPlay(&c1);

	cout<<"hello..."<<endl;
	system("pause");
	return 0;
}