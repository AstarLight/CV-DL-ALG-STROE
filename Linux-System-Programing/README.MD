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

### Linux进程状态有哪几种？
R、S、D、T、Z、X

R (TASK_RUNNING)，可执行状态；S (TASK_INTERRUPTIBLE)，可中断的睡眠状态；D (TASK_UNINTERRUPTIBLE)，不可中断的睡眠状态；T (TASK_STOPPED or TASK_TRACED)，暂停状态或跟踪状态；Z (TASK_DEAD - EXIT_ZOMBIE)，退出状态，进程成为僵尸进程；X (TASK_DEAD - EXIT_DEAD)，退出状态，进程即将被销毁。

### 如何建立守护进程
Linux Daemon（守护进程）是运行在后台的一种特殊进程。它独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件。
编写守护进程的一般步骤步骤：

（1）在父进程中执行fork并exit推出；

（2）在子进程中调用setsid函数创建新的会话；

（3）在子进程中调用chdir函数，让根目录 ”/” 成为子进程的工作目录；

（4）在子进程中调用umask函数，设置进程的umask为0；

（5）在子进程中关闭任何不需要的文件描述符．

```
    #include <unistd.h>   
    #include <signal.h>   
    #include <fcntl.h>  
    #include <sys/syslog.h>  
    #include <sys/param.h>   
    #include <sys/types.h>   
    #include <sys/stat.h>   
    #include <stdio.h>  
    #include <stdlib.h>  
    #include <time.h>  
      
    int init_daemon(void)  
    {   
        int pid;   
        int i;  
          
        // 1）屏蔽一些控制终端操作的信号  
        signal(SIGTTOU,SIG_IGN);   
        signal(SIGTTIN,SIG_IGN);   
        signal(SIGTSTP,SIG_IGN);   
        signal(SIGHUP ,SIG_IGN);  
       
        // 2）在后台运行  
        if( pid=fork() ){ // 父进程  
            exit(0); //结束父进程，子进程继续  
        }else if(pid< 0){ // 出错  
            perror("fork");  
            exit(EXIT_FAILURE);  
        }  
          
        // 3）脱离控制终端、登录会话和进程组  
        setsid();    
          
        // 4）禁止进程重新打开控制终端  
        if( pid=fork() ){ // 父进程  
            exit(0);      // 结束第一子进程，第二子进程继续（第二子进程不再是会话组长）   
        }else if(pid< 0){ // 出错  
            perror("fork");  
            exit(EXIT_FAILURE);  
        }    
          
        // 5）关闭打开的文件描述符  
        // NOFILE 为 <sys/param.h> 的宏定义  
        // NOFILE 为文件描述符最大个数，不同系统有不同限制  
        for(i=0; i< NOFILE; ++i){  
            close(i);  
        }  
          
        // 6）改变当前工作目录  
        chdir("/tmp");   
          
        // 7）重设文件创建掩模  
        umask(0);    
          
        // 8）处理 SIGCHLD 信号  
        signal(SIGCHLD,SIG_IGN);  
          
        return 0;   
    }   
      
    int main(int argc, char *argv[])   
    {  
        init_daemon();  
          
        while(1);  
      
        return 0;  
    }  
```

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

记一下比较经典的操作：
sed:
- sed -e '1d' inputfile (删除第一行)
- sed -e 'x1d' -e 'x2d' -e 'x3d' inputfile  (删除第x1,x2,x3行)
- sed -e '1,3d' file (删除第一到第三行)
- sed -e '1,$d' file  (删除第一行到最后一行)
- sed -e '/#/d' file  (删除含有'#'号的行)
- sed -e '/xx/!d' file (删除除含有字符串xx的所有行)
- sed -e '/t.*t/d' file     (删除含有两个t的行)
- sed -e 'nc/just do it' file  (把第n行替换成just do it)
- sed -e '1,10c/I can do it' file  (把1到10行替换成一行:I can do it)
- sed -e 's/w1/& w2/' file  （w1的地方输出 w1 w2）
- sed 's/book/books/' file (替换文本中book为books)
- sed -i 's/book/books/g' file （全局替换：换文本中book为books）
- sed -i 's/sk/SK/2g' file（从第2个匹配时开始替换）

### http和https的区别？
HTTPS和HTTP的区别主要如下：

1、https协议需要到ca申请证书，一般免费证书较少，因而需要一定费用。

2、http是超文本传输协议，信息是明文传输，https则是具有安全性的ssl加密传输协议。

3、http和https使用的是完全不同的连接方式，用的端口也不一样，前者是80，后者是443。

4、http的连接很简单，是无状态的；HTTPS协议是由SSL+HTTP协议构建的可进行加密传输、身份认证的网络协议，比http协议安全。




### 多线程的生产者消费者模型？

### 出现close_wait状态是怎么回事？怎么解决？
关闭socket分为主动关闭（Active closure）和被动关闭（Passive closure）两种情况。前者是指有本地主机主动发起的关闭；而后者则是指本地主机检测到远程主机发起关闭之后，作出回应，从而关闭整个连接。

在被动关闭连接情况下，在已经接收到FIN，但是还没有发送自己的FIN的时刻，连接处于CLOSE_WAIT状态。
通常来讲，CLOSE_WAIT状态的持续时间应该很短，正如SYN_RCVD状态。但是在一些特殊情况下，就会出现连接长时间处于CLOSE_WAIT状态的情况。

出现大量close_wait的现象，主要原因是某种情况下对方关闭了socket链接，但是我方忙与读或者写，没有关闭连接。代码需要判断socket，一旦读到0，断开连接，read返回负，检查一下errno，如果不是AGAIN，就断开连接。

