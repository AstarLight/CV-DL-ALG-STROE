#include <bits/stdc++.h>

/*
 * 来源：拼多多提前批
 * 题目描述：M 个人给 N 个球星评级，共a-z 26个级别，a最高，z最低，球星X比球星Y评级高的次数大于球星Y比球星X评级高的次数，
    则球星X强于球星Y，若有一个球星强于其他所有球星，则为球王，否则没有球王。有则返回序号，无则为-1
 *
    例子1：M=3，N=4；评价为：acbd；bacd；bdca；输出为：0
    例子2：M=3，N=3；评价为：abc；bca；cab；输出为：-1
 *
 * 分析：1.先用一个二维数组vote记录所有每个人的打分情况，横轴是第n个人的投票情况，纵轴是每个球员的得票情况
 *      2. 翻转vote数组，得到player二维数组，横轴表示每个球员的得票情况，翻转的作用在于易于处理和比较字符串
 *      3. 对player每一组排序（字典序）
 *      ４. 以第０个为起始字符串并记录为最大的字符串，一一与后面每个player的得票字符串比较，较大的player的index记录下来。
 *      ５. 遍历去重，检查当前球王候选人是否与所有球员有相同的票，有则返回-1.
 *
 * */

using namespace std;

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    vector<vector<char> > vote(m, vector<char>(n));  //记录每个投票者的投票情况
    vector<vector<char> > player(n, vector<char>(m));  //没录每个球员的得票情况
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin >> vote[i][j];
            player[j][i] = vote[i][j]; //倒置
        }
    }

    //排序
    for(int i=0;i<n;i++)
    {
        sort(player[i].begin(),player[i].end());
    }

    //比较
    vector<char> best_player = player[0];
    int index = 0;  //球王索引
    for(int i=1;i<n;i++)
    {
        if(best_player > player[i])
        {
            best_player = player[i];
            index = i;
        }
    }

    //检查重复
    for(int i=0;i<n;i++)
    {
        if(i != index && best_player == player[i])
            index = -1;
    }

    cout << index <<endl;

    return 0;
}
