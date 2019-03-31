#include <iostream>

class Point
{
public:
	int get_x() {
		return x_;
	};
	int get_y() {
		return y_;
	};
	void set_point(int x, int y) {
		x_ = x;
		y_ = y;
	};

	
private:
	int x_;
	int y_;	
};

class Circle
{
public:
	void set_circle(int r, int x, int y) {
		r_ = r;
		x_ = x;
		y_ = y;
	};
	//类做函数参数的时候，类封装了属性和方法，在被调用函数里面， 不但可以使用属性，而且可以使用方法（成员函数）；
	//这也是面向对象和面向过程的一个重要区别
	bool IsPointInCircle(Point &point) {	
		int dd = (point.get_x() - x_)*(point.get_x() - x_) + (point.get_y() - y_)* (point.get_y() - y_);
		if (dd <= r_ * r_)
		{
			return true;							//圆形内部
		}
		else
		{
			return false;							//0点在圆外
		}
	
	};

private:
	int r_;
	int x_;
	int y_;
};



int main()
{
	Circle circle;
	Point point;

	circle.set_circle(2, 3, 3);
	point.set_point(7, 7);

	//在圆形1  不在圆内 0
	if (circle.IsPointInCircle(point))
	{
		std::cout << "点在圆形内" << std::endl;
	}
	else
	{
		std::cout << "点在圆形外" << std::endl;
	}

	getchar();
	return 0;
}