# C++知识点汇总

### 在类的成员函数中能不能调用delete this？
答案是肯定的，能调用!当调用delete this时，类对象的内存空间被释放。在delete this之后进行的其他任何函数调用，只要不涉及到this指针的内容，都能够正常运行。一旦涉及到this指针，如操作数据成员，调用虚函数等，就会出现不可预期的问题。

如果在类的析构函数中调用delete this，会发生什么？实验告诉我们，会导致堆栈溢出。原因很简单，delete的本质是“为将被释放的内存调用一个或多个析构函数，然后，释放内存”(来自effective c++)。显然，delete this会去调用本对象的析构函数，而析构函数中又调用delete this，形成无限递归，造成堆栈溢出，系统崩溃。

### 构造函数初始化时必须采用初始化列表一共有三种情况？

1. 需要初始化的数据成员是对象(继承时调用基类构造函数)
2. 需要初始化const修饰的类成员
3. 需要初始化引用成员数据

### 当一个类A中没有声命任何成员变量与成员函数这时sizeof(A)的值是多少?

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
### 析构函数什么情况下定义为虚函数？
当你用一个基类指针指向一个动态创建的派生类对象的时候，如果你想delete这个派生类对象，就必须把基类的析构函数写成虚函数，这样就可以调用派生类的析构函数delete掉这个对象了。否则会内存泄露。

### 如何定义一个只能在堆上（栈上）生成对象的类?
1.只能在堆上实例化

将构造函数私有化，然后提供一个public的static函数来完成构造，这样不使用new，而是使用一个函数来构造，使用一个函数来析构。代码如下，类似于单例模式：
```
#include <iostream>
#include <stdio.h>


class A
{
private:
    A(){}
    ~A(){}
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


### 如何设计一个不能被继承的类？
答案跟上面的“如何定义一个只能在堆上生成对象的类?”的处理方法一样，将构造函数和析构函数私有化，当一个类试图从他那继承时必然会调用他的构造函数，进而导致编译失败。

### C++四种类型转换(cast)
1. static_cast
最常用的类型转换符，在正常状况下的类型转换，如把int转换为float，如：int i；float f； f=（float）i；或者f=static_cast<float>(i)
2. const_cast
用于取出const属性，把const类型的指针变为非const类型的指针，如：const int *fun(int x,int y){}　　int *ptr=const_cast<int *>(fun(2.3))
3. dynamic_cast
    
  dynamic_cast <type-id> (expression),运算符把expression转换成type-id类型的对象。Type-id 必须是类的指针、类的引用或者void*；
- 其他三种都是编译时完成的，dynamic_cast是运行时处理的，运行时要进行类型检查
- 不能用于内置的基本数据类型的强制转换
- dynamic_cast转换如果成功的话返回的是指向类的指针或引用，指针转换失败的话则会返回NULL，引用转换失败抛出异常。
- 使用dynamic_cast进行转换的，基类中一定要有虚函数，否则编译不通过

```
struct B1{
    virtual ~B1(){}
};
struct B2{
    virtual ~B2(){}
};
struct D1 : B1, B2{};
int main()
{
    D1 d;
    B1* pb1 = &d;
    B2* pb2 = dynamic_cast<B2*>(pb1);//L1
    B2* pb22 = static_cast<B2*>(pb1);  //L2
    return 0;
}


```
从上述定义中可以看到,B1和B2是不相关的类,从L1可以看到,dynamic_cast允许这种转换:只要B1存在多态方法.
L2将编译失败,static_cast并不允许两个完全不相干的类互相转换.

4.reinterpret_cast

interpret是解释的意思，reinterpret即为重新解释，此标识符的意思即为数据的二进制形式重新解释，但是不改变其值。如：int i; char *ptr="hello freind!"; i=reinterpret_cast<int>(ptr);这个转换方式很少使用。

### STL中的容器：增减元素对迭代器的影响？
这个问题主要是针对连续内存容器和非连续内存容器。

对于连续内存容器，如vector、deque等，增减元素均会使得当前之后的所有迭代器失效。因此，以删除元素为例：由于erase()总是指向被删除元素的下一个元素的有效迭代器，因此，可以利用该连续内存容器的成员erase()函数的返回值。常见的编程写法为：
```
for(auto iter = myvec.begin(); iter != myvec.end())
{
    if(delete iter)
        iter = myvec.erase(iter);
    else
        iter++;
}

