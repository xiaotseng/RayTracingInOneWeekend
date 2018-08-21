#ifndef _MYCLASS_H_
#define _MYCLASS_H_
namespace ZengLingJun
{
extern int i; //声明全局变量
extern int name;
void print();
class MyClass
{
public:
  int i;
  static  int stddd;//声明了符号   ZenLingJun::MyClass::stddd
  int b;
  MyClass();
  void clsFun();
};
//int MyClass::stddd=1;//定义了符号   ZenLingJun::MyClass::stddd。为避免符号重定义因此不能写在头文件里。
} // namespace ZengLingJun

#endif