解决：
1. 只能通过修改一下TCP/IP的参数，来缩短这个时间：修改tcp_keepalive_*系列参数有助于解决这个问题。 

### TCP如何实现可靠交付？

### 死锁的四个条件?
死锁产生的四个必要条件
- 互斥条件：资源是独占的且排他使用，进程互斥使用资源，即任意时刻一个资源只能给一个进程使用，其他进程若申请一个资源，而该资源被另一进程占有时，则申请者等待直到资源被占有者释放。
- 不可剥夺条件：进程所获得的资源在未使用完毕之前，不被其他进程强行剥夺，而只能由获得该资源的进程资源释放。
- 请求和保持条件：进程每次申请它所需要的一部分资源，在申请新的资源的同时，继续占用已分配到的资源。
- 循环等待条件：在发生死锁时必然存在一个进程等待队列{P1,P2,…,Pn},其中P1等待P2占有的资源，P2等待P3占有的资源，…，Pn等待P1占有的资源，形成一个进程等待环路，环路中每一个进程所占有的资源同时被另一个申请，也就是前一个进程占有后一个进程所申请地资源。 


### 死锁怎么预防？
我们可以通过破坏死锁产生的4个必要条件来 预防死锁，由于资源互斥是资源使用的固有特性是无法改变的。

- 破坏“不可剥夺”条件：一个进程不能获得所需要的全部资源时便处于等待状态，等待期间他占有的资源将被隐式的释放重新加入到 系统的资源列表中，可以被其他的进程使用，而等待的进程只有重新获得自己原有的资源以及新申请的资源才可以重新启动，执行。
- 破坏”请求与保持条件“：第一种方法静态分配即每个进程在开始执行时就申请他所需要的全部资源。第二种是动态分配即每个进程在申请所需要的资源时他本身不占用系统资源。
- 破坏“循环等待”条件：采用资源有序分配其基本思想是将系统中的所有资源顺序编号，将紧缺的，稀少的采用较大的编号，在申请资源时必须按照编号的顺序进行，一个进程只有获得较小编号的进程才能申请较大编号的进程。


### 死锁的避免？
银行家算法：他的思想是：把操作系统看成银行家，操作系统管理的资源看作是银行家管理的资金，进程向操作系统请求分配资源相当于用户向银行家贷款。当进程首次申请资源时，要测试改进程对资源的最大量，如果系统现存的资源可以满足它的最大需求量则按当前的申请量分配资源，否则推迟分配。当进程在执行中继续申请资源时，先测试该进程已占用的资源数与本次申请的资源数之和是否超过了该进程对资源的最大资源量。若超过则拒绝分配资源，若没有超过则再测试系统现存的资源能否满足该进程尚需的最大资源量，若能满足则按当前的申请量分配资源，否则也要推迟分配。

### 死锁怎么解除？
1. 资源剥夺法：挂起某些死锁进程，抢占他们的资源，将这些资源分配给其他死锁进程。
2. 撤销进程法：强制撤销部分、甚至全部死锁进程并剥夺这些进程的资源。
3. 进程回退法：让一个或多个进程回退到足以回避死锁的地步。

### 线程池的原理和实现？

### 内存池的原理和实现？

### IO复用的原理？
I/O多路复用实际上就是用select, poll, epoll监听多个io对象，当io对象有变化（有数据）的时候就通知用户进程。好处就是单个进程可以处理多个socket。
1. 当用户进程调用了select，那么整个进程会被block；
2. 而同时，kernel会“监视”所有select负责的socket；
3. 当任何一个socket中的数据准备好了，select就会返回；
4. 这个时候用户进程再调用read操作，将数据从kernel拷贝到用户进程。

　　所以，I/O 多路复用的特点是通过一种机制一个进程能同时等待多个文件描述符，而这些文件描述符（套接字描述符）其中的任意一个进入读就绪状态，select()函数就可以返回。如果处理的连接数不是很高的话，使用select/epoll的web server不一定比使用多线程 + 阻塞 IO的web server性能更好，可能延迟还更大。
select/epoll的优势并不是对于单个连接能处理得更快，而是在于能处理更多的连接。

### select，epoll内部原理？？从select由来一直到epoll的优势，一一说明
select缺点：
- 每次调用select，都需要把fd集合从用户态拷贝到内核态，这个开销在fd很多时会很大
- 每次调用select都需要在内核遍历传递进来的所有fd，这个开销在fd很多时也很大
- select支持的文件描述符数量太小了，默认是1024
- select的触发方式是水平触发，应用程序如果没有完成对一个已经就绪的文件描述符进行IO操作，那么之后每次select调用还是会将这些文件描述符通知进程。

poll缺点：
- poll修正了select的第三个缺点，即fd最大数量不受限制了，但其他缺点依旧存在

epoll的优点:
- 支持一个进程打开大数目的socket描述符
- IO效率不随FD数目增加而线性下降
- 使用mmap加速内核与用户空间的消息传递
- 支持边缘触发(ET)


在连接数很大，且活跃连接不多的情况下，使用epoll有明显的优势；而如果连接数较少，且连接基本都是活跃的，其实select的效果反而会更好。

内部原理：


poll和select的实现基本上是一致的，只是传递参数有所不同，他们的基本流程如下：

1. 复制用户数据到内核空间

2. 估计超时时间

3. 遍历每个文件并调用f_op->poll 取得文件当前就绪状态， 如果前面遍历的文件都没有就绪，向文件插入wait_queue节点

4. 遍历完成后检查状态：

- 如果已经有就绪的文件转到5；

- 如果有信号产生，重启poll或select（转到 1或3）；

