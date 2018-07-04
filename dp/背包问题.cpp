#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    01背包，完全背包，多重背包
*/

// 01背包解决方案(二维数组解法)
int knapsack01_1(const vector<int>& v, const vector<int>& w, int V)
{
    vector<int> arr(V+1, 0);
    vector<vector<int> > dp(v.size()+1, arr);

    // f[i][j] = max(f[i-1][j], f[i-1][j-w[i]]+v[i])
    for (int i = 1; i <= v.size(); i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (j < w[i-1])  //该物品装不进去
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i-1]] + v[i-1]);
            }
            printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
        }
    }
    printf("max profit is %d\n", dp[dp.size() - 1][dp[0].size() - 1]);
    return dp[dp.size()-1][dp[0].size()-1];
}

// 完全背包解决方案（二维数组）
int knapsackCompleted_1(const vector<int>& v, const vector<int>& w, int V)
{
    vector<int> arr(V + 1, 0);
    vector<vector<int> > dp(v.size() + 1, arr);

    // f[i][j] = max(f[i-1][j], f[i-1][j-k*w[i]]+k*v[i])
    for (int i = 1; i <= v.size(); i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (j < w[i - 1])  //该物品装不进去
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                for (int k = 0; k <= j / w[i - 1]; k++)
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - k*w[i - 1]] + k*v[i - 1]);
                }
            }
            printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
        }
    }
    printf("max profit is %d\n", dp[dp.size() - 1][dp[0].size() - 1]);
    return dp[dp.size() - 1][dp[0].size() - 1];
}


// 多重背包解决方案(二维数组解决方案)
int knapsackMulti_1(const vector<int>& v, const vector<int>& w, const vector<int>& n, int V)
{
    vector<int> arr(V + 1, 0);
    vector<vector<int> > dp(v.size() + 1, arr);

    // f[i][j] = max(f[i-1][j], f[i-1][j-k*w[i]]+k*v[i])
    for (int i = 1; i <= v.size(); i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (j < w[i - 1])  //该物品装不进去
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                int end = min(j / w[i - 1], n[i-1]);
                for (int k = 0; k <= end; k++)
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - k*w[i - 1]] + k*v[i - 1]);
                }
            }
            printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
        }
    }
    printf("max profit is %d\n", dp[dp.size() - 1][dp[0].size() - 1]);
    return dp[dp.size() - 1][dp[0].size() - 1];
}


// 01背包解决方案(一维数组解法)
int knapsack01_2(const vector<int>& v, const vector<int>& w, int V)
{
    vector<int> dp(V + 1, 0);

    // f[j] = max(f[j], f[j-w[i]]+v[i])
    for (int i = 1; i <= v.size(); i++)
    {
        for (int j = V; j >= 0; j--)
        {
            if (j < w[i - 1])  //该物品装不进去
            {
                dp[j] = dp[j];
            }
            else
            {
                dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
            }
            printf("dp[%d] = %d\n",j, dp[j]);
        }
    }
    printf("max profit is %d\n", dp[dp.size() - 1]);
    return dp[dp.size() - 1];
}

// 完全背包解决方案（一维数组）
int knapsackCompleted_2(const vector<int>& v, const vector<int>& w, int V)
{
    vector<int> dp(V + 1, 0);

    for (int i = 1; i <= v.size(); i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (j < w[i - 1])  //该物品装不进去
            {
                dp[j] = dp[j];
            }
            else
            {
                dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
            }
            printf("dp[%d] = %d\n",j, dp[j]);
        }
    }
    printf("max profit is %d\n", dp[dp.size() - 1]);
    return dp[dp.size() - 1];
}


// 多重背包解决方案(一维数组解决方案)
int knapsackMulti_2(const vector<int>& v, const vector<int>& w, const vector<int>& n, int V)
{
    vector<int> dp(V + 1, 0);

    for (int i = 1; i <= v.size(); i++)
    {
        for (int j = V; j >= 1; j--)
        {
            if (j < w[i - 1])  //该物品装不进去
            {
                dp[j] = dp[j];
            }
            else
            {
                  dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
            }
            printf("dp[%d] = %d\n", j, dp[j]);
        }
    }
    printf("max profit is %d\n", dp[dp.size() - 1]);
    return dp[dp.size() - 1];
}

int main()
{
    vector<int> test1_val;
    vector<int> test1_wei;
    vector<int> test1_num;
    test1_val.push_back(10);
    test1_val.push_back(40);
    test1_val.push_back(30);
    test1_val.push_back(50);

    test1_wei.push_back(5);
    test1_wei.push_back(4);
    test1_wei.push_back(6);
    test1_wei.push_back(3);

    test1_num.push_back(1);
    test1_num.push_back(2);
    test1_num.push_back(3);
    test1_num.push_back(1);

    assert(90 == knapsack01_1(test1_val, test1_wei, 10));
    assert(90 == knapsack01_2(test1_val, test1_wei, 10));
    assert(150 == knapsackCompleted_1(test1_val, test1_wei, 10));
    assert(150 == knapsackCompleted_2(test1_val, test1_wei, 10));
    assert(90 == knapsackMulti_1(test1_val, test1_wei, test1_num, 10));
    assert(90 == knapsackMulti_2(test1_val, test1_wei, test1_num, 10));

    vector<int> test2_val;
    vector<int> test2_wei;
    vector<int> test2_num;
    test2_val.push_back(3);
    test2_val.push_back(4);
    test2_val.push_back(5);
    test2_val.push_back(6);
    test2_val.push_back(7);

    test2_wei.push_back(2);
    test2_wei.push_back(3);
    test2_wei.push_back(4);
    test2_wei.push_back(5);
    test2_wei.push_back(6);

    test2_num.push_back(1);
    test2_num.push_back(2);
    test2_num.push_back(2);
    test2_num.push_back(3);
    test2_num.push_back(1);

    assert(13 == knapsack01_1(test2_val, test2_wei, 10));
    assert(13 == knapsack01_2(test2_val, test2_wei, 10));
    assert(15 == knapsackCompleted_1(test2_val, test2_wei, 10));
    assert(15 == knapsackCompleted_2(test2_val, test2_wei, 10));
    assert(13 == knapsackMulti_1(test2_val, test2_wei, test2_num, 10));
    assert(13 == knapsackMulti_2(test2_val, test2_wei, test2_num, 10));

    return 0;
}
