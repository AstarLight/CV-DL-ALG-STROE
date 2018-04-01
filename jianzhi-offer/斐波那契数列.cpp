/*
大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。
n<=39
*/

/*
    递推式：f(n) = f(n-1) + f(n-2)   f(0)=0  f(1)=1
    思路一：迭代求解，美其名曰动态规划
    思路二：递归求解
*/

#if 0
class Solution {
public:
    int Fibonacci(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        int f0 = 0;
        int f1 = 0;
        int fn = 1;
        for(int i=2;i<=n;i++)
        {
            f0 = f1;
            f1 = fn;
            fn = f0 + f1;
        }            
        return fn;
    }
};
#endif

class Solution {
public:
    int Fibonacci(int n) {
        if(n<=0) 
            return 0;
        else if(n == 1)
            return 1;
        else
            return Fibonacci(n-1) + Fibonacci(n-2);
    }
};