- 否则挂起进程等待超时或唤醒，超时或被唤醒后再次遍历所有文件取得每个文件的就绪状态

5. 将所有文件的就绪状态复制到用户空间

6. 清理申请的资源

epoll的高效就在于，当我们调用epoll_ctl往里塞入百万个句柄时，epoll_wait仍然可以飞快的返回，并有效的将发生事件的句柄给我们用户。这是由于我们在调用epoll_create时，内核除了帮我们在epoll文件系统里建了个file结点，在内核cache里建了个红黑树用于存储以后epoll_ctl传来的socket外，还会再建立一个list链表，用于存储准备就绪的事件，当epoll_wait调用时，仅仅观察这个list链表里有没有数据即可。有数据就返回，没有数据就sleep，等到timeout时间到后即使链表没数据也返回。所以，epoll_wait非常高效。

而且，通常情况下即使我们要监控百万计的句柄，大多一次也只返回很少量的准备就绪句柄而已，所以，epoll_wait仅需要从内核态copy少量的句柄到用户态而已，如何能不高效？！

那么，这个准备就绪list链表是怎么维护的呢？当我们执行epoll_ctl时，除了把socket放到epoll文件系统里file对象对应的红黑树上之外，还会给内核中断处理程序注册一个回调函数，告诉内核，如果这个句柄的中断到了，就把它放到准备就绪list链表里。所以，当一个socket上有数据到了，内核在把网卡上的数据copy到内核中后就来把socket插入到准备就绪链表里了。

如此，一颗红黑树，一张准备就绪句柄链表，少量的内核cache，就帮我们解决了大并发下的socket处理问题。执行epoll_create时，创建了红黑树和就绪链表，执行epoll_ctl时，如果增加socket句柄，则检查在红黑树中是否存在，存在立即返回，不存在则添加到树干上，然后向内核注册回调函数，用于当中断事件来临时向准备就绪链表中插入数据。执行epoll_wait时立刻返回准备就绪链表里的数据即可。







###  IP首部，TCP首部，UDP首部？

### TCP和UDP应用场景

### TCP重发机制，Nagle算法
Nagle的文档里定义了处理他所谓的小包问题的方法，这种问题指的是应用程序一次产生一字节数据，这样会导致网络由于太多的包而过载（一个常见的情况是发送端的"糊涂窗口综合症(Silly Window Syndrome)"）。从键盘输入的一个字符，占用一个字节，可能在传输上造成41字节的包，其中包括1字节的有用信息和40字节的首部数据。这种情况转变成了4000%的消耗!

Nagle算法主要是避免发送小的数据包，要求TCP连接上最多只能有一个未被确认的小分组，在该分组的确认到达之前不能发送其他的小分组。

针对上面提到的这个状况，Nagle算法的改进在于：如果发送端欲多次发送包含少量字符的数据包（一般情况下，后面统一称长度小于MSS的数据包为小包，与此相对，称长度等于MSS的数据包为大包，为了某些对比说明，还有中包，即长度比小包长，但又不足一个MSS的包），则发送端会先将第一个小包发送出去，而将后面到达的少量字符数据都缓存起来而不立即发送，直到收到接收端对前一个数据包报文段的ACK确认、或当前字符属于紧急数据，或者积攒到了一定数量的数据（比如缓存的字符数据已经达到数据包报文段的最大长度）等多种情况才将其组成一个较大的数据包发送出去。

- nagle 算法是:   发送端 收到前一个报文的确认然后再发送下一个tcp数据。这样可以避免大量的小数据。 TCP_NODELAY选项控制。
- Delay ACK是:   接收端 在等待超时（还有其他发送ack确认的时机） 然后才发送ACK给客户端。
- CORK算法 是:  发送端 尽可能的进行数据的组包，以最大mtu传输，如果发送的数据包大小过小则如果在0.6~0.8S范围内都没能组装成一个MTU时，直接发送。

### 什么时候用多进程？什么时候用多线程？

### 进程间通讯方式?

管道( pipe )：管道是一种半双工的通信方式，数据只能单向流动，而且只能在具有亲缘关系的进程间使用。进程的亲缘关系通常是指父子进程关系。

命名管道 (FIFO) ： 有名管道也是半双工的通信方式，但是它允许无亲缘关系进程间的通信。
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FIFO_CHANNEL "./fifo.channel"
#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    int fd;
    int pid;
    char recv_buf[BUF_SIZE] = {0};
    
    if(argc != 2)
    {
    	printf("Invalid input! Corrected usage: %s (1|2) \n",argv[0]);
    	return -1;
    }

    //write msg to fifo
    if(atoi(argv[1]) == 1)
    {
    	int count = 1;
    	if(mkfifo(FIFO_CHANNEL,0777) == -1)
    	{
    		perror("cannot create fifo channel!\n");
    		return -1;
    	}

    	fd = open(FIFO_CHANNEL,O_WRONLY);
    	if(fd == -1)
    	{
    		perror("cannot open FIFO\n");
    		return -1;
    	}
    	while(1)
    	{
	    	char s_msg[128] = {0};
	    	sprintf(s_msg,"%d msg to other process.\n",count++);
	    	//注意，如果没有fifo，另一端没有进程读取数fifo数据，write将一直拥塞
	    	if(write(fd,s_msg,strlen(s_msg)) == -1)
	    	{
	    		perror("process cannot write data to  fifo!\n");
	    		return -1;
	    	}
	    	else
	    	{
	    		printf("send msg: %s\n",s_msg);
	    	}
	    	sleep(1);
    	}
    }
    else if (atoi(argv[1]) == 2)  //receive msg from fifo
    {
    	fd = open(FIFO_CHANNEL,O_RDONLY);
    	if(fd == -1)
    	{
    		perror("cannot open the FIFO\n");
    		return -1;
    	}
    	while(1)
    	{
            //注意，如果没有fifo，另一端没有进程向fifo写数据，read将一直拥塞
	    	if(read(fd,recv_buf,BUF_SIZE) == -1)
	    	{
	    		perror("process cannot read data from fifo!\n");
	    		memset(recv_buf,0,BUF_SIZE);
	    	}
	    	else
	    	{
	    		printf("receive msg from fifo : %s\n",recv_buf);
	    	}
    	}
    }
    else
    {
    	printf("Invalid input! Corrected usage: %s (1|2) \n",argv[0]);
    	return -1;
    }

    return 0;
}

