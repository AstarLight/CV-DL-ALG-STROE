/*
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
*/

/*
    思路一是最直观右最蠢的方法，遍历＋借助多个辅助变量，时间复杂度O(n)，空间复杂度O(n)
    思路二一开始想到的是双指针法，同时指向数组前后，并向中间移动。并按照题目的意思依次交换两个数，但是
    奇数和奇数，偶数和偶数之间的相对位置会变，所以要用插入排序。所以还是用尾插法吧，直接把偶数从里面删除然后尾插就行
*/

#if 0
class Solution {
public:
    void reOrderArray(vector<int> &array) {
        vector<int> odd;
        vector<int> even;
        for(int i=0;i<array.size();i++)
        {
            if(array[i]%2 == 0) //偶数
                even.push_back(array[i]);
            else
                odd.push_back(array[i]);
        }
        int even_count = 0;
        for(int i=0;i<array.size();i++)
        {
            if(i < odd.size())
                array[i] = odd[i];
            else
                array[i] = even[even_count++];
        }
    }
};
#endif

class Solution {
public:
    void reOrderArray(vector<int> &array) {
        vector<int>::iterator it = array.begin();
        int m_size = array.size();
        while(m_size)
        {
            if(*it%2 == 0)
            {
                int tmp = *it;
                it = array.erase(it);  //记得是先erase再pushback，否则会迭代器去失效（扩容）造成编译不过
                array.push_back(tmp);
            }
            else
                it++;
            
            m_size--;
        }
    }
};
