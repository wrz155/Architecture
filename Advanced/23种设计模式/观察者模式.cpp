/*
@ Observer模式是行为模式之一，它的作用是当一个对象的状态发生变化时，能够自动通知其他关联对象，自动刷新对象状态。
@ Observer模式提供给关联对象一种同步通信的手段，使某个对象与依赖它的其他对象之间保持状态同步。

@ Subject（被观察者）
	被观察的对象。当需要被观察的状态发生变化时，需要通知队列中所有观察者对象。
	Subject需要维持（添加，删除，通知）一个观察者对象的队列列表。
@ ConcreteSubject
	被观察者的具体实现。包含一些基本的属性状态及其他操作。
@ Observer（观察者）
	接口或抽象类。当Subject的状态发生变化时，Observer对象将通过一个callback函数得到通知。
@ ConcreteObserver
	观察者的具体实现。得到通知后将完成一些具体的业务逻辑处理。

- 侦听事件驱动程序设计中的外部事件
- 侦听/监视某个对象的状态变化
- 发布者/订阅者(publisher/subscriber)模型中，当一个外部事件（新的产品，消息的出现等等）被触发时，通知邮件列表中的订阅者
								
@ 适用于：
	定义对象间一种一对多的依赖关系，使得每一个对象改变状态，则所有依赖于他们的对象都会得到通知。

@ 使用场景：
	定义了一种一对多的关系，让多个观察对象（公司员工）同时监听一个主题对象（秘书），
	主题对象状态发生变化时，会通知所有的观察者，使它们能够更新自己。
*/

#include <iostream>
#include <string>
#include <list>
using namespace std;

class Secretary;


//观察者 
class PlayserObserver
{
public:
	PlayserObserver(Secretary *secretary)
	{
		this->m_secretary = secretary;
	}
	void update(string action)
	{
		cout << "action:" << action << endl;
		cout << "老板来了 我很害怕啊..." << endl;

	}
private:
	Secretary *m_secretary;
};
//
class Secretary
{
public:
	Secretary()
	{
		m_list.clear();
	}
	void Notify(string info)
	{
		//给所有的 观察者 发送 情报
		for (list<PlayserObserver *>::iterator it = m_list.begin(); it != m_list.end(); it++)
		{
			(*it)->update(info); //
		}
	}

	void setPlayserObserver(PlayserObserver *o)
	{
		m_list.push_back(o);
	}

private:
	list<PlayserObserver *> m_list;
};

void main()
{
	Secretary			*secretary = NULL;
	PlayserObserver		*po1 = NULL;
	PlayserObserver		*po2 = NULL;

	secretary = new Secretary;
	po1 = new PlayserObserver(secretary);
	po2 = new PlayserObserver(secretary);

	secretary->setPlayserObserver(po1);
	secretary->setPlayserObserver(po2);

	secretary->Notify("老板来了");
	secretary->Notify("老板走了");
	delete secretary;
	delete po1;
	delete po2;

	system("pause");
	return;
}