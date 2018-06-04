#include <iostream>
#include "MyClass.h"
#include "AClass.h"

AClass cls;
void myfun()
{
    cls.clsFun();
    ZengLingJun::MyClass *myCls = new ZengLingJun::MyClass();
    myCls->clsFun();
    delete myCls;
}

int main()
{
    AClass cc;
    std::cout << ZengLingJun::i << std::endl;
    return 0;
}
