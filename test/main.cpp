#include <iostream>
#include "MyClass.h"
#include "AClass.h"

AClass cls;
void myfun(){
    cls.clsFun();
    MyClass myCls;
    myCls.clsFun();
}

int main(){
    AClass cc;
    std::cout<<kele::i<<std::endl;
    return 0;}
