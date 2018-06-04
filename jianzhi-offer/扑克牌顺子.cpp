/*
思路：先排序，第一遍遍历统计零的个数，第二次遍历统计两数之间的间隔总数，
最后比较总间隔数和零的个数
*/

class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        if(numbers.size() <= 0)
            return false;
        sort(numbers.begin(),numbers.end());
        int king_count = 0;
        int discontinue_count = 0;
        
        for(int i=0;i<numbers.size();i++)
        {
            if(numbers[i] == 0)
            {
                king_count++;
            }
        }
        if(king_count >= 4)
            return true;
        
        for(int i=king_count+1;i<numbers.size();i++)
        {
            int gap = numbers[i]-numbers[i-1];
            if(gap > 1)
                discontinue_count += gap-1;
        }
        return (king_count == discontinue_count)?true:false;
    }
};
