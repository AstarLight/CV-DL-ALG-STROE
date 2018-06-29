# Python相关的知识总结

### 什么是Python的装饰器模式？
```
#既不需要侵入，也不需要函数重复执行
import time

def deco(func):
    def wrapper():
        startTime = time.time()
        func()
        endTime = time.time()
        msecs = (endTime - startTime)*1000
        print("time is %d ms" %msecs)
    return wrapper


@deco
def func():
    print("hello")
    time.sleep(1)
    print("world")

if __name__ == '__main__':
    f = func #这里f被赋值为func，执行f()就是执行func()
    f()

```

这里的deco函数就是最原始的装饰器，它的参数是一个函数，然后返回值也是一个函数。其中作为参数的这个函数func()就在返回函数wrapper()的内部执行。然后在函数func()前面加上@deco，func()函数就相当于被注入了计时功能，现在只要调用func()，它就已经变身为“新的功能更多”的函数了。 
所以这里装饰器就像一个注入符号：有了它，拓展了原来函数的功能既不需要侵入函数内更改代码，也不需要重复执行原函数。 


### Python怎么读写文件？
```
def change_format(in_path,out_path):
    txt_list = os.listdir(in_path)
    for i in range(len(txt_list)):
        base_name,_ = os.path.splitext(txt_list[i])
        full_path = os.path.join(in_path,txt_list[i])
        with open(full_path,'r') as f:
             out_full_name = os.path.join(out_path, base_name+'.txt')
             f2 = open(out_full_name,'w+')
             for line in f:
                 line = line.strip().split(',')[:8]
                 f2.write('{},{},{},{},{},{},{},{}\n'.format(line[0],line[1],line[6],line[7],line[4],line[5],line[2],line[3]))
             f2.close()
```
### __new__()和__init__()的区别是什么？
```
__init__:初始化方法
__new__：构造函数

__new__：创建实例，并返回cls实例，也就是init方法的第一参数self
__init__:在new创建实例对象后调用，self代表创建的这个实例对象，init设置对象属性的初始值，因此是实例方法，并不返回值
```

```
class A(object):
    """docstring for A"""
    def __init__(self, *args, **kwargs):
        print("init ",self.__class__)

    def __new__(cls, *args,**kwargs):
        print("new ",cls)
        return object.__new__(cls, *args,**kwargs)

a = A()

结果输出：
　　new <class '__main__.A'>
　　init  <class '__main__.A'>
```

通常来说，新式类开始实例化时，”new”方法会返回cls（cls指代当前类）的实例，然后调用该类的”init”方法作为初始化方法，该方法接收这个实例（即self）作为自己的第一个参数，然后依次传入”new”方法中接收的位置参数和命名参数。 但是，如果”new”没有返回cls（即当前类）的实例，那么当前类的”init”方法是不会被调用的。看下面的例子：
```
#!/usr/bin/env python

class A(object):
    def __init__(self,*args,**kwargs):
        print "calling __init__ from %s" % self.__class__

    def __new__(cls,*args,**kwargs):
        obj = object.__new__(cls,*args,**kwargs)
        print "calling __new__ from %s" % obj.__class__
        return obj

class B(A):
    def __init__(self,*args,**kwargs):
        print "calling __init__ from %s" % self.__class__
    def __new__(cls,*args,**kwargs):
        obj = object.__new__(A,*args,**kwargs)
        print "calling __new__ from %s" % obj.__class__
        return obj

b=B()
print type(b)

运行结果是：
calling __new__ from <class '__main__.A'>
<class '__main__.A'>

```

### super关键字的作用是什么？
Python中子类调用父类的方法有两种方法能够实现：调用父类构造方法，或者使用super函数（两者不要混用）。
```
class A(object):   # Python2.x 记得继承 object
    pass
class B(A):
    def add(self, x):
        super(B, self).add(x)
```
涉及多继承时：
```
class A:
    def __init__(self):
        self.n = 2

    def add(self, m):
        # 第四步
        # 来自 D.add 中的 super
        # self == d, self.n == d.n == 5
        print('self is {0} @A.add'.format(self))
        self.n += m
        # d.n == 7


class B(A):
    def __init__(self):
        self.n = 3

    def add(self, m):
        # 第二步
        # 来自 D.add 中的 super
        # self == d, self.n == d.n == 5
        print('self is {0} @B.add'.format(self))
        # 等价于 suepr(B, self).add(m)
        # self 的 MRO 是 [D, B, C, A, object]
        # 从 B 之后的 [C, A, object] 中查找 add 方法
        super().add(m)

        # 第六步
        # d.n = 11
        self.n += 3
        # d.n = 14

class C(A):
    def __init__(self):
        self.n = 4

    def add(self, m):
        # 第三步
        # 来自 B.add 中的 super
        # self == d, self.n == d.n == 5
        print('self is {0} @C.add'.format(self))
        # 等价于 suepr(C, self).add(m)
        # self 的 MRO 是 [D, B, C, A, object]
        # 从 C 之后的 [A, object] 中查找 add 方法
        super().add(m)

        # 第五步
        # d.n = 7
        self.n += 4
        # d.n = 11


class D(B, C):
    def __init__(self):
        self.n = 5

    def add(self, m):
        # 第一步
        print('self is {0} @D.add'.format(self))
        # 等价于 super(D, self).add(m)
        # self 的 MRO 是 [D, B, C, A, object]
        # 从 D 之后的 [B, C, A, object] 中查找 add 方法
        super().add(m)

        # 第七步
        # d.n = 14
        self.n += 5
        # self.n = 19

d = D()
d.add(2)
print(d.n)

输出会是:
self is <__main__.D object at 0x10ce10e48> @D.add
self is <__main__.D object at 0x10ce10e48> @B.add
self is <__main__.D object at 0x10ce10e48> @C.add
self is <__main__.D object at 0x10ce10e48> @A.add
19
```
