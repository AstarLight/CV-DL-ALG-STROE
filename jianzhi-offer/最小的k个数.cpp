/*输入n个整数，找出其中最小的K个数*/

/*
思路1：排序，缺点就是改变了原来的数组顺序，O(nlogn)
思路2：最小堆法，O(nlogk)，用set实现
思路3：Partition法，借鉴快排思路，会改变数组的顺序，O(n)
*/
#if 0
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if(k > input.size() || k == 0) return res;
        sort(input.begin(),input.end());
        for(int i=0;i<k;i++)
            res.push_back(input[i]);
        return res;
    }
};
#endif

#if 0
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        set<int> m_set;
        if(k > input.size() || k == 0) return res;
        for(int i=0;i<input.size();i++)
        {
            if(i < k) 
                m_set.insert(input[i]);
            else
            {
                set<int>::iterator it = m_set.end();
                it--;
                if(*it > input[i])
                {
                    m_set.erase(it);
                    m_set.insert(input[i]);
                }
            }
        } 
        for(set<int>::iterator iter = m_set.begin() ; iter != m_set.end() ; ++iter)
        {
            res.push_back(*iter);
        }
            
        return res;
    }
};
#endif

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        
    }
};
