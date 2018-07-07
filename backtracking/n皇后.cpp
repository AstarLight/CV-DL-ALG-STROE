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

// 判断该位置能不能放置皇后
/*
把棋盘存储为一个N维数组a[N]，数组中第i个元素的值代表第i行的皇后位置，
这样便可以把问题的空间规模压缩为一维O(N)，在判断是否冲突时也很简单，
首先每行只有一个皇后，且在数组中只占据一个元素的位置，行冲突就不存在了，
其次是列冲突，判断一下是否有a[i]与当前要放置皇后的列j相等即可。
至于斜线冲突，通过观察可以发现所有在斜线上冲突的皇后的位置都有规律即它们所在的行列互减的绝对值相等，
即| row – i | = | col – a[i] | 。这样某个位置是否可以放置皇后的问题已经解决。
*/
bool canPut(int k, const vector<int>& v)
{
    for (int i = 0; i < k; i++)
    {
        // 列和对角线冲突判断
        if (v[i] == v[k] || abs(v[i] - v[k]) == (k - i))
            return false;
    }
    return true;
}

// k代表当前已经放了k个皇后了
void put(int n, int k, vector<int>& v, int &count)
{
    for (int i = 0; i < n; i++)
    {
        v[k] = i; /* 将皇后摆到第K行第i列的位置 */
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
}

int NQueen(int n)  //n代表一共n个皇后
{
    vector<int> chessboard(n, 0);  //(i,chessboard[i])表示棋盘的在该坐标下可以放下皇后
    int count = 0;
    put(n, 0, chessboard, count);
    return count;
}


int main()
{
    const int n = 10;
    printf("%d-Queen problem has %d solutions.\n",n, NQueen(n));

    return 0;
}
