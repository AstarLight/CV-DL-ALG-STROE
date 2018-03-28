# Linux系统级编程知识点积累

其中包括以下知识点：
- Linux网络编程
- Linux进程间通信
- 线程安全
- 计算机网络
- 操作系统

### GCC的编译过程分为那几步？
预处理、编译、汇编和链接４个步骤。
- 预处理，生成预编译文件：gcc -E hello.c -o hello.i
- 编译，生成汇编代码：gcc -S hello.i -o hello.s
- 汇编，生成目标文件：gcc -c hello.s -o hello.o
- 链接，生成可执行文件：gcc hello.o -o hello

### 文件权限rwxrwxrwx代表什么意思？
前三位表示文件所有者的权限、中间三位是文件所有者所属组权限、后三位是其他用户的权限。777（111,111,111）表示所有用户可读可写可执行，754(111,101,100)表示文件拥有者具有可读可写可执行的权限，文件拥有者所在组有读、执行权限，而其他用户有读权限。

### umask()函数是干什么的？
umask用于影响新建立文件的默认权限，当新建立一个文件或目录时，系统会根据umask的值来“剥夺”文件或目录的相应权限。例如，如果umask的值是022的话，表示新创建的文件权限是622-022=755。即rwxr--r--。


### init进程的PID是多少？
空闲进程（当没有其他进程在运行时，内核所运行的进程，PID为0），在启动后，内核运行的第一个进程交init进程，PID为1

### 进程最大PID是多少？
32768，因为系统只使用16位来存储PID。

### 什么叫僵死进程？
如果一个子进程在父进程之前结束，内核应该把子进程设置为一个特殊的状态，处于这种状态的进程叫做僵死进程，进程只保留最小的概要信息，即一些保存着有用信息的内核数据结构。僵死的进程等待这父进程来查询自己的信息。只要父进程获取了子进程的信息，子进程就会消失，否则一直处于僵死状态。

### 如何建立守护进程
编写守护进程的一般步骤步骤：

（1）在父进程中执行fork并exit推出；

（2）在子进程中调用setsid函数创建新的会话；

（3）在子进程中调用chdir函数，让根目录 ”/” 成为子进程的工作目录；

（4）在子进程中调用umask函数，设置进程的umask为0；

（5）在子进程中关闭任何不需要的文件描述符

### TCP自己实现过吗？滑动窗口过程?

### dup/dup2的作用和区别
有时我们希望把标准输入重定向到一个文件，或者把标准输出重定向到一个网络连接。dup()与dup2()能对输入文件描述符进行重定向。dup重定向标准输出时需要先关闭stdout，而使用dup2时不需要。

dup:
```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("./a.log", O_CREAT|O_RDWR,0644);
    close(1);
    
    int new_fd = dup(fd);
    if(new_fd < 0)
    {
        perror("dup");
        return 0;
    }
    close(fd);
    
    char buf[1024];
    
    while(1)
    {
        memset(buf,0,sizeof(buf));
        scanf("%s",buf);
        if(buf[0] == 'q') break;
        printf("%s\n",buf);
        fflush(stdout); //必须做，因为重定向后printf函数将由行缓冲变为全缓冲  
    }
    close(new_fd);
    
    return 0;
}
```

dup2:
```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("./b.log", O_CREAT|O_RDWR,0644);
    close(1);
    
    int new_fd = dup2(fd,1);
    if(new_fd < 0)
    {
        perror("dup");
        return 0;
    }
    //close(fd);  //使用dup2不需要手动关闭原先的fd，系统自动关
    
    char buf[1024];
    
    while(1)
    {
        memset(buf,0,sizeof(buf));
        scanf("%s",buf);
        if(buf[0] == 'q') break;
        printf("%s\n",buf);
        fflush(stdout); //必须做，因为重定向后printf函数将由行缓冲变为全缓冲  
    }
    close(new_fd);
    
    return 0;
}
```

### sed, awk, grep的作用？
三个超强大的命名，分别用与格式化修改，统计，和正则查找

### http和https的区别？

### 多线程的生产者消费者模型？

### 出现close_wait状态是怎么回事？怎么解决？

### TCP如何实现可靠交付？

### 死锁的四个条件?

### 死锁的避免？

### 线程池的原理和实现？

### 内存池的原理和实现？

### IO复用的原理？

### select，epoll内部原理？？从select由来一直到epoll的优势，一一说明

###  IP首部，TCP首部，UDP首部？

### TCP和UDP应用场景

### TCP重发机制，Nagle算法


### 什么时候用多进程？什么时候用多线程？

### 进程间通讯方式?

