#include<cstdlib>
#include "Goods.h"
#include<new>
using namespace std;

int Goods::totalWight = 0;
Goods::Goods(int w) :wight(w)
{
	Goods::Next = NULL;
	totalWight += w;
}
Goods::~Goods()
{
	totalWight -= wight;
}

int Goods::getTotalWeight()
{
	return totalWight;
}

GoodsQueue::GoodsQueue() : front(NULL), rear(NULL)
{
}

GoodsQueue::~GoodsQueue()
{
	Goods* temp = this->front;
	Goods* pointer = NULL;
	while (temp)
	{
		pointer = temp;
		temp = temp->Next;
		delete pointer;
	}
}

void GoodsQueue::push(int wight)
{
	set_new_handler(0);
	Goods* good = new Goods(wight);

	if (this->front == NULL)
	{
		this->front = this->rear = good;
	}
	else
	{
		this->rear->Next = good;
		rear = rear->Next;
	}
}

void GoodsQueue::pop()
{
	Goods * tempGood;
	if (this->front==NULL)
	{
		return;
	}
	tempGood = this->front;
	this->front = this->front->Next;
	delete tempGood;


}

Shop::Shop(GoodsQueue * goodsQueue) :goodsQueue(goodsQueue)
{

}
Shop::~Shop()
{
	if (goodsQueue!=NULL)
	{
		delete goodsQueue;
	}
}
void Shop::purchase(int w)
{
	goodsQueue->push(w);
}
void Shop::sale()
{
	goodsQueue->pop();
}
int Shop::getTotalWeight()
{
	return Goods::getTotalWeight();
}