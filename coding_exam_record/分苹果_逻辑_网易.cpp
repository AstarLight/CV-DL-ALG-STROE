#include <stdio.h>
#include <vector>
#include <algorithm>


/*
来源：17网易内推

题目描述
n 只奶牛坐在一排，每个奶牛拥有 ai 个苹果，现在你要在它们之间转移苹果，
使得最后所有奶牛拥有的苹果数都相同，每一次，你只能从一只奶牛身上拿走恰好两个苹果到另一个奶牛上，
问最少需要移动多少次可以平分苹果，如果方案不存在输出 -1。

样例：
输入
4
7 15 9 5
输出
3

思路：
    1.先遍历数组，统计每个奶牛手中的苹果
    2.求平均数m，若可以整除，表示右分配方案，否则没有。
    3.遍历每个元素，比较当前元素与m得到差值，如果差值不是2的倍数，说明无论如何不存在移动方案使得
    条件成立。如果差值是2的倍数，就往后找大于平均值的元素作为填补。


*/

using namespace std;


int main()
{
    int n;
    scanf("%d", &n);
    vector<int> cow(n, 0);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cow[i]);
        sum += cow[i];
    }

    if (sum %n != 0)
    {
       printf("%d\n",-1);
        return 0;
    }

    int average = sum / n;
    int step = 0;
    for (int i = 0; i < n; i++)
    {
        int gap = cow[i] - average;
        if (gap == 0)
            continue;
        if(gap %2 != 0)
        {
            printf("%d\n",-1);
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            while (gap < 0 && cow[j] > average)
            {
                step++;
                cow[i] += 2;
                cow[j] -= 2;
                gap = cow[i] - average;
            }
        }
    }
    printf("%d\n", step);

    return 0;
}

