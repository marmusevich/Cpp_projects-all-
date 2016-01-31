#include <iostream>
#include <cstdio>

using namespace std;

class B
{
public:
    virtual void Foo()
    {
        cout <<"B" <<endl;
    }
};

class D1 :public B
{
public:
    void Foo()
    {
        cout <<"D" <<endl;
    }
};
class D2 :public D1
{
public:
};


int main()
{
    B *p, b;
    D2 d2;
    p = &b;
    p->Foo();
    p = &d2;
    p->Foo();


    return 0;
}