管道( pipe )：管道是一种半双工的通信方式，数据只能单向流动，而且只能在具有亲缘关系的进程间使用。进程的亲缘关系通常是指父子进程关系。

命名管道 (FIFO) ： 有名管道也是半双工的通信方式，但是它允许无亲缘关系进程间的通信。

信号量：信号量用于实现进程间的互斥与同步，而不是用于存储进程间通信数据，有XSI信号量和POSIX信号量，POSIX信号量更加完善。

消息队列( message queue ) ： 消息队列是由消息的链表，存放在内核中并由消息队列标识符标识。消息队列克服了信号传递信息少、管道只能承载无格式字节流以及缓冲区大小受限等缺点。

共享内存( shared memory ) ：共享内存就是映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问。共享内存是最快的 IPC 方式，它是针对其他进程间通信方式运行效率低而专门设计的。它往往与其他通信机制，如信号两，配合使用，来实现进程间的同步和通信。(原理一定要清楚，常考)

信号 ( sinal ) ： 信号是一种比较复杂的通信方式，用于通知接收进程某个事件已经发生，常见的信号。

套接字( socket ) ： 套解口也是一种进程间通信机制，与其他通信机制不同的是，它可用于不同及其间的进程通信。

### 匿名管道与命名管道的区别?
匿名管道只能在具有公共祖先的两个进程间使用。

### 常见的信号有哪些？
SIGINT，SIGKILL(不能被捕获)，SIGTERM(可以被捕获)，SIGSEGV，SIGCHLD，SIGALRM

### 虚拟内存的作用和实现

### 孤儿进程与僵死进程
孤儿进程：一个父进程退出，而它的一个或多个子进程还在运行，那么那些子进程将成为孤儿进程。孤儿进程将被init进程(进程号为1)所收养，并由init进程对它们完成状态收集工作。

僵尸进程：一个进程使用fork创建子进程，如果子进程退出，而父进程并没有调用wait或waitpid获取子进程的状态信息，那么子进程的进程描述符仍然保存在系统中。这种进程称之为僵死进程。如果进程不调用wait / waitpid的话， 那么保留的那段信息就不会释放，其进程号就会一直被占用，但是系统所能使用的进程号是有限的，如果大量的产生僵死进程，将因为没有可用的进程号而导致系统不能产生新的进程. 此即为僵尸进程的危害，应当避免。

### 僵尸进程解决办法？
1.通过信号机制

子进程退出时向父进程发送SIGCHILD信号，父进程处理SIGCHILD信号。在信号处理函数中调用wait进行处理僵尸进程。测试程序如下所示：
```
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

static void sig_child(int signo);

int main()
{
    pid_t pid;
    //创建捕捉子进程退出信号
    signal(SIGCHLD,sig_child);
    pid = fork();
    if (pid < 0)
    {
        perror("fork error:");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("I am child process,pid id %d.I am exiting.\n",getpid());
        exit(0);
    }
    printf("I am father process.I will sleep two seconds\n");
    //等待子进程先退出
    sleep(2);
    //输出进程信息
    system("ps -o pid,ppid,state,tty,command");
    printf("father process is exiting.\n");
    return 0;
}

static void sig_child(int signo)
{
     pid_t        pid;
     int        stat;
     //处理僵尸进程
     while ((pid = waitpid(-1, &stat, WNOHANG)) >0)
            printf("child %d terminated.\n", pid);
}
```

2.fork两次

