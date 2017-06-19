#include <iostream>
//#include <stdio.h>

using namespace std;

class A
{
public:
    A()
    {
        cout <<"ctor A " <<endl;
    }
    ~A()
    {
        cout <<"dtor A " <<endl;
    }
};


class B
{
public:
    B()
    {
        cout <<"ctor B " <<endl;
    }
    ~B()
    {
        cout <<"dtor B " <<endl;
    }
};

class C
{
public:
    A a;
    B b;
};



int main()
{

       cout <<"__LINE__ " <<__LINE__  <<endl;

//    C *pc;
//    pc = new C();
//    delete pc;
    return 0;
}

