/*
@ 单例：懒汉式			使用的时候，手动创建
@ 构造方法：
	1)构造函数私有化
	2)提供一个全局的静态方法（全局访问点）
	3)在类中定义一个静态指针，指向本类的变量的静态变量指针
*/

#include <iostream>
using namespace std;

class Singleton
{
private:
	Singleton()
	{
		cout << "Singelton 构造函数执行" << endl;
	}
public:
	static Singleton *get_singelton()
	{
		if (singelton_ == NULL)
		{
			singelton_ = new Singleton;
		}
		return singelton_;
	}

	static void FreeSingelton()
	{
		if (singelton_ != NULL)
		{
			delete singelton_;
			singelton_ = NULL;
		}
	}

private:
	static Singleton *singelton_;
};

Singleton *Singleton::singelton_ = NULL;


void main()
{
	Singleton *single = Singleton::get_singelton();
	single->FreeSingelton();

}