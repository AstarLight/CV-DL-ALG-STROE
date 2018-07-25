#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
* 来源：拼多多提前批
* 题目描述：N位手机号若有K位相同则为靓号，已知一个手机号，求改成靓号的钱最少的情况。
1）由1改为6，或由6改为1，花5块钱；2）6位手机号允许000123；3）输出字典序最小的靓号
*测试用例：N =6,K=5, 755577 输出：4 , 55557
* 分析：
1.用一个nzero_num数组存储去掉前置０的原始手机号, 用一个zero_num记录前置０的数量
2.用一个cost[10]来记录修改对应数字的代价，定义一个vector<int> res来记录变化后的号码
4.遍历nzero_num数组，当前元素为d,假设要修改的元素就是d，再起一层遍历，计算abs(nzero_num[i]-d),
这是对于数字d变成靓号的cost。在遍历求cost的期间我们需要建立一个临时的vector　m_cost(nzero_num.size())来记录个元素变成
d的cost。
5.对m_cost排序，遍历m_cost求最小的t个值，并将修改后的靓号记录下来于vector<string>,将总cost记录在cost数组内
6.遍历cost数组，找出cost最小那个改变方式，先输出前置０再输出对应的代价最小数组
*
* */

using namespace std;

struct node
{
    int index;
    int value;
};

bool cmp(node x, node y)
{
    return x.value < y.value;
}


int main()
{
    int front_zero_num = 0; //记录前置零的个数
    bool front_zero_flag = true;
    int n, k;
    string s;
    scanf("%d %d", &n, &k);
    cin >> s;
    vector<int> nzero_num;
    for (int i = 0; i < s.size(); i++)
    {
        int tmp = s[i] - '0';
        if (tmp != 0)
        {
            front_zero_flag = false;
        }
        if (front_zero_flag && tmp == 0)
        {
            front_zero_num++;
            continue;
        }
        nzero_num.push_back(tmp);
    }

    printf("loading input data done!\n");
    vector<int> cost(nzero_num.size(), 0);
    vector<vector<int> > res(nzero_num.size(), vector<int> (nzero_num.size()));

    for (int i = 0; i < nzero_num.size(); i++)
    {
        vector<node> m_cost(nzero_num.size());
        int count = 1;
        for (int j = 0; j < nzero_num.size(); j++)
        {
            if (i == j)
            {
                m_cost[j].index = j;
                m_cost[j].value = 100000;
                continue;
            }

            if (count == k)
                break;

            m_cost[j].index = j;
            m_cost[j].value = abs(nzero_num[i] - nzero_num[j]);
            count++;
        }

        sort(m_cost.begin(), m_cost.end(), cmp);  //从小到大
        vector<int> m_change_num(nzero_num);
        int m_sum = 0;
        for (int t = 0; t < nzero_num.size(); t++)
        {
            if (t == k)
                break;
            m_sum += m_cost[t].value;
            m_change_num[m_cost[t].index] = nzero_num[i];
        }
        res[i] = m_change_num;
        cost[i] = m_sum;
    }

    printf("building cost vector done!\n");
    // selcet min-cost good number
    int min_cost = cost[0];
    int min_id = 0;
    for (int i = 1; i < cost.size(); i++)
    {
        //　既要比较改变的代价，又要比较字典序
        if (min_cost > cost[i] || (min_cost == cost[i] && res[min_id] > res[i]))
        {
            min_id = i;
            min_cost = cost[i];
        }
    }

    //print final result
    printf("%d\n", min_cost);
    for (int i = 0; i < front_zero_num; i++)
        printf("%d", 0);
    for (int i = 0; i < nzero_num.size(); i++)
        printf("%d", res[min_id][i]);
    printf("\n");

    return 0;
}
