/*
来源：１７网易提前批
题目：牛牛拿到了一个藏宝图，顺着藏宝图的指示，牛牛发现了一个藏宝盒，藏宝盒上有一个机关，
机关每次会显示两个字符串 s 和 t，根据古老的传说，牛牛需要每次都回答 t 是否是 s 的子序列。
注意，子序列不要求在原字符串中是连续的，例如串 abc，它的子序列就有 {空串, a, b, c, ab, ac, bc, abc} 8 种。

思路：其实就是求全组合，另外用map来记录字符组合，求子序列在是源字符串的子序列，其实就是验证该子序列是否存在与
map中即可。
*/

#include <map>
#include <iostream>
#include <string>

using namespace std;

map<string, int> m;

void all_combination(string str)
{
    int nBits = 1 << str.size();
    for(int i=0;i<nBits;i++)
    {
        string tmp;
        for(int j=0;j<str.size();j++)
        {
            if(i & (1 << j))
                tmp += str[j];
        }
        if(tmp.size() != 0)
            m[tmp] = 1;
    }
}



int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    all_combination(s1);
    if(m.count(s2))
        cout<< "Yes" << endl;
    else
        cout<< "No" << endl;
    return 0;
}
