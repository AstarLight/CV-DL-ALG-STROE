#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    leetcode 找零钱： 已知不同面额的钞票，求如何利用最少数量的钞票组成某个金额，求可以
    使用的最少钞票的数量，如果任意数量的已知面额钞票都无法组成该金额，则返回-1
*/

int coinChange(const vector<int>& v, int amount)
{
    vector<int> dp(amount+1, -1);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            if (i - v[j] >= 0 && dp[i - v[j]] != -1)
            {
                if(dp[i]==-1 || dp[i] > dp[i-v[j]] + 1)
                {
                    dp[i] = dp[i - v[j]] + 1;
                }
            }
        }
        printf("dp[%d]=%d\n", i, dp[i]);
    }
    return dp.back();
}

int main()
{
    vector<int> test_case1;
    // [1,2,5,7,10]
    test_case1.push_back(1);
    test_case1.push_back(2);
    test_case1.push_back(5);
    test_case1.push_back(7);
    test_case1.push_back(10);

    vector<int> test_case2;
    // [1,2,3,5,7,8]
    test_case2.push_back(1);
    test_case2.push_back(2);
    test_case2.push_back(3);
    test_case2.push_back(5);
    test_case2.push_back(7);
    test_case2.push_back(8);

    assert(2 == coinChange(test_case1, 14));
    assert(3 == coinChange(test_case2, 20));

    return 0;
}
