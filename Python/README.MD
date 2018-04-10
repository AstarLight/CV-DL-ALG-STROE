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
