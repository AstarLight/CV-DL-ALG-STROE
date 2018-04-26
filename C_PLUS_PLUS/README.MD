# C++和数据结构识点汇总

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

定义了一个非虚成员函数，sizeof(a)还是1，表明函数指针不存储在对象空间中
```
#include <iostream>
#include <stdio.h>

class A
{
	void foo() {}
};

int main() {
	A a;
	printf("sizeof(A) = %d\n", sizeof(a));  // sizeof(A) = 1
	return 0;
}
```
定义一个虚函数，sizeof(a) = 4，存了个虚函数表指针
```
#include <iostream>
#include <stdio.h>

class A
{
	virtual void foo() {}
};

int main() {
	A a;
	printf("sizeof(A) = %d\n", sizeof(a));  // sizeof(A) = 4
	return 0;
}
```

### 析构函数什么情况下定义为虚函数？
当你用一个基类指针指向一个动态创建的派生类对象的时候，如果你想delete这个派生类对象，就必须把基类的析构函数写成虚函数，这样就可以调用派生类的析构函数delete掉这个对象了。否则会内存泄露。

### C++里是怎么定义常量的？常量存放在内存的哪个位置？

常量在C++里的定义就是一个top-level const加上对象类型，常量定义必须初始化。对于局部对象，常量存放在栈区，对于全局对象，常量存放在全局/静态存储区。对于字面值常量，常量存放在常量存储区。

### 什么是隐式类型转换？怎么避免？
对于内置类型，低精度的变量给高精度变量赋值会发生隐式类型转换，其次，对于只存在单个参数的构造函数的对象构造来说，函数调用可以直接使用该参数传入，编译器会自动调用其构造函数生成临时对象。避免：explict关键字

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
最常用的类型转换符，在正常状况下的类型转换
	
```
char a = 'a';
int b = static_cast<char>(a);//正确，将char型数据转换成int型数据

double *c = new double;
void *d = static_cast<void*>(c);//正确，将double指针转换成void指针

int e = 10;
const int f = static_cast<const int>(e);//正确，将int型数据转换成const int型数据

const int g = 20;
int *h = static_cast<int*>(&g);//编译错误，static_cast不能转换掉g的const属性


if(Derived *dp = static_cast<Derived *>(bp)){//下行转换是不安全的
  //使用dp指向的Derived对象  
}
else{
  //使用bp指向的Base对象  
}

if(Base*bp = static_cast<Derived *>(dp)){//上行转换是安全的
  //使用bp指向的Derived对象  
}
else{
  //使用dp指向的Base对象  
}
```
2. const_cast
用于取出const属性，把const类型的指针变为非const类型的指针，如：const int *fun(int x,int y){}　　int *ptr=const_cast<int *>(fun(2.3))
```
const int g = 20;
int *h = const_cast<int*>(&g);//去掉const常量const属性

const int g = 20;
int &h = const_cast<int &>(g);//去掉const引用const属性

 const char *g = "hello";
char *h = const_cast<char *>(g);//去掉const指针const属性

```
3. dynamic_cast
    
  dynamic_cast <type-id> (expression),运算符把expression转换成type-id类型的对象。Type-id 必须是类的指针、类的引用或者void*；
- 其他三种都是编译时完成的，dynamic_cast是运行时处理的，运行时要进行类型检查
- 不能用于内置的基本数据类型的强制转换
- dynamic_cast转换如果成功的话返回的是指向类的指针或引用，指针转换失败的话则会返回NULL，引用转换失败抛出异常。
- 使用dynamic_cast进行转换的，基类中一定要有虚函数，否则编译不通过
```
if(Derived *dp = dynamic_cast<Derived *>(bp)){
  //使用dp指向的Derived对象  
}
else{
  //使用bp指向的Base对象  
}

//因为不存在所谓空引用，所以引用类型的dynamic_cast转换与指针类型不同，在引用转换失败时，会抛出std::bad_cast异常，该异常定义在头文件typeinfo中。

void f(const Base &b){
 try{
   const Derived &d = dynamic_cast<const Base &>(b);  
   //使用b引用的Derived对象
 }
 catch(std::bad_cast){
   //处理类型转换失败的情况
 }
}

```
从上述定义中可以看到,B1和B2是不相关的类,从L1可以看到,dynamic_cast允许这种转换:只要B1存在多态方法.
L2将编译失败,static_cast并不允许两个完全不相干的类互相转换.

4.reinterpret_cast


interpret是解释的意思，reinterpret即为重新解释，此标识符的意思即为数据的二进制形式重新解释，但是不改变其值。允许将任何指针转换为任何其他指针类型,比如不同类的对象指针可以互相转换。 也允许将任何整数类型转换为任何指针类型以及反向转换。.如：int i; char *ptr="hello freind!"; i=reinterpret_cast<int>(ptr);这个转换方式很少使用。