```

信号量：信号量用于实现进程间的互斥与同步，而不是用于存储进程间通信数据，有XSI信号量和POSIX信号量，POSIX信号量更加完善。

消息队列( message queue ) ： 消息队列是由消息的链表，存放在内核中并由消息队列标识符标识。消息队列克服了信号传递信息少、管道只能承载无格式字节流以及缓冲区大小受限等缺点。

查看msgqid的方法：ipcs -q

msg_recv:
```
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define MSG_TYPE 100

typedef struct 
{
    long mtype;
    char mtext[BUF_SIZE];
}msg_info_t;

int recv_msg(int msqid, int msg_type, char msg[])
{
    int result;
    msg_info_t buffer;
    buffer.mtype = msg_type;

    result = msgrcv(msqid, &buffer, BUF_SIZE, msg_type, 0);
    if(result == -1)
    {
        perror("cannot receive msg from msg queue!\n");
    }

    strcpy(msg, buffer.mtext);

    return result;
}

int main(int argc, char *argv[])
{
    int msqid = atoi(argv[1]);

    char buf[BUF_SIZE] = {0};
    while(1)
    {
        if(recv_msg(msqid, MSG_TYPE, buf) == -1)
        {
            perror("cannot get msg!\n");
            return -1;
        }
        else
        {
            printf("recv msg: %s\n",buf);
        }
    }

    return 0;
}
```
msg_send:
```
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256
#define MYKEY 168
#define MSG_TYPE 100

typedef struct 
{
    long mtype;
    char mtext[BUF_SIZE];
}msg_info_t;

int create_msg_queue()
{
    key_t key;
    int msqid;
    key = MYKEY;

    msqid = msgget(key, IPC_CREAT|0660);
    if(msqid == -1)
    {
        perror("cannot create msg queue!\n");
        return -1;
    }

    return msqid;
}

int send_msg(int msqid, char msg[])
{
    int result;
    msg_info_t buf;

    buf.mtype = MSG_TYPE;
    strcpy(buf.mtext, msg);

    result = msgsnd(msqid, &buf, strlen(msg), 0);
    if(result == -1)
    {
        perror("cannot send msg to msg queue!\n");
        return -1;
    }

    return result;
}

