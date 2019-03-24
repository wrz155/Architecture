/*
@ 一些应用提供了内建（build in）的脚本或者宏语言来让用户可以定义他们能够在系统中进行的操作。
	Interpreter模式的目的就是使用一个解释器为用户提供一个一门定义语言的语法表示的解释器，然后通过这个解释器来解释语言中的句子

@ Context
	解释器上下文环境类。用来存储解释器的上下文环境，比如需要解释的文法等。 
	用来保存输入，输出值
@ AbstractExpression
	解释器抽象类。
@ ConcreteExpression
	解释器具体实现类。
	具体解释器的名称是对输入进行哪种操作的标识
*/


#include <iostream>
using namespace std;

// Context 

// Expression 

// PlusExpression   MinusExpression 

class Context
{
public:
	Context(int num)
	{
		this->m_num = num;
	}

	int getNum()
	{
		return m_num;
	}
	void setNum(int num)
	{
		this->m_num = num;
	}

	int getRes()
	{
		return m_res;
	}
	void  setRes(int res)
	{
		this->m_res = res;
	}

private:
	int m_num;
	int m_res;
};

class Expression
{
public:
	virtual void  interpreter(Context *context) = 0;
private:
	Context *m_context;
};


//加法解释器
class PlusExpression : public Expression
{
public:
	PlusExpression()
	{
		this->context = NULL;
	}
	virtual void  interpreter(Context *context)
	{
		int num = context->getNum();
		num++;
		context->setNum(num);
		context->setRes(num);
	}
private:
	Context *context;
};

//减法解释器
class MinusExpression : public Expression
{
public:
	MinusExpression()
	{
		this->context = NULL;
	}
	virtual void  interpreter(Context *context)
	{
		int num = context->getNum();
		num--;
		context->setNum(num);
		context->setRes(num);
	}
private:
	Context *context;
};



void main()
{
	Context *context = NULL;
	context = new Context(10);

	Expression *expression = NULL;
	Expression *expression2 = NULL;

	cout << context->getNum() << endl;

	expression = new PlusExpression;
	expression->interpreter(context);

	cout << context->getRes() << endl;

	//////////////////////////////////////////////////////////////////////////
	expression2 = new MinusExpression;
	expression2->interpreter(context);
	cout << context->getRes() << endl;


	cout << "hello..." << endl;
	system("pause");
	return;
}