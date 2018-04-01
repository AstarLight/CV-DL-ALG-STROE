/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。 
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
*/

/*
思路１：遍历法，O(n),缺点是没用到题目提供的有序，旋转的性质
思路二：二分查找，带了很多约束条件

采用二分法解答这个问题，
mid = low + (high - low)/2
需要考虑三种情况：
(1)array[mid] > array[high]:
出现这种情况的array类似[3,4,5,6,0,1,2]，此时最小数字一定在mid的右边。
low = mid + 1
(2)array[mid] == array[high]:
出现这种情况的array类似 [1,0,1,1,1] 或者[1,1,1,0,1]，此时最小数字不好判断在mid左边
还是右边,这时只好一个一个试 ，
high = high - 1
(3)array[mid] < array[high]:
出现这种情况的array类似[2,2,3,4,5,6,6],此时最小数字一定就是array[mid]或者在mid的左
边。因为右边必然都是递增的。
high = mid
*/

#if 0
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size() <= 0) return 0;
        
        int min_val = rotateArray[0];
        for(int i=1;i<rotateArray.size();i++)
        {
            if(min_val > rotateArray[i])
                min_val = rotateArray[i];
        }
        
        return min_val;
        
    }
};
#endif

class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) 
    {
        if(rotateArray.size() <= 0) return 0;

        int low = 0;
        int high = rotateArray.size()-1;
        while(low < high)
        {
            int mid = (low + high)/2;
            if(rotateArray[mid] > rotateArray[high])
                low = mid + 1;
            else if(rotateArray[mid] == rotateArray[high])
                high = high -1;
            else
                high = mid;
        }
        
        return rotateArray[low];
    }
};
