#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <iostream>

using namespace std;

/*
    字符全组合
*/

void print_result(const vector<string>& res)
{
    cout << "#############################" <<endl;
    for(int i=0;i<res.size();i++)
    {
        cout<< res[i] <<endl;
    }
}

void all_combination(const vector<char>& charSet, vector<string>& res)
{
    int nBits = 1 << charSet.size();
    for(int i=0;i<nBits;i++)
    {
        string tmp;
        for(int j=0;j<charSet.size();j++)
        {
            if(i & (1<<j))
            {
                tmp += charSet[j];
            }
        }
        if(tmp.size() != 0)
            res.push_back(tmp);
    }
}

int main()
{
    vector<char> test_case1;
    test_case1.push_back('A');
    test_case1.push_back('B');
    test_case1.push_back('C');

    vector<string> result1;
    all_combination(test_case1,result1);
    print_result(result1);

    vector<char> test_case2;
    test_case2.push_back('2');
    test_case2.push_back('4');
    test_case2.push_back('1');
    test_case2.push_back('6');
    test_case2.push_back('9');

    vector<string> result2;
    all_combination(test_case2,result2);
    print_result(result2);

    vector<char> test_case3;
    test_case3.push_back('2');
    test_case3.push_back('4');
    test_case3.push_back('1');
    test_case3.push_back('2');

    vector<string> result3;
    all_combination(test_case3,result3);
    print_result(result3);

    return 0;
}
