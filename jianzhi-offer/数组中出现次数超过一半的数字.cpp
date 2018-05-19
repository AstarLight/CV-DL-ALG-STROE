/*
    法一：借助哈希表记录,时间复杂度O(n)，空间复杂度O(n)
    法二：加减相消法,遍历数组，相同元素就加一，不同就减一，如果遇到计数器为０，
    那就更新结果元素。最后需要检查得到的结果元素个数是否大于总数的一半。
    法三：快排Partition策略
*/
#if 0
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        map<int,int> m_map;
        for(int i=0;i<numbers.size();i++)
        {
            m_map[numbers[i]]+=1;
            if(m_map[numbers[i]] > numbers.size()/2)
                return numbers[i];
        }
        
        return 0;
    }
};


class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int result = numbers[0];
        int count = 1;
        for(int i=1;i<numbers.size();i++)
        {
            if(count == 0)
            {
                result = numbers[i];
                count = 1;
            }
            
            if(numbers[i] == result)
                count++;
            else
                count--;
        }
        return isMoreThanHalf(numbers,result)?result:0;
    }
private:
    bool isMoreThanHalf(const vector<int>& numbers, int target)
    {
        int times = 0;
        for(int i=0;i<numbers.size();i++)
        {
            if(numbers[i] == target)
                times++;
        }
        
        return times>numbers.size()/2?true:false;
    }
};

#endif

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int start = 0;
        int end = numbers.size()-1;
        int mid = (start+end)/2;
        int index = Partition(numbers,start,end);
        while(index != mid)
        {
            if(index > mid)
            {
                end = index -1;
                index = Partition(numbers,start,end);
            }
            else
            {
                start = index + 1;
                index = Partition(numbers,start,end);
            }
        }
        int result = numbers[mid];
        return isMoreThanHalf(numbers,result)?result:0;
    }
    
private: 
    int Partition(vector<int>& numbers, int low, int high)
    {
        int privot = numbers[low];
        while(low < high)
        {
            while(low<high && numbers[high]>=privot)
                high--;
            numbers[low] = numbers[high];
            while(low<high && numbers[low]<=privot)
                low++;
            numbers[high] = numbers[low];
        }
        numbers[low] = privot;
        return low;
    }
    
    bool isMoreThanHalf(const vector<int>& numbers, int target)
    {
        int times = 0;
        for(int i=0;i<numbers.size();i++)
        {
            if(numbers[i] == target)
                times++;
        }
        
        return times>numbers.size()/2?true:false;
    }
};
