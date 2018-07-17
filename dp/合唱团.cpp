/*
有 n 个学生站成一排，每个学生有一个能力值，牛牛想从这 n 个学生中按照顺序选取 k 名学生，
要求相邻两个学生的位置编号的差不超过 d，使得这 k 个学生的能力值的乘积最大，你能返回最大的乘积吗？

*/



#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int getMaxValue(const vector<int> &stu, int k, int d)
{
    vector<int> dp(k+1, 0);
    vector <vector<int> > fmax(d+1, dp);
    vector <vector<int> > fmin(d+1, dp);
    int res = INT_MIN;;
    for (int i = 1; i <= stu.size(); i++)
    {
        fmax[1][i] = stu[i];
        fmin[1][i] = stu[i];
        for (int m = 2; m <= k; m++)
            for (int j = i - 1; j>0 && i - j <= d; j--)
            {
                fmax[m][i] = max(fmax[m][i], max(fmax[m][j - 1] * stu[i], fmin[m][j - 1] * stu[i]));
                fmin[m][i] = min(fmax[m][i], min(fmax[m][j - 1] * stu[i], fmin[m][j - 1] * stu[i]));
            }
        res = max(res, fmax[k][i]);
    }
    return res;
}

int main()
{
    vector<int> stu;
    int n;
    scanf("%d", &n);
    for (int i = 0; i<n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        stu.push_back(tmp);
    }
    int k, d;
    scanf("%d %d", &k, &d);

    printf("%d\n", getMaxValue(stu, k, d));

    return 0;
}
