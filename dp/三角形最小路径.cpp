#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    leetcode 找零钱： 已知不同面额的钞票，求如何利用最少数量的钞票组成某个金额，求可以
    使用的最少钞票的数量，如果任意数量的已知面额钞票都无法组成该金额，则返回-1
*/

int minPathLen(const vector<vector<int> >& v)
{
    vector<vector<int> > dp(v);
    for (int i = 0; i < dp.size(); i++)
        for (int j = 0; j < dp[i].size(); j++)
            dp[i][j] = 0;

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
    vector<vector<int> > test_case1;
    for (int i = 1; i <= 5; i++)
    {
        vector<int> array1(i, 0);
        test_case1.push_back(array1);
    }
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

    assert(7 == minPathLen(test_case1));

    return 0;
}
