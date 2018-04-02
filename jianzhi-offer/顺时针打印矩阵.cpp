


/*
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下矩阵：
1 2  3  4
5 6  7  8
9 10 11 12
13 14 15 16
则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
*/

/*
    纯粹是暴力法，没有技巧可言，主要考察边界条件和重复打印问题，很难考虑完整
*/

class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<int> ret;
        int start = 0;
        while(cols > start*2 && rows > start*2)
        {
            printInCircle(matrix, cols, rows, start,ret);
            start++;
        }
        return ret;
    }
private:
    //打印一圈，顺时针
    void printInCircle(vector<vector<int> > matrix, int cols, int rows, int start, vector<int>& ret)
    {
        int end_x = cols-start-1;
        int end_y = rows-start-1;

        //从左往右打印
        for(int i=start;i<=end_x;i++)
            ret.push_back(matrix[start][i]);

        //从上往下打印
        if(start < end_y)
            for(int i=start+1;i<=end_y;i++)
                ret.push_back(matrix[i][end_x]);   

        //从右往左打印
        if(start < end_x && start < end_y)
            for(int i=end_x-1;i>=start;i--)
                ret.push_back(matrix[end_y][i]);

        //从下往上打印
        if(start <　end_x && start < end_y-1)
            for(int i=end_y-1;i>start;i--)
                ret.push_back(matrix[i][start]);
    }
};
