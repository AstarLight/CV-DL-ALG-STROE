/*
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
*/

/*
思路：先把二维数组index定为最左上角点（列数最大，行数为0），然后以以下规则改变i,j：
    如果target值比array[i][j]大，那么我们就认为target不可能在该行上，我们i++，换行；
    如果target值比array[i][j]大，那么我们就认为target不可能在该列上，我们j--，换列；
    如果target值等于array[i][j]，那么值找到了。
    注意循环跳出条件：j要>=0，i要<=max_cols
*/

class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int max_cols = array[0].size()-1;  //最大列数
        int max_rows = array.size()-1; //最大行数
        int i = 0;
        int j = max_cols;
        while(i<=max_rows && j>=0)
        {
            if(target > array[i][j])
                i++;
            else if(target < array[i][j])
                j--;
            else  // ==
                return true;  // find it!
        }
        return false;
    }
};
