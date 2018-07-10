#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;

/*
    LCS:最长公共子序列
*/

void print_lcs(const vector<vector<int> >& record, string s, int i, int j)
{
    if (i == 0 || j == 0)
        return;
    if (record[i][j] == 'E')
    {
        print_lcs(record, s, i - 1, j - 1);
        cout << s[i-1] << " ";
    }
    else
        if (record[i][j] == 'U')
            print_lcs(record, s, i - 1, j);
        else
            print_lcs(record, s, i, j - 1);
}

int LCS(string s1, string s2)
{
    vector<int> arr(s2.size()+1, 0);
    vector<vector<int> > dp(s1.size()+1, arr);
    vector<vector<int> > record(dp);
    for (int i = 1; i <= s1.size(); i++)
    {
        for (int j = 1; j <= s2.size(); j++)
        {
            printf("i = %d, j = %d\n", i, j);
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                record[i][j] = 'E';
            }
            else
            {
                if (dp[i - 1][j] >= dp[i][j - 1])
                {
                    dp[i][j] = dp[i - 1][j];
                    record[i][j] = 'L';
                }
                else
                {
                    dp[i][j] = dp[j][i-1];
                    record[i][j] = 'U';
                }
            }
        }
    }

    printf("LCS of %s and %s is %d\n", s1.c_str(), s2.c_str(), dp[s1.size()][s2.size()]);
    //print_lcs(record, s1, dp.size(), dp[0].size());
    return dp[s1.size()][s2.size()];
}



int main()
{
    string test_str1 = "ababbasbcsws";
    string test_str2 = "bascawsias";

    assert(6 == LCS(test_str1, test_str2));

    return 0;
}