int main()
{
    int msqid;
    if(msqid=create_msg_queue() < 0)
    {
        perror("fail to create msg queue!\n");
        return -1;
    }

    char str[] = "hello friend!\n";
    
    while(1)
    {
        if(send_msg(msqid, str) < 0)
        {
            perror("fail to send msg to msg queue!\n");
            return -1;
        }

        sleep(1);
    }

    return 0;
}
```

共享内存( shared memory ) ：共享内存就是映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问。共享内存是最快的 IPC 方式，它是针对其他进程间通信方式运行效率低而专门设计的。通常是由一个进程开辟一块共享内存区域，然后允许多个进程对此区域进行访问。由于不需要使用中间介质，而是数据由内存直接映射到进程空间，因此共享内存是最快速的进程间通信机制。它往往与其他通信机制，如信号量，配合使用，来实现进程间的同步和通信。(原理一定要清楚，常考)
```
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SHM_SIZE 1024
#define MYKEY 24

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		perror("Invalid input!Usage: %s (1|2)\n");
		return -1;
	}
	if(atoi(argv[1]) == 1)  //write msg to shared memory
	{
		key_t key;
		int shmid;
		char* shm_addr;

		key = ftok("./", MYKEY);
		if(key == -1)
		{
			perror("cannot generate the IPC key!\n");
			return -1;
		}

		shmid = shmget(key, SHM_SIZE, IPC_CREAT|0660);
		if(shmid == -1)
		{
			perror("cannot create a shared memory segment!\n");
			return -1;
		}

		shm_addr = (char*)shmat(shmid,NULL,0);
		if(shm_addr == (char*)-1)
		{
			perror("cannot attach the shared memory to process!\n");
			return -1;
		}

		while(1)
		{
			printf("input:");
			scanf("%s",shm_addr);			
		}

	}
	else if(atoi(argv[1]) == 2)  // read msg from shared memory
	{
		key_t key;
		int shmid;
		char* shm_addr;

		key = ftok("./", MYKEY);
		if(key == -1)
		{
			perror("cannot generate the IPC key!\n");
			return -1;
		}

		shmid = shmget(key, SHM_SIZE, IPC_CREAT|0660);
		if(shmid == -1)
		{
			perror("cannot create a shared memory segment!\n");
			return -1;
		}

		shm_addr = (char*)shmat(shmid,NULL,0);
		if(shm_addr == (char*)-1)
		{
			perror("cannot attach the shared memory to process!\n");
			return -1;
		}
		int read_conut = 0;
		while(1)
		{
			if(read_conut > 20)
				break;
			printf("out:%s\n",shm_addr);
			sleep(3);
			read_conut++;
		}

		
		if(shmdt(shm_addr) == -1)
	    {
	        perror("shmdt department error!\n");
	        return -1;
	    }

	    // 删除共享内存
	    if(shmctl(shmid, IPC_RMID, 0) == -1)
	    {
	        perror("shmctl delete error!\n");
	        return -1;
	    }
	}
	else
	{
		perror("Invalid input!Usage: %s (1|2)\n");
		return -1;		
	}

	return 0;
}
```

信号 ( sinal ) ： 信号是一种比较复杂的通信方式，用于通知接收进程某个事件已经发生，常见的信号。

套接字( socket ) ： 套解口也是一种进程间通信机制，与其他通信机制不同的是，它可用于不同及其间的进程通信。

### 匿名管道与命名管道的区别?
匿名管道只能在具有公共祖先的两个进程间使用。

### 怎么实现管道的双向通信？
在Linux系统中，管道只能实现单向通信，因此要实现双向通信，必须创建两个管道：一个作为读取数据的管道，一个作为写入数据的管道。

### 常见的信号有哪些？
SIGINT，SIGKILL(不能被捕获)，SIGTERM(可以被捕获)，SIGSEGV，SIGCHLD，SIGALRM

### 什么是线程同步？
同步就是协同步调，按预定的先后次序进行运行。如：你说完，我再说。如进程、线程同步，可理解为进程或线程A和B一块配合，A执行到一定程度时要依靠B的某个结果，于是停下来，示意B运行；B依言执行，再将结果给A；A再继续操作。线程同步：即当有一个线程在对内存进行操作时，其他线程都不可以对这个内存地址进行操作，直到该线程完成操作， 其他线程才能对该内存地址进行操作，而其他线程又处于等待状态，目前实现线程同步的方法有很多，临界区对象就是其中一种。 

### 线程同步的方式有哪几种？
互斥锁、信号量、条件变量
- 互斥锁
```
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_lock(pthread_mutex *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex *mutex);
```
- 信号量
```
int sem_init (sem_t *sem , int pshared, unsigned int value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_destroy(sem_t *sem);
```

- 条件变量:条件变量用来自动阻塞一个线程，直到某特殊情况发生为止。通常条件变量和互斥锁同时使用。条件变量分为两部分: 条件和变量。条件本身是由互斥量保护的。线程在改变条件状态前先要锁住互斥量。条件变量使我们可以睡眠等待某种条件出现。条件变量是利用线程间共享的全局变量进行同步的一种机制，主要包括两个动作：一个线程等待"条件变量的条件成立"而挂起；另一个线程使"条件成立"（给出条件成立信号）。条件的检测是在互斥锁的保护下进行的。如果一个条件为假，一个线程自动阻塞，并释放等待状态改变的互斥锁。如果另一个线程改变了条件，它发信号给关联的条件变量，唤醒一个或多个等待它的线程，重新获得互斥锁，重新评价条件。
```
pthread_cond_t cond = PTHREAD_COND_INITIALIER;
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond); //解除所有线程的阻塞
int pthread_cond_destroy(pthread_cond_t *cond);
```

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
当文件进程锁定，或者有进程一直在向这个文件写数据，就会出现这种删除文件后空间不释放的情况。

### df和du底层/原理是什么，是干什么的，百分比计算是怎么算的?
du命令会对待统计文件逐个调用fstat这个系统调用，获取文件大小。它的数据是基于文件获取的，所以有很大的灵活性，不一定非要针对一个分区，可以跨越多个分区操作。如果针对的目录中文件很多，du速度就会很慢了。

df命令使用的事statfs这个系统调用，直接读取分区的超级块信息获取分区使用情况。它的数据是基于分区元数据的，所以只能针对整个分区。由于df直接读取超级块，所以运行速度不受文件多少影响。

### 内存映射是什么?
mmap是一种内存映射文件的方法，即将一个文件或者其它对象映射到进程的地址空间，实现文件磁盘地址和进程虚拟地址空间中一段虚拟地址的一一对映关系。

1. 通过以上的分析，发现应用程序通过read,write,ioctl来访问硬件设备，它们都要经过两次的数据拷贝，一次是用户空间和内核空间的数据拷贝，另外一次是内核空间和硬件之间的数据拷贝
2. 用户访问设备，最终其实涉及的用户和硬件，而read,write,ioctl本身会牵扯到内核，所以这些函数涉及2次的数据拷贝，用户要直接去访问硬件设备，只需要将硬件设备的物理地址信息映射到用户的虚拟地址空间即可，一旦完毕，不会在牵扯到内核空间，以后用户直接访问用户的虚拟地址就是在访问设备硬件，由2次的数据拷贝的
转换为一次的数据拷贝。(mmap)

MMAP内存映射区作用：目的：将硬件物理地址映射到用户虚拟地址空间，由2次数据拷贝变成1次数据拷贝！

让用户程序直接访问设备内存，在要求高性能的应用当中比较常用。应用程序使用的动态库映射到这个区域；
应用程序调用mmap，将设备物理地址和这个区域的虚拟内存进行映射；
mmap映射内存必须是页面大小的整数倍（也就是字节/4K）.当访问的文件比较小时，可以用read、write，文件比较大时，用mmap

```
/*
 * mmap file to memory
 * ./mmap1 data.txt
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
        int fd = -1;
        struct stat sb;
        char *mmaped = NULL;

        fd = open(argv[1], O_RDWR);
        if (fd < 0) {
                fprintf(stderr, "open %s fail\n", argv[1]);
                exit(-1);
        }

        if (stat(argv[1], &sb) < 0) {
                fprintf(stderr, "stat %s fail\n", argv[1]);
                goto err;
        }

        /* 将文件映射至进程的地址空间 */
        mmaped = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (mmaped == (char *)-1) {
                fprintf(stderr, "mmap fail\n");
                goto err;
        }

        /* 映射完后, 关闭文件也可以操纵内存 */
        close(fd);
        printf("%s", mmaped);

        mmaped[5] = '$';
        if (msync(mmaped, sb.st_size, MS_SYNC) < 0) {
                fprintf(stderr, "msync fail\n");
                goto err;
        }
        
        printf("%s",mmaped);

        return 0;

