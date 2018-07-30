
/*
来源：１７网易内推
题目：牛牛想尝试一些新的料理，每个料理需要一些不同的材料，问完成所有的料理需要准备多少种不同的材料。

样例：
输入
BUTTER FLOUR
HONEY FLOUR EGG
输出
4


*/

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string str;
    map<string,int> m;
    while(cin >> str)
    {
        m[str] = 1;
    }
    cout << m.size() << endl;
    return 0;
}
