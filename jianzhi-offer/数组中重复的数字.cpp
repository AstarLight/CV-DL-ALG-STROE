/*
在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。
也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 
例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。
*/

/*
    思路１：暴力两层遍历，Ｏ(n^2)，空间复杂度Ｏ(1)
    思路２：哈希表法，空间复杂度Ｏ(n)，时间复杂度O(n)
*/
#if 0
class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        if(length == 1) return false;
        for(int i=0;i<length;i++)
        {
            for(int j=i+1;j<length;j++)
            {
                if(numbers[i] == numbers[j])
                {
                    *duplication = numbers[i];
                    return true;;
                }
            }
        }
        return false;
    }
};
#endif

class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        map<int,int> m_map;
        for(int i=0;i<length;i++)
        {
            m_map[numbers[i]] += 1;
            if(m_map[numbers[i]] == 2)
            {
                *duplication = numbers[i];
                return true;
            }
        }
        return false;
    }
};
