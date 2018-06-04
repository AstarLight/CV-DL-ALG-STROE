/*
思路1：借助哈希表
思路2：双指针法
*/
#if 0
class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        map<int,int> hash;
        vector<int> result;
        int multiple = 10000000;
        for(int i=0;i<array.size();i++)
        {
            if(hash.find(array[i])!=hash.end())
            {
                if(array[i]*(sum-array[i]) < multiple)
                {
                    result.clear();
                    multiple = array[i]*(sum-array[i]);
                    int small = min(array[i], sum-array[i]);
                    result.push_back(small);
                    result.push_back(sum-small);
                }
            }
            hash[sum-array[i]] = i;
        }      
        return result;
    }
};
#endif

class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        int i = 0;
        int j = array.size()-1;
        vector<int> res;
        while(i<j)
        {
            if(array[i]+array[j]==sum)
            {
                res.push_back(array[i]);
                res.push_back(array[j]);
                break;
            }
            while(i<j && array[i]+array[j]>sum) j--;
            while(i<j && array[i]+array[j]<sum) i++;
        }
        return res;
    }
};
