#include <bits/stdc++.h>

/*
 * 来源：拼多多提前批
 * 题目描述：N位手机号若有K位相同则为靓号，已知一个手机号，求改成靓号的钱最少的情况。
    1）由1改为6，或由6改为1，花5块钱；2）6位手机号允许000123；3）输出字典序最小的靓号

 *测试用例：N =6,K=5,755577 输出：4 , 777577


 * 分析：
        1.用一个origin_num数组存储原始手机号, 用一个zero_num记录前置０的数量
        2.用一个cost[10]来记录修改对应数字的代价，定义一个vector<string>来记录变化后的号码
        4.遍历nzero_num数组，当前元素为d,假设要修改的元素就是d，再起一层遍历，计算abs(nzero_num[i]-d),
        这是对于数字d变成靓号的cost。在遍历求cost的期间我们需要建立一个临时的vector　m_cost(nzero_num.size())来记录个元素变成
        d的cost。记录要修改的元素个数t
        5.遍历m_cost求最小的t个值，并将修改后的靓号记录下来于vector<string>,将总cost记录在cost数组内
        6.遍历cost数组，找出cost最小那个改变方式，输出

 *
 * */

using namespace std;

int main()
{


    return 0;
}
