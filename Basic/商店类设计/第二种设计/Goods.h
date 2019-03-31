#pragma once
#ifndef _GOODS_H_
#define _GOODS_H_

class Goods
{
public:
	Goods(int w);
	~Goods();
	Goods * Next;
   static int getTotalWeight();
private:
	int wight;
    static	int totalWight;

};

class GoodsQueue
{

public:
	GoodsQueue();
	~GoodsQueue();
	void pop();
	void push(int wight);


private:
	Goods * front;	/*头*/
	Goods * rear;	/*尾*/
};


class Shop
{
public:
	Shop(GoodsQueue * goodsQueue);
	~Shop();
	void purchase(int w);
	void sale();
	int getTotalWeight();


private:
	GoodsQueue * goodsQueue;
};


#endif