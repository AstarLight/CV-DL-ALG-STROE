/*
    思路一：暴力遍历法，时间复杂度为O(mn),m是数组长度，n是滑动窗口长度
    思路二：维护一个双端队列，一次遍历，时间复杂度O(m)
*/
#if 0
class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> res;
        if(num.size() <= 0 || size > num.size() || size <=0)
            return res;
        for(unsigned int i=0;i<num.size();i++)
        {
            if(i+size <= num.size())
            {
                unsigned int end = i+size;
                vector<int> tmp;
                for(unsigned int j = i;j<end;j++)
                {
                    tmp.push_back(num[j]);
                }
                int max_val =  *max_element(tmp.begin(),tmp.end());  
                res.push_back(max_val);
            }
        }
        return res;
    }
};
#endif

class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> res;
        if(num.size() <= 0 || size > num.size() || size <=0)
            return res;
        deque<int> dq;
        for(unsigned int i=0;i<num.size();i++)
        {
            if(!dq.empty())
            {
                // 如果队列头元素不在滑动窗口中了，就删除头元素
                if(dq.front()+size <= i)
                    dq.pop_front();
                //如果当前数字大于队列尾，则删除队列尾，直到当前数字小于等于队列尾，或者队列空
                while(!dq.empty() && num[dq.back()]<=num[i])
                    dq.pop_back();
            }
                dq.push_back(i);
                // 滑动窗口经过三个元素，获取当前的最大值，也就是队列的头元素
                if(i+1 >= size)
                    res.push_back(num[dq.front()]);
        }
        return res;
    }
};
