# C++知识点汇总

## 在类的成员函数中能不能调用delete this？

答案是肯定的，能调用!

## 构造函数初始化时必须采用初始化列表一共有三种情况？

1.需要初始化的数据成员是对象(继承时调用基类构造函数)
2.需要初始化const修饰的类成员
3.需要初始化引用成员数据

## 当一个类A中没有声命任何成员变量与成员函数这时sizeof(A)的值是多少?

通常是1，用作占位的。为了确保不同对象有不同的地址。

实验：
```
#include <iostream>
#include <stdio.h>

class A
{

};

int main() {
    A a;
    printf("sizeof(A) = %d\n",sizeof(a));  // sizeof(A) = 1
    return 0;
}
```
## 析构函数什么情况下定义为虚函数？

## 如何定义一个只能在堆上（栈上）生成对象的类?
1.只能在堆上实例化

将构造函数私有化，然后提供一个public的static函数来完成构造，这样不使用new，而是使用一个函数来构造，使用一个函数来析构。代码如下，类似于单例模式：
```
#include <iostream>
#include <stdio.h>


class A
{
private:
    A()
    {

    }
    ~A()
    {

    }
public:
    static A* create()
    {
        return new A();
    }
    void destory()
    {
        delete this;
    }
};


int main() {
    //A a;  //直接栈上生成对象编译错误
    A* pA = A::create();
    pA->destory();
    return 0;
}
```

2.只能在栈上实例化
只有使用new运算符，对象才会建立在堆上，因此，只要禁用new运算符就可以实现类对象只能建立在栈上。将operator new()设为私有即可。代码如下：
```
#include <iostream>
#include <stdio.h>


class A
{
private:
    void* operator new(size_t t){}
    void operator delete(void *p){}
public:
    A(){}
    ~A(){}
};


int main() {
    A a;
    //A* pA = new A();  //堆上实例化失败
    return 0;
}
```


## 如何设计一个不能被继承的类？

