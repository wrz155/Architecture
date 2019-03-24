/*
@ 单例：懒汉式
@ 构造方法：
	1)构造函数私有化
	2)提供一个全局的静态方法（全局访问点）
	3)在类中定义一个静态指针，指向本类的变量的静态变量指针
*/

#include <iostream>
using namespace std;

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
		if (m_psl == NULL)
		{
			m_psl = new Singelton;
		}
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

Singelton *Singelton::m_psl = NULL;


void main01()
{

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

}

void main()
{
	main01();

	getchar();
}