/*
抽象工厂模式实现对产品家族的创建，一个产品家族是这样的一系列产品：
	具有不同分类维度的产品组合，采用抽象工厂模式则是不需要关心构建过程，只关心什么产品由什么工厂生产即可。
	
而建造者模式则是要求按照指定的蓝图建造产品，它的主要目的是通过组装零配件而产生一个新产品，两者的区别还是比较明显的。
　　
现代化的汽车工厂能够批量生产汽车（不考虑手工打造的豪华车）。
不同的工厂生产不同的汽车，宝马工厂生产宝马牌子的车，奔驰工厂生产奔驰牌子的车。
车不仅具有不同品牌，还有不同的用途分类，如商务车Van，运动型车SUV等，我们按照两种设计模式分别实现车辆的生产过程。

注意看上面的描述，我们在抽象工厂模式中使用“工厂”来描述构建者，而在建造者模式中使用“车间”来描述构建者，
其实我们已经在说它们两者的区别了，抽象工厂模式就好比是一个一个的工厂，宝马车工厂生产宝马SUV和宝马VAN，奔驰车工厂生产奔驰车SUV和奔驰VAN，
它是从一个更高层次去看对象的构建，具体到工厂内部还有很多的车间，如制造引擎的车间、装配引擎的车间等，
但这些都是隐藏在工厂内部的细节，对外不公布。

也就是对领导者来说，他只要关心一个工厂到底是生产什么产品的，不用关心具体怎么生产。
而建造者模式就不同了，它是由车间组成，不同的车间完成不同的创建和装配任务，
一个完整的汽车生产过程需要引擎制造车间、引擎装配车间的配合才能完成，它们配合的基础就是设计蓝图，
而这个蓝图是掌握在车间主任（导演类）手中，它给建造车间什么蓝图就能生产什么产品，建造者模式更关心建造过程。
虽然从外界看来一个车间还是生产车辆，但是这个车间的转型是非常快的，只要重新设计一个蓝图，即可产生不同的产品，这有赖于建造者模式的功劳。

相对来说，抽象工厂模式比建造者模式的尺度要大，它关注产品整体，而建造者模式关注构建过程，
因此建造者模式可以很容易地构建出一个崭新的产品，只要导演类能够提供具体的工艺流程。
也正因为如此，两者的应用场景截然不同，如果希望屏蔽对象的创建过程，只提供一个封装良好的对象，则可以选择抽象工厂方法模式。
而建造者模式可以用在构件的装配方面，如通过装配不同的组件或者相同组件的不同顺序，可以产生出一个新的对象，它可以产生一个非常灵活的架构，
方便地扩展和维护系统。

*/


// 建造着模式可以  可以混合创建，一辆车由BMW的引擎和BZNE的车身，而工厂模式就不好创建了。
#include <iostream>
using namespace std;

#include "string"

class House
{
public:
	void setDoor(string door)
	{
		this->m_door = door;
	}

	void setWall(string wall)
	{
		this->m_wall = wall;
	}
	void setWindow(string window)
	{
		this->m_window = window;
	}

	//--
	string getDoor( )
	{
		cout << m_door << endl;
		return this->m_door ;
	}

	string getWall()
	{
		cout << m_wall << endl;
		return this->m_wall;
	}
	string getWindow()
	{
		cout << m_window << endl;
		return m_window;
	}

private:
	string	m_door;
	string	m_wall;
	string	m_window;
};

class  Builder
{
public:
	virtual void buildWall() = 0;
	virtual void buildDoor() = 0;
	virtual void buildWindow() = 0;
	virtual House* getHouse() = 0;
};

//公寓工程队
class  FlatBuilder : public Builder
{
public:
	FlatBuilder()
	{
		m_house = new House;
	}
	virtual void buildWall()
	{
		m_house->setWall(" flat wall");
	}

	virtual void buildDoor()
	{
		m_house->setDoor("flat door");
	}

	virtual void buildWindow()
	{
		m_house->setWindow("flat window");
	}

	virtual House* getHouse()
	{
		return m_house;
	}
private:
	House *m_house;
};

//别墅 villa 工程队
class  VillaBuilder : public Builder
{
public:
	VillaBuilder()
	{
		m_house = new House;
	}
	virtual void buildWall()
	{
		m_house->setWall(" villa wall");
	}

	virtual void buildDoor()
	{
		m_house->setDoor("villa door");
	}

	virtual void buildWindow()
	{
		m_house->setWindow("villa window");
	}

	virtual House* getHouse()
	{
		return m_house;
	}
private:
	House *m_house;
};

//设计师(指挥者) 负责建造逻辑  
//建筑队 干具体的活
class Director 
{
public:
	Director( Builder * build)
	{
		m_build = build;
	}
	void Construct()
	{
		m_build_1->buildWall();
		m_build_1->buildWindow();
		m_build_2->buildDoor();
	}
private:
	 VillaBuilder * m_build_1;
	 FlatBuilder *m_build_2;
};


void main()
{
	House		*house  = NULL;
	Builder		*builder = NULL;
	Director	*director = NULL;

	// 请VillaBuilder 建造别墅的工程队
	builder = new VillaBuilder;

	//设计师 指挥 工程队 干活
	director = new Director(builder);
	director->Construct(); 
	house  =  builder->getHouse();
	house->getWindow();
	house->getDoor();

	delete house;
	delete builder;

	//请 FlatBuilder 公寓
	builder = new FlatBuilder;
	director = new Director(builder);
	director->Construct(); 
	house  =  builder->getHouse();
	house->getWindow();
	house->getDoor();
	delete house;
	delete builder;


	delete director;
	system("pause");
	return ;
}