#include<iostream>
#include"Goods.h"
using namespace std;


void main()
{
	int i;
	GoodsQueue * goodsQueue=new GoodsQueue;
	Shop shop(goodsQueue);
	puts("-------可进行的业务操作---------");
	puts("---------1、购买货物-------------");
	puts("---------2、卖出货物-------------");
	puts("---------3、获取总存货量----------");
	puts("------------0、退出----------------");

	cout << "请选择要操作的业务:" << endl;
	cin >> i;

	while (i)
	{
		if (i == 1)
		{
			int wieght;
			cout << "请输入购买获取的重量:" << endl;
			cin >> wieght;
			shop.purchase(wieght);
			cout << "购买成功!" << endl;
		}
		else if (i == 2)
		{
			shop.sale();
			cout << "售出成功!" << endl;
		}
		else if (i == 3)
		{
			cout << "剩余的总库存量为:" << shop.getTotalWeight() << endl;
		}
		else
		{
			cout << "没有相应的操作，请重新选择操作" << endl;
		}

		cout << "请选择要操作的业务:" << endl;
		cin >> i;
	}

	system("pause");

}