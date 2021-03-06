## 分布式系统知识点汇总。

### map reduce的原理是什么？

### 一致性哈希是如何实现的？


### 分布式系统和单机系统的区别在哪里？
根本区别在于进程空间时一个还是多个。分布式系统不是放大的单机系统，因为单机没有部分故障的情况。对于单机，我们很容易判断某个进程、某个硬件是否还在正常工作。但在分布式系统中，这是无解的，我们无法及时得知另一台机器的死活，也无法把机器崩溃和网络故障区分开来。这正是分布式系统与单机的最大区别。

### 怎么用Redis来实现分布式锁？
实现思路为:

当我们在执行代码前，先去设置一个分布式锁

其实就是给Redis设置一个Key,但是要这个Key不存再的情况下才可以设置成功

如果设置成功，表示当前进程拿到锁，可以执行后续代码 

如果设置失败，表示其它进程已经锁定，那么我们就要让当前进程休眠一下，然后再去重试设置锁

直到设置锁成功，才表示当前进程锁定，才可以执行自定义代码

在执行自宝义代码后，释放锁，这样其它进程就可以拿到锁了

我们在设置锁的时候，为了防此自定义代码报错，而出现死锁的情况

所以我们在设置锁的时候可以设置锁的一个过期时间，这样就算自定义代码出错，没有释放锁的情况下

其它进程也可以在一定时间内拿到锁，当然可以try,catch把自定义代码包起来


### 什么是CAP原则？
CAP原则又称CAP定理，指的是在一个分布式系统中， Consistency（一致性）、 Availability（可用性）、Partition tolerance（分区容错性），三者不可得兼。

- 一致性（C）：在分布式系统中的所有数据备份，在同一时刻是否同样的值。（等同于所有节点访问同一份最新的数据副本），换句话就是说，任何时刻，所用的应用程序都能访问得到相同的数据。
- 可用性（A）：在集群中一部分节点故障后，集群整体是否还能响应客户端的读写请求。（对数据更新具备高可用性），换句话就是说，任何时候，任何应用程序都可以读写数据。
- 分区容错性（P）：以实际效果而言，分区相当于对通信的时限要求。系统如果不能在时限内达成数据一致性，就意味着发生了分区的情况，必须就当前操作在C和A之间做出选择，换句话说，系统可以跨网络分区线性的伸缩和扩展。

要满足P，就是允许网络通信可能失败，那么在多个副本之间的同步就可能存在失败，那么某个副本就可能存在过期的数据。所以当用户访问这个副本时，系统有两种选择：
1. 为了满足强一致性，就一直同步，直到这个副本也得到了最新数据。但是由于通信可能失败，这个同步时间无法满足不超过timeout。即取C舍A。
2. 保证在timeout内返回结果，那么最坏情况下只能得到过期数据，即得不到最新数据，没有满足所有副本都得到最新数据（强一致性）。即取A舍C。

以上两种情况的“舍”都是最坏情况的。没有绝对，只有相对。重点是同步时间和timeout的权衡，如果网络故障率保证能在timeout内完成同步，那么C和A就都满足了。


### GFS是怎么实现的？

### 什么是Raft?

### 什么是强一致性和弱一致性、最终一致性？
一致性又可以分为强一致性与弱一致性。
强一致性可以理解为在任意时刻，所有节点中的数据是一样的。同一时间点，你在节点A中获取到key1的值与在节点B中获取到key1的值应该都是一样的。
弱一致性包含很多种不同的实现，目前分布式系统中广泛实现的是最终一致性。
所谓最终一致性，就是不保证在任意时刻任意节点上的同一份数据都是相同的，但是随着时间的迁移，不同节点上的同一份数据总是在向趋同的方向变化。也可以简单的理解为在一段时间后，节点间的数据会最终达到一致状态。
对于最终一致性最好的例子就是DNS系统，由于DNS多级缓存的实现，所以修改DNS记录后不会在全球所有DNS服务节点生效，需要等待DNS服务器缓存过期后向源服务器更新新的记录才能实现。

### leader选举算法有哪些？
假设有N个process, 每个process都有个可以比较的ID，可以提出选举。

leader election算法要满足两点：
- safety: 每一个进程要么不知道结果，要么知道正确的结果（不会选错leader）。
- liveness: 选举算法总会结束，每一个进程都知道了结果。

***Ring leader election 环算法***:processes组成了一个环，第i个 process p_i 可以和 p_(i+1)modN通信。

如果进程i发现原来的leader挂了，它就会发起选举，发送一个包含自己ID a_i “Election”的信息。然后当某个进程j收到了这个信息的时候，会将这个a_i与自己的ID a_j比，如果a_i>a_j, 继续转发这条消息，如果a_i<a_j且它之前没有转发过消息,就把a_i取代掉然后把消息发送出去。如果发现收到的标识符和自己的一样，代表自己成为leader，然后把自己当选的信息发送出去。

最坏情况分析：一个进程发起选举，如果它的上一个进程具有最大标识符，则选举消息到达上一个进程需要（N—1）次传递，然后消息又要N次才能宣布它当选，最后需要N个消息告诉大家它当选了，所以需要（3N-1）个消息。最好情况就是发起选举的进程就是leader，只需要（2N）个消息。如果有多个进程同时发起选举，那么只有具有最大ID的进程会完成选举。

但是环算法实用价值很少，因为在选举过程中如果有进程崩溃，选举就无法完成，不符合liveness的要求。

***Bully Algorithm 霸道算法***:设系统是同步的，所有进程都可以互相通信。当某一进程发现leader挂掉，如果自己ID最大，就宣布自己是leader，否则向ID比自己高的进程发起选举。发起选举如果没有收到回应，就宣布自己是leader，收到了回应就等待比自己ID大的进程宣布结果。
当一个进程收到从ID比自己低的进程发来的选举消息时，就向更高的进程发起选举。

最坏时间复杂度分析：只需5个消息传递时间
1. 最小ID进程发起选举
2. 第二大ID进程回应
3. 第二大ID进程向最大ID进程发起选举
4. 最大ID进程无回应，timtout
5. 第二大ID进程宣布当选