《Unix 环境高级编程》8.6节说的非常详细。原理是将子进程成为孤儿进程，从而其的父进程变为init进程，通过init进程可以处理僵尸进程。测试程序如下所示：
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    pid_t  pid;
    //创建第一个子进程
    pid = fork();
    if (pid < 0)
    {
        perror("fork error:");
        exit(1);
    }
    //第一个子进程
    else if (pid == 0)
    {
        //子进程再创建子进程
        printf("I am the first child process.pid:%d\tppid:%d\n",getpid(),getppid());
        pid = fork();
        if (pid < 0)
        {
            perror("fork error:");
            exit(1);
        }
        //第一个子进程退出
        else if (pid >0)
        {
            printf("first procee is exited.\n");
            exit(0);
        }
        //第二个子进程
        //睡眠3s保证第一个子进程退出，这样第二个子进程的父亲就是init进程里
        sleep(3);
        printf("I am the second child process.pid: %d\tppid:%d\n",getpid(),getppid());
        exit(0);
    }
    //父进程处理第一个子进程退出
    if (waitpid(pid, NULL, 0) != pid)
    {
        perror("waitepid error:");
        exit(1);
    }
    exit(0);
    return 0;
}
```

### du和df的区别和联系？
du，disk usage,是通过搜索文件来计算每个文件的大小然后累加，du能看到的文件只是一些当前存在 
的，没有被删除的。他计算的大小就是当前他认为存在的所有文件大小的累加和。

df，disk free，通过文件系统来快速获取空间大小的信息，当我们删除一个文件的时候，这个文件不 
是马上就在文件系统当中消失了，而是暂时消失了，当所有程序都不用时，才会根据OS的规则释放掉已 
经删除的文件， df记录的是通过文件系统获取到的文件的大小，他比du强的地方就是能够看到已经删除 
的文件，而且计算大小的时候，把这一部分的空间也加上了，更精确了。
当文件系统也确定删除了该文件后，这时候du与df就一致了。

常见的df和du不一致情况就是文件删除的问题。当一个文件被删除后，在文件系统 目录中已经不可见了，所以du就不会再统计它了。然而如果此时还有运行的进程持有这个已经被删除了的文件的句柄，那么这个文件就不会真正在磁盘中被删除， 分区超级块中的信息也就不会更改。这样df仍旧会统计这个被删除了的文件。

当出现du和df差距很大的情况时，考虑是否是有删除文件未完成造成的，方法是lsof命令，然后停止相关进程即可。

### 一个文件被删除了，没有被释放是什么原因呢?

### df和du底层/原理是什么，是干什么的，百分比计算是怎么算的?
du命令会对待统计文件逐个调用fstat这个系统调用，获取文件大小。它的数据是基于文件获取的，所以有很大的灵活性，不一定非要针对一个分区，可以跨越多个分区操作。如果针对的目录中文件很多，du速度就会很慢了。

df命令使用的事statfs这个系统调用，直接读取分区的超级块信息获取分区使用情况。它的数据是基于分区元数据的，所以只能针对整个分区。由于df直接读取超级块，所以运行速度不受文件多少影响。

### 内存映射是什么?

### timewait状态的时候，可以接受到新的请求吗？

### 怎么保证一个CPU只有一个线程运行?

### 协程了解过没有？

### 线程共享进程的什么，不共享什么，CPU共享吗？


### 多线程同步和互斥方法，内核态下有什么方法?
回答三个：信号、互斥量、条件遍历

### 缓冲区溢出是什么？会造成什么危害呢？出现原因是什么？

### 如何查看端口使用情况？
- lsof -i  
- lsof -i：端口号
- netstat -tunlp
- netstat -tunlp|grep 端口号

### 0.0.0.0与127.0.0.1的区别？
严格说来，0.0.0.0已经不是一个真正意义上的IP地址了。它表示的是这样一个集合：所有不清楚的主机和目的网络。这里的“不清楚”是指在本机的路由表里没有特定条目指明如何到达。对本机来说，它就是一个“收容所”，所有不认识的“三无”人员，一律送进去。如果你在网络设置中设置了缺省网关，那么Windows系统会自动产生一个目的地址为0.0.0.0的缺省路由。

127.0.0.1,本机地址，主要用于测试。用汉语表示，就是“我自己”。在Windows系统中，这个地址有一个别名“Localhost”。寻址这样一个地址，是不能把它发到网络接口的。除非出错，否则在传输介质上永远不应该出现目的地址为“127.0.0.1”的数据包。


### Linux的I/O模型介绍以及同步异步阻塞非阻塞的区别?

###  Epoll的ET模式和LT模式（ET的非阻塞）

### 硬链接和软链接（符号链接）的区别？
- 硬链接指向了物理硬盘的一个区块，事实上文件系统会维护一个引用计数，只要有文件指向这个区块，它就不会从硬盘上消失。
- 软链接： 保存了其代表的文件的绝对路径，是另外一种文件，在硬盘上有独立的区块，访问时替换自身路径。

ln we.txt hard

ln we.txt -s soft

删除源文件后，之前的硬链接没有丝毫地影响，因为它 inode 所指向的区块由于有一个硬链接在指向它，所以这个区块仍然有效，并且可以访问到。
然而软链接的 inode 所指向的内容实际上是保存了一个绝对路径，当用户访问这个文件时，系统会自动将其替换成其所指的文件路径，然而这个文件已经被删除了，所以自然就会显示无法找到该文件了。


### 海量数据的bitmap使用原理

###  怎么回收线程

### 异常和中断的区别

### 那在linux中，对于一个已经动态编译后的文件，怎么查找出它用了哪些动态库？ 
### 怎么查询一个文件的最后10行
tail指令

最后 10行 

tail -n 10 a.log

最后 5行

tail -n 5 a.log

最后10行的前5行

tail -n 10 a.log | head -n 5

### 

