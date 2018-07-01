#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    leetcode 三角形：给定一个二维数组，其保存了一个三角形，求从数字三角形顶端到底端的各数字和最小的路径之和，
    每次可以向下走相邻的两个位置。
*/

int minPathLen(const vector<vector<int> >& v)
{
    vector<int> a(v[0].size(), 0);
    printf("a size=%d\n", a.size());
    vector<vector<int> > dp(v.size(), a);
    printf("dp[0].size = %d\n", dp[0].size());
    printf("dp.size = %d\n", dp.size());

    for (int i = 0; i < dp.size(); i++)
    {
        dp[dp.size() - 1][i] = v[dp.size() - 1][i];
    }
    printf("init done!\n");
    for (int i = dp.size() - 2; i >= 0; i--)
    {
        for (int j = 0; j < dp[i].size(); j++)
        {
            printf("i = %d, j = %d\n", i, j);
            dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + v[i][j];
        }
    }

    return dp[0][0];
}

int main()
{
    vector<int> array1(5,0);
    vector<vector<int> > test_case1(5, array1);
    /*
    1
    1 1
    2 1 3
    3 3 1 4
    1 2 3 4 5
    */
    test_case1[0][0] = 1;
    test_case1[1][0] = 1;
    test_case1[1][1] = 1;
    test_case1[2][0] = 2;
    test_case1[2][1] = 1;
    test_case1[2][2] = 3;
    test_case1[3][0] = 3;
    test_case1[3][1] = 3;
    test_case1[3][2] = 1;
    test_case1[3][3] = 4;
    test_case1[4][1] = 1;
    test_case1[4][1] = 2;
    test_case1[4][2] = 3;
    test_case1[4][3] = 4;
    test_case1[4][4] = 5;

    printf("minPathLen = %d\n", minPathLen(test_case1));

    return 0;
}
