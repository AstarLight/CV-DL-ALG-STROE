#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    leetcode 盗贼问题：n个房间，每个房间都有数量不等的珠宝，有一个盗贼详尽房子盗取钱财，
    由于房间有报警器，如果同时从相邻的两个房间盗取珠宝就会触发警报，请问在不触发警报的
    条件下，最多可以获取多少珠宝？
*/

int MaxTheftMoney(const vector<int>& v)
{
    // key: dp[i] = max(dp[i - 2] + v[i], dp[i-1]);
    vector<int> dp(v.size(), 0);
    dp[0] = v[0];
    dp[1] = max(v[0],v[1]);
    for (int i = 2; i < v.size(); i++)
    {
        dp[i] = max(dp[i - 2] + v[i], dp[i-1]);
        printf("dp[%d]=%d\n", i, dp[i]);
    }
    return dp.back();
}

int main()
{
    vector<int> test_case1;
    // [5, 1, 2, 6, 3, 4, 9, 7]
    // 5 6 4 7 = 22
    test_case1.push_back(5);
    test_case1.push_back(1);
    test_case1.push_back(2);
    test_case1.push_back(6);
    test_case1.push_back(3);
    test_case1.push_back(4);
    test_case1.push_back(9);
    test_case1.push_back(7);

    vector<int> test_case2;
    // [15, 13, 2, 16, 30, 4, 39, 27]
    test_case2.push_back(15);
    test_case2.push_back(13);
    test_case2.push_back(2);
    test_case2.push_back(16);
    test_case2.push_back(30);
    test_case2.push_back(4);
    test_case2.push_back(39);
    test_case2.push_back(27);

    vector<int> test_case3;
    // [5, 2, 6, 3, 1, 7]
    test_case3.push_back(5);
    test_case3.push_back(2);
    test_case3.push_back(6);
    test_case3.push_back(3);
    test_case3.push_back(1);
    test_case3.push_back(7);

    assert(22 == MaxTheftMoney(test_case1));
    assert(86 == MaxTheftMoney(test_case2));
    assert(18 == MaxTheftMoney(test_case3));

    return 0;
}
