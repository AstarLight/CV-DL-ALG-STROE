/*
方法一：写一个判断是否是丑数的函数，然后遍历每个数，判断是不是丑数。此方法时间复杂度过高。
方法二：开辟一个数组，因为每个丑数的2,3,5倍还是丑数，所以我们可以把它存进数组内，免除重复判断。
*/

#if 0
class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if(index <= 0)
            return 0;
        int count = 0;
        int i = 0;
        while(count < index)
        {
            i++;
            if(isUgly(i))
            {
                count++;
            }
        }
        return i;
    }
private:
    bool isUgly(int n)
    {
        while(n%2 == 0)
            n /= 2;
        while(n%3 == 0)
            n /= 3;
        while(n%5 ==0)
            n /= 5;
        return n==1?true:false;
    }
    
};
#endif
class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if(index < 7)
            return index;
        vector<int> res(index);
        res[0] = 1;
        int t2 = 0, t3 = 0, t5 = 0;
        for(int i=1;i<index;i++)
        {
            res[i] = min(res[t2]*2, min(res[t3]*3, res[t5]*5));
            if(res[i] == res[t2]*2) t2++;
            if(res[i] == res[t3]*3) t3++;
            if(res[i] == res[t5]*5) t5++;
        }
        return res[index-1];
    }
};
