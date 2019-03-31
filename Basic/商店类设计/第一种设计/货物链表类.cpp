#include "iostream"
using namespace std;

//类的开发和设计，出现了两个模型
//1 贫血模型
//2 充血模型

//货物类
class Goods 
{ 
public :
	Goods(int  w) {
		weight = w;  
		total_weight += w; 
	}
	~ Goods() { 
		total_weight -= weight ; 
	}
	int  Weight() { 
		return  weight ; 
	}

	static  int  TotalWeight() { 
		return  total_weight ; 
	}  
public:
	Goods *next ;								//最核心的地方
private :
	int  weight ;
	static  int  total_weight ;
} ;

int  Goods::total_weight = 0 ;

//业务操作函数 通过全局函数实现
void purchase(Goods *& head, Goods *& tail, int w)
{
	Goods *tmp = new Goods(w) ;
	tmp -> next = NULL ;
	if (head == NULL)
		head = tail = tmp ;
	else { 
		tail->next = tmp;
		tail = tail->next;
	}
}

void sale( Goods * & head , Goods * & tail )
{ 
	if ( head == NULL ) { 
		cout << "No any goods!\n" ;  
		return ; 
	}

	Goods *q = head ;  
	head = head -> next ;  
	delete q ;

	cout << "saled.\n" ;
}

void main()
{ 
	Goods * head = NULL, *tail = NULL;
	int  w;
	int  choice;

	do 
	{ 
		cout << "Please choice:\n" ;
		cout << "Key in 1 is purchase,\nKey in 2 is sale,\nKey in 0 is over.\n" ;
		cin >> choice ;
		switch ( choice )		
		{ 
		case 1 :							
			{  
				cout << "Input weight: " ;
				cin >> w ;
				purchase( head, tail, w ) ;		
				break ;
			}
		case 2 : 						
			{ 
				sale(head, tail);
			}       
		case 0 :  
			break;
		}
		cout << "Now total weight is:" << Goods::TotalWeight() << endl ; 
	} while ( choice ) ;
} 