### static_cast与dynamic_cast用法的异同？
static_cast < type-id > ( exdivssion ) 
该运算符把exdivssion转换为type-id类型，但没有运行时类型检查来保证转换的安全性。它主要有如下几种用法：
1. 用于类层次结构中基类和子类之间指针或引用的转换。
- 进行上行转换（把子类的指针或引用转换成基类表示）是安全的；
- 进行下行转换（把基类指针或引用转换成子类表示）时，由于没有动态类型检查，所以是不安全的。
2. 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
3. 把空指针转换成目标类型的空指针。
3. 把任何类型的表达式转换成void类型。

4. 注意：static_cast不能转换掉exdivssion的const、volitale、或者__unaligned属性。

dynamic_cast主要用于类层次间的上行转换和下行转换，还可以用于类之间的交叉转换。
1. 在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的；
2. 在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。
3. 要注意：B要有虚函数，否则会编译出错；static_cast则没有这个限制。
这是由于运行时类型检查需要运行时类型信息，而这个信息存储在类的虚函数表（
关于虚函数表的概念，详细可见）中，只有定义了虚函数的类才有虚函数表，
没有定义虚函数的类是没有虚函数表的。

dynamic_cast几乎唯一的被用来处理多态。多态分为上行转换和下行转换，上行转换没问题，子类的指针肯定可以转换成父类指针。下行转换就有问题了，如果要把父类的指针A转换成子类的指针B，如果A指向的是子类的对象，这样转没问题。但是，如果A指向的是父类的对象，正确的做法是转换应该为不成功的，因为多态里没有子类的指针指向父类的对象的。所以，在“A指向的是父类的对象，现要把A转成B”这种情况下，如果采用static_cast，不会报错，返回的是转换后的指针，但程序此时是不安全的。如果采用dynamic_cast，它会根据虚函数表找到A指向的是什么对象（这里要求父类必须要有虚函数，否则报错），如果是父类对象，返回NULL，如果是子类对象，返回转换后的指针，程序此时是安全的。所以，这就是dynamic_cast和static_cast最大的区别。


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
        myset.erase(iter++);
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
智能指针和普通指针的区别在于智能指针实际上是对普通指针加了一层封装机制，这样的一层封装机制的目的是为了使得智能指针可以方便的管理一个对象的生命期。智能指针实质是一个对象，行为表现的却像一个指针。
智能指针共分为4种，即boost库中的auto_ptr、scoped_ptr、shared_ptr、weak_ptr。

- auto_ptr:auto_ptr 基于【排他所有权模式】，这意味着：两个指针（同类型）不能指向同一个资源，复制或赋值都会改变资源的所有权。auto_ptr的析构函数内部释放资源时调用的是delete而不是delete[]，因此不要让auto_ptr托管数组
- scoped_ptr:这是比较简单的一种智能指针，正如其名字所述，scoped_ptr所指向的对象在作用域之外会自动得到析构。但是scoped_ptr的所有权更加严格，不能转让，一旦scoped_pstr获取了对象的管理权，你就无法再从它那里取回来。
- shared_ptr:shared_ptr中所实现的本质是引用计数(reference counting)，也就是说shared_ptr是支持复制的，复制一个shared_ptr的本质是对这个智能指针的引用次数加1，而当这个智能指针的引用次数降低到0的时候，该对象自动被析构。shared_ptr不能对循环引用的对象的内存进行自动管理
- unique_ptr:unique_ptr持有对对象的独有权——两个unique_ptr不能指向一个对象，不能进行复制操作只能进行移动操作。同一时刻只能有一个unique_ptr指向给定对象但可以转移所有权。
- weak_ptr:weak_ptr是为了配合shared_ptr而引入的一种智能指针，因为它不具有普通指针的行为，没有重载operator*和->,它的最大作用在于协助shared_ptr工作，像旁观者那样观测资源的使用情况。weak_ptr可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。有点像普通指针。

使用weak_ptr解决循环引用
```
class B;
class A
{
public:
    A()
    {
        cout << "Class A Constructor is called." << endl;
    }

    ~A()
    {
        cout << "Class A Deconstructor is called." << endl;
    }

    // tr1::shared_ptr<B> m_shB;
    tr1::weak_ptr<B> m_shB;
};

class B
{
public:
    B()
    {
        cout << "Class B Constructor is called." << endl;
    }

    ~B()
    {
        cout << "Class B Deconstructor is called." << endl;
    }

    tr1::shared_ptr<A> m_shA;
};

int _tmain(int argc, _TCHAR* argv[])
{
    {
        // 测试重复引用
        tr1::shared_ptr<A> shA(new A());
        tr1::shared_ptr<B> shB(new B());
        
        if (shA && shB)
        {
            shA->m_shB = shB;
            shB->m_shA = shA;
        }

        cout << "A的引用计数：" << shA.use_count() << " B的引用计数：" << shB.use_count() << endl;
      
        cout << "要离开shA和shB的作用域了，正常情况下在这之后会执行shA和shB的析构函数的" << endl;
            
       // 这里是要执行析构函数的
       // 首先，会执行shB这个B对象的析构函数，要析构B的话，得先去判断下托管B的shared_ptr的引用计数，
       //       这里是1，所以去析构B，B析构后紧接着去析构其成员对象A，此时A的引用计数为2，所以会使A的引用计数减为1
       // 然后，会执行shA这个A对象的析构函数，要析构A的话，也得先去判断下托管的A的shared_ptr的引用计数，这里是1，它可以析构
    }

    cout << "已经离开shA和shB的作用域了，请观察shA和shB的析构函数有没有被执行" << endl;
}
```

