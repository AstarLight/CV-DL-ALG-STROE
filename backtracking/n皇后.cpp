#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    N皇后回溯解法
*/

void show(int n, const vector<int>& v)
{
    vector<int> arr(n, 0);
    vector<vector<int> > chessboard(n,arr);
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            if (j == v[i])
                printf("Q ");
            else
                printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}

bool canPut(int n, const vector<int>& v)
{
    for (int i = 0; i < n; i++)
    {
        if (v[i] == v[n] || abs(v[i] - v[n]) == (n - i))
            return false;
    }
    return true;
}

int put(int n, int k, vector<int>& v, int &count)
{
    for (int i = 0; i < n; i++)
    {
        v[k] = i; /* 将皇后摆到当前循环到的位置 */
        if (canPut(k, v))
        {
            if (k == n - 1)  //碰到棋盘底部了
            {
                count++;
                show(n, v); /* 如果全部摆好，则输出所有皇后的坐标 */
            }
            else
            {
                put(n, k+1, v, count); /* 否则继续摆放下一个皇后 */
            }
        }
    }
    return 0;
}

int NQueen(int n)  //n代表一共n个皇后
{
    vector<int> chessboard(n, 0);
    int count = 0;
    put(n, 0, chessboard, count);
    return count;
}


int main()
{
    printf("N Queen solution is %d\n",NQueen(8));

    return 0;
}
