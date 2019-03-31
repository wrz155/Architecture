/*
@ Proxy模式又叫做代理模式，是构造型的设计模式之一，它可以为其他对象提供一种代理（Proxy）以控制对这个对象的访问。
-所谓代理，是指具有与代理元（被代理的对象）具有相同的接口的类，
-客户端必须通过代理与被代理的目标类交互，而代理一般在交互的过程中（交互前后），进行某些特别的处理。

@ subject（抽象主题角色）：
	真实主题与代理主题的共同接口。
@ RealSubject（真实主题角色）：
??	定义了代理角色所代表的真实对象。
@ Proxy（代理主题角色）：
?	含有对真实主题角色的引用，代理角色通常在将客户端调用传递给真是主题对象之前或者之后执行某些操作，而不是单纯返回真实的对象。
			
@ 适合于：
	为其他对象提供一种代理以控制对这个对象的访问。
	提示：a中包含b类；a、b类实现协议类protocol
*/


#include <iostream>
using namespace std;

class Subject
{
public:
	virtual void sailbook() = 0;
};

class RealSubjectBook : public Subject
{
public:
	virtual void sailbook()
	{
		cout << "卖书" << endl;
	}
};

//a中包含b类；a、b类实现协议类protocol 
class dangdangProxy : public Subject
{
public:
	virtual void sailbook()
	{
		RealSubjectBook *rsb = new RealSubjectBook;
		dazhe();
		rsb->sailbook();
		dazhe();
	}
public:
	void dazhe()
	{
		cout << "双十一打折" << endl;
	}
private:
	Subject *m_subject;
};

void main()
{
	Subject *s = new dangdangProxy;
	s->sailbook();
	delete s;
	system("pause");
	return;
}