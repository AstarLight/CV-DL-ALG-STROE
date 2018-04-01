/*
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/

/*
    动态规划，f(n) = f(n-1) + f(n-2)
*/

class Solution {
public:
    int jumpFloor(int number) {
        int f0 = 0;
        int f1 = 1;
        int fn = f0 + f1;
        for(int i=2;i<=number;i++)
        {
            f0 = f1;
            f1 = fn;
            fn = f0 + f1;
        }
        
        return fn;
    }
};
