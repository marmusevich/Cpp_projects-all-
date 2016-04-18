#include <iostream>
using namespace std;

template<class T> void kill(T *& op)
{
    delete op;
}
class m{};


int main()
{
    m *mp = new m();
    kill(mp);
    //kill(mp);

    return 0;
}

