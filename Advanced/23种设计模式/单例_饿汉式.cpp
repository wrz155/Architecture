/*
@ 单例：饿汉式
@ 构造方法：
	在懒汉式的基础上，将类中定义一个静态指针直接指向本类（不管本类有没有new对象）
*/

#include <iostream>
using namespace std;


//懒汉式
class Singelton
{
private:
	Singelton()
	{
		cout << "Singelton 构造函数执行" << endl;
	}
public:
	static Singelton *getInstance()
	{
		return m_psl;
	}

	static void FreeInstance()
	{
		if (m_psl != NULL)
		{
			delete m_psl;
			m_psl = NULL;
		}
	}

private:
	static Singelton *m_psl;
};

//饿汉式
Singelton *Singelton::m_psl = new Singelton;


void main01()
{
	//验证类的构造函数是在hello world之前调用
	printf("hello world\n");
	Singelton *p1 = Singelton::getInstance();
	Singelton *p2 = Singelton::getInstance();

	if (p1 == p2)
	{
		cout << "是同一个对象" << endl;
	}
	else
	{
		cout << "不是同一个对象" << endl;
	}
	Singelton::FreeInstance();

	return;
}

void main()
{
	main01();

	getchar();
}