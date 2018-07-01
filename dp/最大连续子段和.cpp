#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    leetcode 最大连续子段和： 给定一个数组，求这个数组的连续子数组中，最大的那一段的和。
*/

int MaxContinuousSubString(const vector<int>& v)
{
    // f[n] = max(f[n-1]+a[n], a[n]) 
    vector<int> dp(v.size(), 0);
    dp[0] = v[0];
    int max_val = dp[0];
    for (int i = 1; i < v.size(); i++)
    {
        dp[i] = max(dp[i - 1] + v[i], v[i]);
        printf("dp[%d]=%d\n", i, dp[i]);
        if (max_val < dp[i])
            max_val = dp[i];
    }
    return max_val;
}

int main()
{
    vector<int> test_case1;
    // [5, 1, 2, -6, 3, 4, -9, 7]
    test_case1.push_back(5);
    test_case1.push_back(1);
    test_case1.push_back(2);
    test_case1.push_back(-6);
    test_case1.push_back(3);
    test_case1.push_back(4);
    test_case1.push_back(-9);
    test_case1.push_back(7);

    vector<int> test_case2;
    // [15, -13, 2, -16, 30, -4, 39, 27]
    test_case2.push_back(15);
    test_case2.push_back(-13);
    test_case2.push_back(2);
    test_case2.push_back(-16);
    test_case2.push_back(30);
    test_case2.push_back(-4);
    test_case2.push_back(39);
    test_case2.push_back(27);

    vector<int> test_case3;
    // [-2,1,-3,4,-1,2,1,-5,4]
    test_case3.push_back(-2);
    test_case3.push_back(1);
    test_case3.push_back(-3);
    test_case3.push_back(4);
    test_case3.push_back(-1);
    test_case3.push_back(2);
    test_case3.push_back(1);
    test_case3.push_back(-5);
    test_case3.push_back(4);

    assert(9 == MaxContinuousSubString(test_case1));
    assert(92 == MaxContinuousSubString(test_case2));
    assert(6 == MaxContinuousSubString(test_case3));

    return 0;
}