### 纯虚函数如何定义，为什么对于存在虚函数的类中析构函数要定义成虚函数？
为了实现多态进行动态绑定，将派生类对象指针绑定到基类指针上，对象销毁时，如果析构函数没有定义为析构函数，则会调用基类的析构函数，显然只能销毁部分数据。如果要调用对象的析构函数，就需要将该对象的析构函数定义为虚函数，销毁时通过虚函数表找到对应的析构函数。
```
virtual ~myClass()=0;
```

### 什么是虚函数？
首先的话虚函数的写法是在成员函数上加关键字virtual，虚函数主要的作用是实现多态，执行动态绑定，在运行的时候确定。它虚就虚在所谓“推迟联编”或者“动态联编”上，一个类函数的调用并不是在编译时刻被确定的，而是在运行时刻被确定的。由于编写代码的时候并不能确定被调用的是基类的函数还是哪个派生类的函数，所以被成为“虚”函数。虚函数只能借助于指针或者引用来达到多态的效果。

一个vfptr被加入到类中（如果类中没有的话），该vfptr指向类的虚函数表（vftable）。类中每个虚函数在该类的虚函数表中都占据一项。每项保存一个对于该类适用的虚函数的地址。因此，调用虚函数的过程如下：取得实例的vfptr；通过vfptr得到虚函数表的一项；通过虚函数表该项的函数地址间接调用虚函数。也就是说，在普通函数调用的参数传递、调用、返回指令开销外，虚函数调用还需要额外的开销。

### 虚函数原理，虚函数表存放位置？
一个类存在虚函数，那么编译器就会为这个类生成一个虚表，在虚表里存放的是这个类所有虚函数的地址。当生成类对象的时候，编译器会自动的将类对象的前四个字节设置为虚表的地址，而这四个字节就可以看作是一个指向虚表的指针。虚表里依次存放的是虚函数的地址，每个虚函数的地址占4个字节。

主流 C++ 实现（gcc/clang/VC++）对于最简单的单继承且基类有虚函数的情况（非虚拟继承）的做法都差不多：
- vtable 是每个 class 类型一个，不是每个对象一个。
- vtable 的大小（长度）跟这个 class 的虚函数总数（继承和自己新增）正相关。
- vptr 是每个对象一个，vptr 大小是固定的，跟虚函数多少无关。
- 对象的 vptr 在构造和析构的时候可能会变，指向不同的 vtable。对象构造完就不会变了。
- “只使用前一段”有可能发生，如果派生类添加了新的虚函数的话（比如 virtual void B::print()）。



### 为什么用成员初始化列表会快一些（性能优势）？
优势：省去了临时对象的存在

方法一是在构造函数当中做赋值的操作，而方法二是做纯粹的初始化操作。我们都知道，C++的赋值操作是会产生临时对象的。临时对象的出现会降低程序的效率。

### 析构函数能抛出异常吗?
不能。

如果析构函数抛出异常，则异常点之后的程序不会执行，如果析构函数在异常点之后执行了某些必要的动作比如释放某些资源，则这些动作不会执行，会造成诸如资源泄漏的问题。
通常异常发生时，c++的机制会调用已经构造对象的析构函数来释放资源，此时若析构函数本身也抛出异常，则前一个异常尚未处理，又有新的异常，会造成程序崩溃的问题。


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
- set和map都是基于红黑树实现的。
- 红黑树是一种平衡二叉查找树，与AVL树的区别是什么？AVL树是完全平衡的，红黑树基本上是平衡的。
- 为什么选用红黑数呢？因为红黑数是平衡二叉树，其插入和删除的效率都是N(logN)，与AVL相比红黑数插入和删除最多只需要3次旋转，而AVL树为了维持其完全平衡性，在坏的情况下要旋转的次数太多。


红黑树的定义：
1. 节点是红色或者黑色；
2. 父节点是红色的话，子节点就不能为红色；
3. 从根节点到每个页子节点路径上黑色节点的数量相同；
4. 根是黑色的，NULL节点被认为是黑色的。