```
对于非连续内存容器，如set、map等。增减元素只会使得当前迭代器无效。仍以删除元素为例，由于删除元素后，erase()返回的迭代器将是无效的迭代器。因此，需要在调用erase()之前，就使得迭代器指向删除元素的下一个元素。常见的编程写法为：
```
for(autoiter = myset.begin(); iter != myset.end())
{
    if(delete iter)
        iter = myset.erase(iter++);
    else
        iter++;
}

```
### mutable和volatile
1. mutable 

 在C++中，mutable是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中，甚至结构体变量或者类对象为const，其mutable成员也可以被修改。
 ```
#include <iostream>
#include <stdio.h>

struct A
{
    int a;
    mutable int b;
};

int main() {
    const A instance = {1,2};
    instance.a = 11;  //编译错误
    instance.b = 12;

    return 0;
}
 ```
 2. volatile
 
编译器进行优化时，它有时会取一些值的时候，直接从寄存器里进行存取，而不是从内存中获取，这种优化在单线程的程序中没有问题，但到了多线程程序中，由于多个线程是并发运行的，就有可能一个线程把某个公共的变量已经改变了，这时其余线程中寄存器的值已经过时，但这个线程本身还不知道，以为没有改变，仍从寄存器里获取，就导致程序运行会出现未定义的行为。并不是因为用volatile修饰了的变量就是“易变”了，假如没有外因，即使用volatile定义，它也不会变化。而加了volatile修饰的变量，编译器将不对其相关代码执行优化，而是生成对应代码直接存取原始内存地址。

### 智能指针的作用？


### 纯虚函数作用和实现方式？


### STL的数据结构的内部实现?
- vector          底层数据结构为数组 ，支持快速随机访问
- list            底层数据结构为双向链表，支持快速增删
- deque           底层数据结构为一个中央控制器和多个缓冲区
- stack           底层一般用list或deque实现，封闭头部即可
- queue           底层一般用list或deque实现，封闭头部即可

（stack和queue其实是适配器,而不叫容器，因为是对容器的再封装）

- priority_queue  底层数据结构一般为vector为底层容器，堆heap为处理规则来管理底层容器实现
- set             底层数据结构为红黑树，有序，不重复
- multiset        底层数据结构为红黑树，有序，可重复 
- map             底层数据结构为红黑树，有序，不重复
- hash_set        底层数据结构为hash表，无序，不重复

### map的实现原理和红黑树的特点?

### extern"C"的作用

### C++多态实现机制?

### 单例模式和工厂模式的实现？

### 类中哪些函数不能为虚函数？ 
- 构造函数:因为构造函数本来就是为了明确初始化对象成员才产生的,现在对象还没有产生，如何使用virtual函数来完成你想完成的动作
- 内联成员函数:内联函数就是为了在代码中直接展开，减少函数调用花费的代价，虚函数是为了在继承后对象能够准确的执行自己的动作，这是不可能统一的
- 静态成员函数:静态成员函数对于每个类来说只有一份代码，所有的对象都共享这一份代码，他也没有要动态邦定的必要性
- 友元函数:因为C++不支持友元函数的继承，对于没有继承特性的函数没有虚函数的说法

### 为什么采用内存对齐，理由？

### 函数的调用怎么实现的，传参呢？

### 如何检测内存泄漏

### 讲讲大端小端，如何检测

### 静态链接、动态链接的区别
