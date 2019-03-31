#include "iostream"
#include "cstdlib"
using namespace std;

/*
	1 函数模板可以像普通函数一样被重载
	2 C++编译器优先考虑普通函数
	3 如果函数模板可以产生一个更好的匹配，那么选择模板
	4 可以通过空模板实参列表的语法限定编译器只通过模板匹配
*/

/*
函数模板不允许自动类型转化
普通函数能够进行自动类型转换
*/

/*
函数模板的深入理

	― 编译器并不是把函数模板处理成能够处理任意类型的函数
	― 编译器从函数模板通过具体类型产生不同的函数
	― 编译器会对函数模板进行两次编译
	―在声明的地方对模板代码本身进行编译
	―在调用的地方对参数替换后的代码进行编译
*/

//template告诉编译器，这里开始进行泛型编程
//typename告诉编译器，类型名称为T 编译器你看到类型T（T为类型，可以参数化，int float）， 不要乱报错。。。。
//T为类型，类型参数化而已
template<typename T>
void swap2(T &a, T &b)
{
	T t = a;
	a = b;
	b = t;
}

int main()
{
	int x = 1;
	int y = 2;

	//泛型编程的调用方式分为两种
	//自动类型 推导调用
	swap2<int>(x, y);

	//printf("\n%d, %d", x, y);

	float x1 = 1.0;
	float y1 = 2.0;

	//具体类 显示调用
	swap2<float>(x1, y1);

	//printf("\n%f, %f", x1, y1);
	cout<<"hello...."<<endl;

	system("pause");
	return 0;
}