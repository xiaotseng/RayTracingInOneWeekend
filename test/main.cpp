#include <iostream>
#include "MyClass.h"
#include "AClass.h"
using namespace std;
AClass cls;
void myfun(){
    cls.clsFun();
    MyClass myCls;
    myCls.clsFun();
}
int main(){
    AClass cc;
    cout<<sizeof(cc)<<endl;
    return 0;}
