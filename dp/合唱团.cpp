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
    vector <vector<int> > fmax(stu.size(), vector<int>(k+1, 0));
    vector <vector<int> > fmin(stu.size(), vector<int>(k+1, 0));

    for (int i = 0; i < stu.size(); i++)
    {
        fmax[i][1] = stu[i];
        fmin[i][1] = stu[i];
    }
    for (int i = 0; i < stu.size();i++)
        for (int j = 2; j <= k; j++)
            for (int m = max(0, i - d); m <= i - 1; m++)
            {
                fmax[i][j] = max(fmax[i][j], max(fmax[m][j - 1] * stu[i], fmin[m][j - 1] * stu[i]));
                fmin[i][j] = min(fmax[i][j], min(fmax[m][j - 1] * stu[i], fmin[m][j - 1] * stu[i]));
            }
    
    int max_val = fmax[k-1][k];
    for(int i=k;i<stu.size();i++)
    {
        max_val = max(max_val, fmax[i][k]);
    }
    return max_val;
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
