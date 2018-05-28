/*
维护一个数组，如果当前数组里面的元素的和大于sum，则去除数组的排第一的元素，如果小于则
去除将新元素加入数组内。若等于则将当前数组的元素存入结果数组。在遍历数组时需要维护small
和big两个指针。
*/

class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> > res;
        int small = 1;
        int big = 2;
        vector<int> vec;
        vec.push_back(small);
        int m_sum = small+big;
        while(small < big && big <= sum)
        {
            if(m_sum == sum)
            {
                vec.push_back(big);
                res.push_back(vec);
                big++;
                m_sum += big; 
            }
            else if(m_sum > sum)
            {
                vec.erase(vec.begin());
                m_sum -= small;
                small++;
            }
            else
            {
                vec.push_back(big);
                big++;
                m_sum += big; 
            }
        }
        return res;
    }
};