err:
        if (fd > 0)
                close(fd);

        if (mmaped != (char *)-1)
                munmap(mmaped, sb.st_size);

        return -1;
}

```

### timewait状态的时候，可以接受到新的请求吗？
![](./74311666jw1f2cc3saeoej20d40iygnj.jpg) 

如果只看连接释放阶段，四次握手

- 客户端先发送FIN，进入FIN_WAIT1状态
- 服务端收到FIN，发送ACK，进入CLOSE_WAIT状态，客户端收到这个ACK，进入FIN_WAIT2状态
- 服务端发送FIN，进入LAST_ACK状态
- 客户端收到FIN，发送ACK，进入TIME_WAIT状态，服务端收到ACK，进入CLOSE状态
- 客户端TIME_WAIT持续2倍MSL时长，在linux体系中大概是60s，转换成CLOSE状态

TCP主动断开连接的一方可能是客户端，也可能是服务端。能不能发送完ACK之后不进入TIME_WAIT就直接进入CLOSE状态呢？不行的，这个是为了TCP协议的可靠性，由于网络原因，ACK可能会发送失败，那么这个时候，被动一方会主动重新发送一次FIN，这个时候如果主动方在TIME_WAIT状态，则还会再发送一次ACK，从而保证可靠性。那么从这个解释来说，2MSL的时长设定是可以理解的，MSL是报文最大生存时间，如果重新发送，一个FIN＋一个ACK，再加上不定期的延迟时间，大致是在2MSL的范围。

### 怎么保证一个CPU只有一个线程运行?

### 协程了解过没有？

### 线程共享进程的什么，不共享什么，CPU共享吗？
线程共享的环境包括：进程代码段、进程的公有数据(利用这些共享的数据，线程很容易的实现相互之间的通讯)、进程打开的文件描述符、信号的处理器、进程的当前目录和进程用户ID与进程组ID。

进程拥有这许多共性的同时，还拥有自己的个性。有了这些个性，线程才能实现并发性。这些个性包括：
1. 线程ID
2. 寄存器组的值
3. 线程的栈
4. 错误返回码
5. 线程的信号屏蔽码
6. 线程的优先级

### 多线程同步和互斥方法，内核态下有什么方法?
回答三个：信号、互斥量、条件变量

### 缓冲区溢出是什么？会造成什么危害呢？出现原因是什么？
溢出，在计算机程序中，就是数据使用到了被分配内存空间之外的内存空间。而缓冲区溢出，简单的说就是计算机对接收的输入数据没有进行有效的检测（理想的情况是程序检查数据长度并不允许输入超过缓冲区长度的字符），向缓冲区内填充数据时超过了缓冲区本身的容量，而导致数据溢出到被分配空间之外的内存空间，使得溢出的数据覆盖了其他内存空间的数据。

### 如何查看端口使用情况？
- lsof -i  
- lsof -i：端口号
- netstat -tunlp
- netstat -tunlp|grep 端口号

### 0.0.0.0与127.0.0.1的区别？
严格说来，0.0.0.0已经不是一个真正意义上的IP地址了。它表示的是这样一个集合：所有不清楚的主机和目的网络。这里的“不清楚”是指在本机的路由表里没有特定条目指明如何到达。对本机来说，它就是一个“收容所”，所有不认识的“三无”人员，一律送进去。如果你在网络设置中设置了缺省网关，那么Windows系统会自动产生一个目的地址为0.0.0.0的缺省路由。

127.0.0.1,本机地址，主要用于测试。用汉语表示，就是“我自己”。在Windows系统中，这个地址有一个别名“Localhost”。寻址这样一个地址，是不能把它发到网络接口的。除非出错，否则在传输介质上永远不应该出现目的地址为“127.0.0.1”的数据包。


### Linux的I/O模型介绍以及同步异步阻塞非阻塞的区别?
- 阻塞 I/O（blocking IO）:说明：任何一个系统调用都会产生一个由用户态到内核态切换，再从内核态到用户态切换的过程，而进程上下文切换是通过系统中断程序来实现的，需要保存当前进程的上下文状态，这是一个极其费力的过程。
![](./20150111112815015.png)

- 非阻塞 I/O（nonblocking IO）:当我们把套接口设置成非阻塞时，就是由用户进程不停地询问内核某种操作是否准备就绪，这就是我们常说的“轮询”。这同样是一件比较浪费CPU的方式。
![](./20150111112909184.png)

- I/O 多路复用（ IO multiplexing）:有一点不同于阻塞IO的就是，尽管看起来与阻塞IO相比，这里阻塞了两次，但是第一次阻塞在select上时，select可以监控多个套接口上是否已有IO操作准备就绪的，而不是像阻塞IO那种，一次性只能监控一个套接口。
![](./20150111112917109.png)

- 信号驱动 I/O（ signal driven IO）:信号驱动IO就是说我们可以通过sigaction系统调用注册一个信号处理程序，然后主程序可以继续向下执行，当我们所监控的套接口有IO操作准备就绪时，由内核通知触发前面注册的信号处理程序执行，然后将我们所需要的数据从内核空间拷贝到用户空间。

![](./20150111113004736.png)

- 异步 I/O（asynchronous IO）:异步IO与信号驱动IO最主要的区别就是信号驱动IO是由内核通知我们何时可以进行IO操作了，而异步IO则是由内核告诉我们IO操作何时完成了。具体来说就是，信号驱动IO当内核通知触发信号处理程序时，信号处理程序还需要阻塞在从内核空间缓冲区拷贝数据到用户空间缓冲区这个阶段，而异步IO直接是在第二个阶段完成后内核直接通知可以进程后续操作了。
![](./20150111113026654.png)

总结：

![](./20150111113049149.png)


###  Epoll的ET模式和LT模式（ET的非阻塞）?
- LT(level triggered，水平触发模式)是缺省的工作方式，并且同时支持 block 和 non-block socket。在这种做法中，内核告诉你一个文件描述符是否就绪了，然后你可以对这个就绪的fd进行IO操作。如果你不作任何操作，内核还是会继续通知你的，所以，这种模式编程出错误可能性要小一点。比如内核通知你其中一个fd可以读数据了，你赶紧去读。你还是懒懒散散，不去读这个数据，下一次循环的时候内核发现你还没读刚才的数据，就又通知你赶紧把刚才的数据读了。这种机制可以比较好的保证每个数据用户都处理掉了。

- ET(edge-triggered，边缘触发模式)是高速工作方式，只支持no-block socket。在这种模式下，当描述符从未就绪变为就绪时，内核通过epoll告诉你。然后它会假设你知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的就绪通知，等到下次有新的数据进来的时候才会再次出发就绪事件。简而言之，就是内核通知过的事情不会再说第二遍，数据错过没读，你自己负责。这种机制确实速度提高了，但是风险相伴而行。

### 硬链接和软链接（符号链接）的区别？
- 硬链接指向了物理硬盘的一个区块，事实上文件系统会维护一个引用计数，只要有文件指向这个区块，它就不会从硬盘上消失。
- 软链接： 保存了其代表的文件的绝对路径，是另外一种文件，在硬盘上有独立的区块，访问时替换自身路径。

ln we.txt hard

ln we.txt -s soft

删除源文件后，之前的硬链接没有丝毫地影响，因为它 inode 所指向的区块由于有一个硬链接在指向它，所以这个区块仍然有效，并且可以访问到。
然而软链接的 inode 所指向的内容实际上是保存了一个绝对路径，当用户访问这个文件时，系统会自动将其替换成其所指的文件路径，然而这个文件已经被删除了，所以自然就会显示无法找到该文件了。


### 海量数据的bitmap使用原理

###  怎么回收线程?
默认的条件下，一个线程结束后，其对应的资源不会被释放，于是，如果在一个程序中，反复建立线程，而线程又默认的退出，则最终线程资源耗尽，进程将不再能建立新的线程。线程是可结合的（joinable），或者是分离的（detached）。一个可结合的线程能够被其他线程收回其资源和杀死；在被其他线程回收之前，它的存储器资源（如栈）是不释放的。相反，一个分离的线程是不能被其他线程回收或杀死的，它的存储器资源在它终止时由系统自动释放。线程回收问题，有2种方式，系统自动释放线程资源，或者由另一个线程释放该线程资源。
- 系统自动释放：如果想在线程结束时，由系统释放线程资源，则需要设置线程属性为detach，是线程分离主线程。pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);      //设置线程属性
- 由另一个线程将该资源释放:pthread_join(t)//等待线程t退出，并释放t线程所占用的资源。注意：在默认情况下线程可结合状态的
- 设置线程分离状态的函数为pthread_attr_setdetachstate（pthread_attr_t *attr, int detachstate）。第二个参数可选为PTHREAD_CREATE_DETACHED（分离线程）和 PTHREAD _CREATE_JOINABLE（非分离线程）。
- 这里要注意的一点是，如果设置一个线程为分离线程，而这个线程运行又非常快，它很可能在pthread_create函数返回之前就终止了，它终止以后就可能将线程号和系统资源移交给其他的线程使用，这样调用pthread_create的线程就得到了错误的线程号。要避免这种情况可以采取一定的同步措施，最简单的方法之一是可以在被创建的线程里调用pthread_cond_timewait函数，让这个线程等待一会儿，留出足够的时间让函数pthread_create返回。


### 异常和中断的区别
中断和异常的作用是指示系统中的某个地方发生一些事件, 需要引起处理器(包括正在执行中的程序和任务)的注意. 当中断和异常发生时, 典型的结果是迫使处理器将控制从当前正在执行的程序或任务转移到另一个历程或任务中去. 该例程叫做中断处理程序, 或者异常处理程序. 如果是一个任务, 则发生任务切换.
- 异常是80386在执行指令期间检测到不正常的或非法的条件所引起的。异常与正执行的指令有直接的联系。例如，执行除法指令时，除数等于0、地址越界、虚拟内存缺页。再如，执行指令时发现特权级不正确。当发生这些情况时，指令就不能成功完成。
- 中断是由异步的外部事件引起的，比如设备发出的IO结束中断。包括硬中断和软中断。

### 那在linux中，对于一个已经动态编译后的文件，怎么查找出它用了哪些动态库？ 


### 怎么查询一个文件的最后10行
tail指令

最后 10行 

tail -n 10 a.log

最后 5行

tail -n 5 a.log

最后10行的前5行

tail -n 10 a.log | head -n 5

### 什么是惊群效应？
使用线程池会发生惊群效应。惊群现象就是多进程（多线程）在同时阻塞等待同一个事件的时候（休眠状态），如果等待的这个事件发生，那么他就会唤醒等待的所有进程（或者线程），但是最终却只可能有一个进程（线程）获得这个时间的“控制权”，对该事件进行处理，而其他进程（线程）获取“控制权”失败，只能重新进入休眠状态，这种现象和性能浪费就叫做惊群。

解决惊群问题:Nginx中使用mutex互斥锁解决这个问题，具体措施有使用全局互斥锁，每个子进程在epoll_wait()之前先去申请锁，申请到则继续处理，获取不到则等待，并设置了一个负载均衡的算法（当某一个子进程的任务量达到总设置量的7/8时，则不会再尝试去申请锁）来均衡各个进程的任务量。

惊群效应到底消耗了什么：
1. 系统对用户进程/线程频繁的做无效的调度、上下文切换，系统系能大打折扣。
2. 为了确保只有一个线程得到资源，用户必须对资源操作进行加锁保护，进一步加大了系统开销。



### 计算机网络怎么划分层次的？
OSI七层模型：
- 应用层
- 表示层
- 会话层
- 传输层
- 网络层
- 数据链路层
- 物理层

TCP/IP四层模型：
- 应用层
- 传输层
- 网际层
- 网络接口层

五层模型：
- 应用层
- 传输层(TCP UDP ARQ)
- 网络层(IP ICMP ARP IGMP NAT)
- 数据链路层(PPP）
- 物理层

### 数据链路层的三个基本问题是什么？
封装成帧（帧首部和尾部）、透明传输（字节填充）、差错检测（CRC，不是可靠传输）。

### TCP和UDP在应用层都有哪些应用呢？
- UDP:DNS(53),TFTP(69),RIP,DHCP,SNMP(161)
- TCP:SMTP,TELNET(23),HTTP(80),FTP(21)

###　TCP如何实现可靠通信？
停止等待协议和自动重传请求ARQ。即每次发送信息都需要对方确认，如果在指定时间内没收到对方确认，那就重传刚才的数据包。

### TCP如何实现拥塞控制？
慢开始、拥塞避免、快重传、快恢复

![](./20160909153222894.png) 

### 什么是CSMA/CD协议?
这是一个数据链路层上的协议，中文全称为：载波监听多点接入/碰撞检测。它的核心思想是：
1. 发送前先检测信道，信道忙则等待；
2. 边发送边检测信道，争用期内未检测到碰撞，则该帧发送成功，若检测碰撞，则停止发送数据，执行截断二进制指数避让算法等待重传，若重传１６次仍不成功则停止重传向上报错。

### A,B,C,D类地址是怎么划分的？
- 1.0.0.0到126.255.255.255为A类 主要分配给具有大量主机而局域网络数量较少的大型网络
- 128.0.0.0到191.255.255.255为B类 一般用于国际性大公司和政府机构
- 192.0.0.0到223.255.255.255为C类 用于一般小公司 校园网 研究机构等
- 224.0.0.0到239.255.255.255为D类 用于特殊用途. 又称做广播地址
- 240.0.0.0到247.255.255.255为E类. 暂时保留

### 两个进程访问临界区资源，会不会出现都获得自旋锁的情况？

### 怎么唤醒被阻塞的socket线程？

### 怎样确定当前线程是繁忙还是阻塞？

### 就绪状态的进程在等待什么？

### 死循环+来连接时新建线程的方法效率有点低，怎么改进？

### 键盘敲一个A，发生了什么?

### 网络编程中，怎么建立UDP/TCP服务器和客户端？

### 怎么根据场景选择服务器类型？

### 什么是Linux系统调用？
系统调用就是用户进入内核态然后执行特权指令然后再回到用户态。用户程序只在用户态下运行，有时需要访问系统核心功能，这时通过系统调用接口使用系统调用。常用系统调用有fork、exit、getpid、wait、open、read、write

### 系统调用和普通调用的区别？
系统调用本质上是一种过程调用，但它是一种特殊的过程调用，与一般用户程序中的过程调用有明显的区别 。 
- 运行状态不同。
系统调用的调用过程和被调用过程运行在不同的状态，而普通的过程调用一般运行在相同的状态。 
- 调用方法不同。
系统调用必须通过软中断机制首先进入系统核心，然后才能转向相应的命令处理程序。普通过程调用可以直接由调用过程转向被调用过程。 
- 返回问题。
在采用抢先式调度的系统中，当系统调用返回时，要重新进行调度分析――是否有更高优先级的任务就绪。普通的过程调用直接返回调用过程继续执行。 

### Linux查看一个100G的文件该用什么命令?

### Linux用户态占用过高怎么排查?

###  cat的原理?

### DNS解析过程?

### 进程有哪些状态？
- 运行状态
- 就绪状态
- 等待状态
- 创建状态
- 结束状态

前三个是三种最基本的状态。

![](./20160728195253757.png)

就绪状态和等待状态的区别在于：就绪状态是缺少cpu而不能执行，而等待状态又叫拥塞状态，该状态表明进程缺少的是除cpu外的其他资源（事件或资源）。

### 为什么要引入线程？
为了减小程序在并发执行时所付出的时空开销，提高操作系统的并发性能。线程，是被系统调度和分配的基本单位。

### 线程与进程的区别？
- 调度。
- 拥有资源。
- 并发性。
- 系统开销。
- 地址空间和其他资源。
- 通信方式。

### 调度算法有哪些？
- 先来先服务（FCFS）调度算法：对长作业有利，对短作业不利，有利于CPU繁忙型作业，不利于IO繁忙型作业。
- 短作业优先（SJF）：平均等待时间、平均周转时间最小，对长作业不利（饥饿），没考虑作业的紧迫程度，不合理。
- 优先级调度算法。
- 高响应比优先调度算法：响应比=（等待时间+要求服务时间）/要求服务时间
- 时间片轮转调度算法。
- 
