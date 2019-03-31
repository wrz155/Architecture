/*
开闭原则
　　类的改动是通过增加代码进行的，不是修改源代码。
*/
#include <iostream>
using namespace std;

class AbstractBankWorker {
public:
    virtual void doSomething() = 0;
};
class saveBankWorker : public AbstractBankWorker {
public:
    virtual void doSomething() {
        cout << "存款" << endl;
    }
};
class transBankWorker : public AbstractBankWorker {
public:
    virtual void doSomething() {
        cout << "转账" << endl;
    }
};
/*若现在想开通付款业务，只需要再继承基类，实现业务虚函数即可*/
class payBankWorker : public AbstractBankWorker {
public:
    virtual void doSomething() {
        cout << "付款" << endl;
    }
};

int main(int argc, char **argv) 
{
    /*
        产生多态的3个必要条件
        1.有继承
        2.要有重写
        3.父类指针指向子类对象
    */
    AbstractBankWorker *worker = NULL;
    worker = new saveBankWorker;
    worker->doSomething();
    delete worker;
    worker = NULL;
    return 0;
}