### vector的扩容机制
vector有两个函数一个是capacity()返回内存空间即缓冲区的大小，另一个是size()返回当前数组中数的数量。vector增加元素来说，当容量已经不能放进数据了，那么他会重新申请一块内存，把之前的内存利用复制构造函数复制到新的内存当中，然后把新添加的内容放入后面，另外此时的他申请的内存空间是原来空间的2倍，vecotor占用的内存只增不减，erase只是将一段区间（ earse(arr.begin(), arr.end() ）的值清除掉或者将某个值( erase(x) )清除掉，但是对于内存空间来说是没变化的。

所有内存空间是在vector析构时候才能被系统回收。empty()用来检测容器是否为空的，clear()可以清空所有元素。但是即使clear()，vector所占用的内存空间依然如故，无法保证内存的回收。

### 为何map和set的插入删除效率比用其他序列容器高？
因为对于关联容器来说，不需要做内存拷贝和内存移动。说对了，确实如此。map和set容器内所有元素都是以节点的方式来存储，其节点结构和链表差不多，指向父节点和子节点。插入和删除就是指针换来换去，和内存移动没有关系。

###  为何每次map和set insert之后，以前保存的iterator不会失效？
iterator这里就相当于指向节点的指针，内存没有变，指向内存的指针怎么会失效呢(当然被删除的那个元素本身已经失效了)。相对与vector来说，vector每次插入和删除，指针都有可能会失效，比如：当该内存块不够它扩容时，它会申请其它内存块，此时指针会失效！

### extern"C"的作用
extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码。加上extern "C"后，会指示编译器这部分代码按C语言的进行编译，而不是C++的。由于C++支持函数重载，因此编译器编译函数的过程中会将函数的参数类型也加到编译后的代码中，而不仅仅是函数名;而C语言并不支持函数重载，因此编译C语言代码的函数时不会带上函数的参数类型，一般只包括函数名。

### C++多态实现机制?
多态分为静态多态和动态多态。静态多态是通过重载和模板技术实现，在编译的时候确定。动态多态通过虚函数和继承关系来实现，执行动态绑定，在运行的时候确定。

动态多态实现有几个条件：
(1) 虚函数；
(2) 一个基类的指针或引用指向派生类的对象；

基类指针在调用成员函数(虚函数)时，就会去查找该对象的虚函数表。虚函数表的地址在每个对象的首地址。查找该虚函数表中该函数的指针进行调用。
每个对象中保存的只是一个虚函数表的指针，C++内部为每一个类维持一个虚函数表，该类的对象的都指向这同一个虚函数表。
虚函数表中为什么就能准确查找相应的函数指针呢？因为在类设计的时候，虚函数表直接从基类也继承过来，如果覆盖了其中的某个虚函数，那么虚函数表的指针就会被替换，因此可以根据指针准确找到该调用哪个函数。

### 虚函数表是针对类的还是针对对象的？同一个类的两个对象的虚函数表是怎么维护的？
编译器为每一个类维护一个虚函数表，每个对象的首地址保存着该虚函数表的指针，同一个类的不同对象实际上指向同一张虚函数表。

### 工厂模式的实现？
简单工厂模式：
```

enum CTYPE {COREA, COREB};     
class SingleCore    
{    
public:    
    virtual void Show() = 0;  
};    
//单核A    
class SingleCoreA: public SingleCore    
{    
public:    
    void Show() { cout<<"SingleCore A"<<endl; }    
};    
//单核B    
class SingleCoreB: public SingleCore    
{    
public:    
    void Show() { cout<<"SingleCore B"<<endl; }    
};    
//唯一的工厂，可以生产两种型号的处理器核，在内部判断    
class Factory    
{    
public:     
    SingleCore* CreateSingleCore(enum CTYPE ctype)    
    {    
        if(ctype == COREA) //工厂内部判断    
            return new SingleCoreA(); //生产核A    
        else if(ctype == COREB)    
            return new SingleCoreB(); //生产核B    
        else    
            return NULL;    
    }    
};    
```

工厂方法模式:
```

class SingleCore    
{    
public:    
    virtual void Show() = 0;  
};    
//单核A    
class SingleCoreA: public SingleCore    
{    
public:    
    void Show() { cout<<"SingleCore A"<<endl; }    
};    
//单核B    
class SingleCoreB: public SingleCore    
{    
public:    
    void Show() { cout<<"SingleCore B"<<endl; }    
};    
class Factory    
{    
public:    
    virtual SingleCore* CreateSingleCore() = 0;  
};    
//生产A核的工厂    
class FactoryA: public Factory    
{    
public:    
    SingleCoreA* CreateSingleCore() { return new SingleCoreA; }    
};    
//生产B核的工厂    
class FactoryB: public Factory    
{    
public:    
    SingleCoreB* CreateSingleCore() { return new SingleCoreB; }    
}; 
```



抽象工厂模式：
```
//单核    
class SingleCore     
{    
public:    
    virtual void Show() = 0;  
};    
class SingleCoreA: public SingleCore      
{    
public:    
    void Show() { cout<<"Single Core A"<<endl; }    
};    
class SingleCoreB :public SingleCore    
{    
public:    
    void Show() { cout<<"Single Core B"<<endl; }    
};    
//多核    
class MultiCore      
{    
public:    
    virtual void Show() = 0;  
};    
class MultiCoreA : public MultiCore      
{    
public:    
    void Show() { cout<<"Multi Core A"<<endl; }    
    
};    
class MultiCoreB : public MultiCore      
{    
public:    
    void Show() { cout<<"Multi Core B"<<endl; }    
};    
//工厂    
class CoreFactory      
{    
public:    
    virtual SingleCore* CreateSingleCore() = 0;  
    virtual MultiCore* CreateMultiCore() = 0;  
};    
//工厂A，专门用来生产A型号的处理器    
class FactoryA :public CoreFactory    
{    
public:    
    SingleCore* CreateSingleCore() { return new SingleCoreA(); }    
    MultiCore* CreateMultiCore() { return new MultiCoreA(); }    
};    
//工厂B，专门用来生产B型号的处理器    
class FactoryB : public CoreFactory    
{    
public:    
    SingleCore* CreateSingleCore() { return new SingleCoreB(); }    
    MultiCore* CreateMultiCore() { return new MultiCoreB(); }    
};   

```

### 单例中懒汉和饿汉的区别有哪些？
单例中懒汉和饿汉的本质区别在于以下几点：
1. 饿汉式是线程安全的,在类创建的同时就已经创建好一个静态的对象供系统使用,以后不在改变。懒汉式如果在创建实例对象时不加上synchronized则会导致对对象的访问不是线程安全的。
2. 从实现方式来讲他们最大的区别就是懒汉式是延时加载,他是在需要的时候才创建对象,而饿汉式在虚拟机启动的时候就会创建，饿汉式无需关注多线程问题、写法简单明了、能用则用。但是它是加载类时创建实例,所以如果是一个工厂模式、缓存了很多实例、那么就得考虑效率问题，因为这个类一加载则把所有实例不管用不用一块创建。

### 单例模式的实现（懒汉、饿汉）？
为什么我们需要单例模式，绝对不是因为方便调用，因为静态方法更方便。那到底为什么使用单例模式呢？其实经过我们的讨论，单例模式的使用场景是一些全局不可变参数，可以放到单例中，比如从配置获取值，然后缓存到单例中

懒汉式：一种实现方法是定义一个单例类，使用类的私有静态指针变量指向类的唯一实例，并用一个公有的静态方法获取该实例。单例模式通过类本身来管理其唯一实例，这种特性提供了解决问题的方法。唯一的实例是类的一个普通对象，但设计这个类时，让它只能创建一个实例并提供对此实例的全局访问。唯一实例类Singleton在静态成员函数中隐藏创建实例的操作。
```
class CSingleton  
{  
private:  
    CSingleton()   //构造函数是私有的  
    {  
    }  
    static CSingleton *m_pInstance;  
public:  
    static CSingleton * GetInstance()  
    {  
        if(m_pInstance == NULL)  //判断是否第一次调用  
            m_pInstance = new CSingleton();  
        return m_pInstance;  
    }  
};  
```
这种实现方式存在的一个问题是m_pInstance变量的释放问题，即实例的析构问题，虽然我们可以在程序结束时主动调用GetInstance（）方法并对其返回的指针智行delete操作，但是这种方式不仅繁琐，而且调用者忘记的话，会引起很多的问题。

对于上面这种问题的一种解决方法是在该类中定义一个静态全局变量，我们知道，程序在结束的时候，系统会自动析构所有的全局变量。系统也会析构所有的类的静态成员变量，就像这些静态成员也是全局变量一样。我们可以在CSingleton单例类中定义一个这样的静态成员变量，在它的析构函数中删除单例类的实例。
```
class CSingleton  
{  
private:  
    CSingleton()  
    {  
    }  
    static CSingleton *m_pInstance;  
    class CGarbo   //它的唯一工作就是在析构函数中删除CSingleton的实例  
    {  
    public:  
        ~CGarbo()  
        {  
            if(CSingleton::m_pInstance)  
                delete CSingleton::m_pInstance;  
        }  
    };  
    static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  
public:  
    static CSingleton * GetInstance()  
    {  
        if(m_pInstance == NULL)  //判断是否第一次调用  
            m_pInstance = new CSingleton();  
        return m_pInstance;  
    }  
}; 
```



饿汉式:如果你对上面添加在单例类内部添加一个类静态对象的方法不是很满意，还可以使用局部静态变量方法构造：
```

class CSingleton  
{  
private:  
    CSingleton()   //构造函数是私有的  
    {  
    }  
public:  
    static CSingleton & GetInstance()  
    {  
        static CSingleton instance;   //局部静态变量  
        return instance;  
    }  
}; 
```
用此种方法会出现类拷贝的问题，例如 Singleton singleton = Singleton :: GetInstance();这种调用方式编译器会为类生成一个默认的构造函数，来支持类的拷贝。这样的话就违背了单例的特性，所以我们可以稍微改一下，返回的是指针：
```
class CSingleton  
{  
private:  
    CSingleton()   //构造函数是私有的  
    {  
    }  
public:  
    static CSingleton * GetInstance()  
    {  
        static CSingleton instance;   //局部静态变量  
        return &instance;  
    }  
}; 
```

### 怎么写出单例模式的线程安全版本？

此处进行了两次m_Instance == NULL的判断，是借鉴了Java的单例模式实现时，使用的所谓的“双检锁”机制。因为进行一次加锁和解锁是需要付出对应的代价的，而进行两次判断，就可以避免多次加锁与解锁操作，同时也保证了线程安全。(懒汉线程安全版)
```
#include <iostream>
using namespace std;
 
class Singleton
{
public:
	static Singleton *GetInstance()
	{
		if (m_Instance == NULL )
		{
			Lock(); // C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
			if (m_Instance == NULL )
			{
				m_Instance = new Singleton ();
			}
			UnLock(); // C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
		}
		return m_Instance;
	}
 
	static void DestoryInstance()
	{
		if (m_Instance != NULL )
		{
			delete m_Instance;
			m_Instance = NULL ;
		}
	}
 
	int GetTest()
	{
		return m_Test;
	}
 
private:
	Singleton(){ m_Test = 0; }
	static Singleton *m_Instance;
	int m_Test;
};
 
Singleton *Singleton ::m_Instance = NULL;
 
int main(int argc , char *argv [])
{
	Singleton *singletonObj = Singleton ::GetInstance();
	cout<<singletonObj->GetTest()<<endl;
	Singleton ::DestoryInstance();
 
	return 0;
}

```

或者这种：（饿汉模式）
```
#include <iostream>
using namespace std;
 
class Singleton
{
public:
	static Singleton *GetInstance()
	{
		static Singleton m_Instance;
		return &m_Instance;
	}
 
	int GetTest()
	{
		return m_Test++;
	}
 
private:
	Singleton(){ m_Test = 10; };
	int m_Test;
};
 
int main(int argc , char *argv [])
{
	Singleton *singletonObj = Singleton ::GetInstance();
	cout<<singletonObj->GetTest()<<endl;
 
	singletonObj = Singleton ::GetInstance();
	cout<<singletonObj->GetTest()<<endl;
}

```

### 策略模式的实现？
当用户需要选择不同的算法或行为时，如果把这些算法或行为写在一个类里，通过判断来选择的话，这个类将变得非常复杂并且难以维护。策略模式就是构造一个抽象类，具体的算法或者行为继承这个类，让用户来选择。这样做的好处是，可以随时增加或者修改行为，即增加、修改算法或行为的类就可以了。

策略模式和简单工厂模式的差别：

简单工厂模式是通过一个抽象类来构造新对象，用户接触不到具体对象。

策略模式是通过抽象类来选择行为或算法。

```
//抽象接口  
class ReplaceAlgorithm  
{  
public:  
    virtual void Replace() = 0;  
};  
//三种具体的替换算法  
class LRU_ReplaceAlgorithm : public ReplaceAlgorithm  
{  
public:  
    void Replace() { cout<<"Least Recently Used replace algorithm"<<endl; }  
};  
  
class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm  
{  
public:  
    void Replace() { cout<<"First in First out replace algorithm"<<endl; }  
};  
class Random_ReplaceAlgorithm: public ReplaceAlgorithm  
{  
public:  
    void Replace() { cout<<"Random replace algorithm"<<endl; }  
};  

//Cache需要用到替换算法  
class Cache  
{  
private:  
    ReplaceAlgorithm *m_ra;  
public:  
    Cache(ReplaceAlgorithm *ra) { m_ra = ra; }  
    ~Cache() { delete m_ra; }  
    void Replace() { m_ra->Replace(); }  
};  


int main()  
{  
    Cache cache(new LRU_ReplaceAlgorithm()); //暴露了算法的定义  
    cache.Replace();  
    return 0;  
}  

```

### 什么是适配器模式？
适配器模式将一个类的接口转换成客户希望的另外一个接口，使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。举个例子，在STL中就用到了适配器模式。STL实现了一种数据结构，称为双端队列（deque），支持前后两段的插入与删除。STL实现栈和队列时，没有从头开始定义它们，而是直接使用双端队列实现的。这里双端队列就扮演了被适配类的角色。队列用到了它的后端插入，前端删除。而栈用到了它的后端插入，后端删除。假设栈和队列都是一种顺序容器，有两种操作：压入和弹出。

```
//使用复合，对象模式
class Deque  //双端队列，被适配类
{
public:
    void push_back(int x)
    {
        cout << "Deque push_back:" << x << endl;
    }
    void push_front(int x)
    {
        cout << "Deque push_front:" << x << endl;
    }
    void pop_back()
    {
        cout << "Deque pop_back" << endl;
    }
    void pop_front()
    {
        cout << "Deque pop_front" << endl;
    }
};

class Sequence  //顺序类，目标类
{
public:
    virtual void push(int x) = 0;
    virtual void pop() = 0;
};

class Stack:public Sequence   //栈, 适配类
{
public:
    void push(int x)
    {
        m_deque.push_back(x);
    }
    void pop()
    {
        m_deque.pop_back();
    }
private:
    Deque m_deque;
};

class Queue:public Sequence  //队列，适配类
{
public:
    void push(int x)
    {
        m_deque.push_back(x);
    }
    void pop()
    {
        m_deque.pop_front();
    }
private:
    Deque m_deque;
};
//END
```

### 什么是代理模式？
- 代理模式：为其它对象提供一种代理以控制对这个对象的访问。
- 主要解决：在直接访问对象时带来的问题，比如：要访问的对象在远程服务器上。在面向对象系统中，有些对象由于某些原因，直接访问会给使用者或系统带来很多麻烦，可以在访问此对象时加上一个对此对象的访问层。

```
//统一的抽象接口 IFactory
class IFactory  
{  
public:  
    IFactory(){}  
    virtual void makeProduct() = 0;  
};  

//你的手机工厂
class PhoneFactory : IFactory  
{  
public:  
    PhoneFactory(){}  
    void makeProduct()  
    {  
        cout<<"生产手机"<<endl;  
    }  
};  

//专门做代工的代理工厂富士康
class FoxconnProxy : IFactory  
{  
public:  
    FoxconnProxy(IFactory* factory)  
    {  
        m_real = factory;  
    }  
    void makeProduct()  
    {  
        m_real->makeProduct();  
    }  
private:  
    IFactory* m_real;  
};  

//客户端：
IFactory* factory = new PhoneFactory();  
FoxconnProxy* proxy =  new FoxconnProxy(factory);  
proxy->makeProduct();  

```

### 类中哪些函数不能为虚函数？ 
- 构造函数:因为构造函数本来就是为了明确初始化对象成员才产生的,现在对象还没有产生，如何使用virtual函数来完成你想完成的动作（编译器报错）
- 内联成员函数:内联函数就是为了在代码中直接展开，减少函数调用花费的代价，内联函数是个静态行为，而虚函数是个动态行为，他们之间是有矛盾的（多态调用，不能内联，非多态调用可以内联,如b->Base::Foo(); // 非多态调用，可以内联（但具体是否内联由编译器决定））
- 静态成员函数:静态成员函数对于每个类来说只有一份代码，所有的对象都共享这一份代码，他也没有要动态邦定的必要性（编译器报错）
- 友元函数:因为C++不支持友元函数的继承，对于没有继承特性的函数没有虚函数的说法

### 为什么采用内存对齐，理由？
一方面是因为我们的计算机硬件就是这么设计的，也就是说CPU在访问存储器的时候只能在某些地址处获取某些特定类型的数据。另一方面，因为CPU读取数据的时候不是一个一个读的，几个几个读的。如果数据不按照一定的规则存储的话，会降低读取速度，从而影响计算效率。如果加入pragma pack(n) ，取n和变量自身大小较小的一个。

### 函数的调用怎么实现的，传参呢？

### 如何检测内存泄漏
自己重载new操作符，用list或者map对分配的内存进行收集，如果释放了，就删除节点，最后检测容器里面还有没有节点，有就是泄露了，也可以记录是哪一行的代码分配的内存被泄露了，这都看你想要记录什么。最终可以生成报告给自己去分析。

存泄漏通常是指堆内存的泄漏，也就是通过malloc、calloc函数申请的内存，因此内存泄漏的检测方法核心思想就是通过宏定义自定义内存分配及释放函数来替换用户的malloc、calloc、free等函数。申请信息，申请内存时，记录并插入到全局的链表中；释放内存时从全局链表中查找对应的记录，并删除。程序结束时，将链表中信息写入文件，并清除链表。
```
#define malloc(size) malloc_detector(size,__FILE__,__LINE__)
#define calloc(element_num,element_size) calloc_detector (element_num,element_size,__FILE__,__LINE__)
#define free(addr) free_detector(addr)
```

```
//---------------------------------------------------------------
// 重载new,new[],delete,delete[] 
//---------------------------------------------------------------
void* operator new(size_t size, const char* file, unsigned int line) {
  void* ptr = malloc(size);
  mem_stack.Insert(ptr, file, line);
  return ptr;
}
void* operator new[](size_t size, const char* file, unsigned int line) {
  return operator new(size, file, line); // 不能用new 
}
void operator delete(void* ptr) {
  free(ptr);
  mem_stack.Delete(ptr);
}
void operator delete[](void* ptr) {
  operator delete(ptr);
}

//---------------------------------------------------------------
// 使用宏将带测试代码中的new和delte替换为重载的new和delete 
//---------------------------------------------------------------
#define new new(__FILE__,__LINE__)
```

使用工具：Linux下通过工具valgrind检测

```
g++ mem.cpp -o mem -g

Valgrind --tool=memcheck --leak-check=full ./mem
```

该工具可以检测下列与内存相关的问题 :

- 未释放内存的使用
- 对释放后内存的读/写
- 对已分配内存块尾部的读/写
- 内存泄露
- 不匹配的使用malloc/new/new[] 和 free/delete/delete[]
- 重复释放内存

### 讲讲大端小端，如何检测？
- 变量的高字节放到内存的低地址中（变量的低字节放到内存的高地址中）==>大端
- 变量的高字节放到内存的高地址中（变量的低字节放到内存的低地址中）==>小端 

```
#include <stdio.h>
int main() {
    int i = 0x11223344;
    char *p;

    p = (char *) &i;
    if (*p == 0x44) {
        printf("Little endian\n");
    }
    else {
        printf("Big endian\n");
    }
    return 0;
}
```


### 静态链接、动态链接的区别？
静态链接是指在编译阶段直接把静态库加入到可执行文件中去，这样可执行文件会比较大。而动态链接则是指链接阶段仅仅只加入一些描述信息，而程序执行时再从系统中把相应动态库加载到内存中去。

### STL中unordered_map和map

### hash冲突如何解决？
- 开放定址法：线性，平方
- 链地址法

### 堆和栈的区别 堆的栈哪个大？ 堆一般多大？
Linux:栈1M，堆理论上无上限，取决于机器位数（32位，4G）

### B+树为何适合数据库索引？
- 不同于B树只适合随机检索，B+树同时支持随机检索和顺序检索；
- B+树的磁盘读写代价更低。B+树的内部结点并没有指向关键字具体信息的指针，其内部结点比B树小，盘块能容纳的结点中关键字数量更多，一次性读入内存中可以查找的关键字也就越多，相对的，IO读写次数也就降低了。而IO读写次数是影响索引检索效率的最大因素。
- B树在提高了磁盘IO性能的同时并没有解决元素遍历的效率低下的问题。B+树的叶子节点使用指针顺序连接在一起，只要遍历叶子节点就可以实现整棵树的遍历。而且在数据库中基于范围的查询是非常频繁的，而B树不支持这样的操作（或者说效率太低）。

### reverse/capacity函数和 resize/size函数的区别？
size()告诉你容器中实际有多少个元素，resize()则会在容器末尾添加或者删除元素，使得容器达到指定大小；capacity()告诉你最少添加多少个元素才会导致容器的重新分配内存，而reserve()在必要时候总是容器内部缓冲区扩至一个更大的内容，reserve()并不改变容器中元素的数量，它仅影响vector预先分配多大的内存空间。

### 迭代器类型有哪些？ map的迭代器属于哪一种类型?

### C++内存分为那几块？
（堆区，栈区，常量区，静态和全局区）
上面是高地址，堆区向上生长（地址越分越大），栈区向下生长（地址越分越小）,栈的生长方向是从高地址向低地址（X86）

### STL里的内存池实现？

STL内存分配分为一级分配器和二级分配器，一级分配器就是采用malloc分配内存，二级分配器采用内存池。
二级分配器设计的非常巧妙，分别给8k，16k,..., 128k等比较小的内存片都维持一个空闲链表，每个链表的头节点由一个数组来维护。需要分配内存时从合适大小的链表中取一块下来。假设需要分配一块10K的内存，那么就找到最小的大于等于10k的块，也就是16K，从16K的空闲链表里取出一个用于分配。释放该块内存时，将内存节点归还给链表。
如果要分配的内存大于128K则直接调用一级分配器。
为了节省维持链表的开销，采用了一个union结构体，分配器使用union里的next指针来指向下一个节点，而用户则使用union的空指针来表示该节点的地址。


### 十亿整数（随机生成，可重复）中前K最大的数？
- 快排的思想 近似O(n):调用降序快排的partition函数，设区间为[low,high]，返回index，则index左边都是大于data[index]的。 
1. 若index及index左边数字有k个则data[index]就是第k大，index及其左边元素为Top K元素 
2. 左边数字大于k个则继续在[low,index]里找 
3. 左边数字小于k个则去右边[index+1,high]找 k - 左边数字个数
- 小根堆 O(nlogk):维护一个k个元素的小根堆，保持堆里元素为最大的K个且堆顶为第k大(堆里最小的)，扫一遍数据，若堆里个数小于k则插入，否则看新的数和堆顶数大小关系： 
1. 若新来的数小于等于堆顶，即新元素比Top K里最小的还小，则新来的数显然不可能是前k大 
2. 若新来的数大于堆顶，则删掉堆顶，将新数字放到堆里且调整堆来保持堆的属性
- 部分排序:题目要求是求出Top 10，因此我们没有必要对所有的Query都进行排序，我们只需要维护一个10个大小的数组，初始化放入10个Query，按照每个Query的统计次数由大到小排序，然后遍历这300万条记录，每读一条记录就和数组最后一个Query对比，如果小于这个Query，那么继续遍历，否则，将数组中最后一条数据淘汰(还是要放在合适的位置，保持有序)，加入当前的Query。最后当所有的数据都遍历完毕之后，那么这个数组中的10个Query便是我们要找的Top10了。不难分析出，这样，算法的最坏时间复杂度是N*K， 其中K是指top多少。

### 什么是布隆过滤器？

### 几十亿个数经常要查找某一个数在不在里面，使用布隆过滤器，布隆过滤器的原理。布隆过滤器可能出现误判，怎么保证无误差？



### 全局变量和static变量的区别？
1) 全局变量(外部变量)的说明之前再冠以static 就构成了静态的全局变量。全局变量本身就是静态存储方式， 静态全局变量当然也是静态存储方式。 这两者在存储方式上并无不同。这两者的区别在于非静态全局变量的作用域是整个源程序， 当一个源程序由多个源文件组成时，非静态的全局变量在各个源文件中都是有效的。 而静态全局变量则限制了其作用域， 即只在定义该变量的源文件内有效， 在同一源程序的其它源文件中不能使用它。由于静态全局变量的作用域局限于一个源文件内，只能为该源文件内的函数公用， 因此
