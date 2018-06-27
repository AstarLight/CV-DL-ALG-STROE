#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
 *  LIS:最短递增子序列
 *
 */

// O(n^2) solution, return the longest increasing string's length
int LIS1(const vector<int>& s)
{
    vector<int> dp(s.size(), 1);
    for(int i=1;i<s.size();i++)
    {
        for(int j=0;j<i;j++)
        {
            if(s[i] > s[j])
            {
                dp[i] = max(dp[j]+1, dp[i]);
            }
        }
    }

    int max_val = dp[0];
    for(int i=1;i<s.size();i++)
    {
        if(max_val < dp[i])
            swap(max_val, dp[i]);
    }

    printf("LIS 1 solution len is %d\n", max_val);
    return max_val;
}

int binSearch(const vector<int>& v, int start, int end, int target)
{
    while(start<=end)
    {
        int mid = (start+end)/2;
        if(v[mid] == target)
            return mid;
        else if(v[mid] > target)
            end = mid-1;
        else
            start = mid+1;
    }
    return start;
}

//O(nlogn) solution return the longest increasing string's length
int LIS2(const vector<int>& s)
{
    vector<int> dp(s.size(), 1);
    int len = 0;
    int pos = 0;
    for(int i=1;i<s.size();i++)
    {
        if(s[i] > dp[len-1])
        {
            dp[len] = s[i];
            ++len;
        }
        else
        {
            pos = binSearch(s, 0, i-1, s[i]);
            dp[pos] = s[i];
        }
    }
    printf("LIS 2 solution len is %d\n", len);
    return len;
}

int main()
{
    vector<int> test1, test2;
    test1.push_back(1);
    test1.push_back(1);
    test1.push_back(3);
    test1.push_back(6);
    test1.push_back(2);
    test1.push_back(9);
    test2.push_back(9);
    test2.push_back(2);
    test2.push_back(3);
    test2.push_back(4);
    test2.push_back(1);
    test2.push_back(7);
    test2.push_back(1);

    assert(4 == LIS1(test1));
    assert(4 == LIS1(test2));
    assert(4 == LIS2(test1));
    assert(4 == LIS2(test2));

    return 0;
}
