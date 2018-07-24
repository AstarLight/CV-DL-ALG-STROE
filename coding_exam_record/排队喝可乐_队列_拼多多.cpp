#include<bits/stdc++.h>

/*
 * 来源：拼多多提前批
 * 题目描述：ABCD　四个人排队喝可乐，喝完一个变两个，再到队尾继续排队，求第N个喝可乐的是谁?
 *
 * 样例输入：　8
 * 输出：　B
 *
 * 分析：用队列模拟拿可乐和返回队列尾部的操作，同时需要借用辅助空间哈希表来存储当前队列中同名人的数目，
 * 每次取队首的人进行取可乐操作，同时所剩的n瓶可乐减去哈希表中该名字的同名人的数目，表示一次性拿了多少。
 * 并记得更新哈希表中该名字的个数（原数目乘以2）。当n<=0时会跳出模拟，队列中的最后一个元素就是我们要求的那个人。
 *
 * */

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    queue<char> Q;
    Q.push('A');
    Q.push('B');
    Q.push('C');
    Q.push('D');
    map<char, int> M;
    M['A'] = 1;
    M['B'] = 1;
    M['C'] = 1;
    M['D'] = 1;

    while(n > 0)
    {
        char head = Q.front();
        Q.pop();
        n -= M[head];
        Q.push(head);
        M[head] *= 2;
    }
    cout<< Q.back()<<endl;

    return 0;
}
