/*
方法一：开辟一个数组存储候选最大值。遍历数组，检查当前元素与前面元素之和是否比当前元素小，若是就更新sum值为当前元素的值，
反之则更新sum为前面元素之和+当前元素。最终得到取得一个记录着所有元素大小的数组，这个数组的元素
最大值就是向量中连续值之和。

方法二：动态规划。sum(n) = sum(i-1) + data(i)
*/
#if 0
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        vector<int> candidate;
        int sum = array[0];
        candidate.push_back(sum);
        for(int i=1;i<array.size();i++)
        {
            if(sum+array[i] < array[i])
            {
                sum = array[i];
            }
            else
            {
                sum += array[i];
            }
            candidate.push_back(sum);
        }
        
        int max_value = candidate[0];
        for(int i=1;i<candidate.size();i++)
        {
            if(max_value < candidate[i])
                max_value = candidate[i];
        }
        
        return max_value;
    }
};
#endif

class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        vector<int> sum;
        sum.push_back(array[0]);
        for(int i=1;i<array.size();i++)
        {
            if(sum[i-1] > 0)
            {
                sum.push_back(sum[i-1]+array[i]);
            }
            else{
                sum.push_back(array[i]);
            }
        }
        
        int max_value = sum[0];
        for(int i=1;i<sum.size();i++)
        {
            if(max_value < sum[i])
                max_value = sum[i];
        }
        return max_value;
    }
};
