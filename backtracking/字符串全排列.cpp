#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

/*
    字符串全排列
*/

void print_result(const vector<vector<char> > &result)
{
    printf("##############################################\n");
    printf("全排列数目: %d\n", result.size());
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            printf("%c ", result[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isDuplicate(const vector<char> &arr, int k, int t)
{
    while (k < t)
    {
        if (arr[k] == arr[t])
            return false;
        k++;
    }
    return true;
}

void permutation(vector<char> &arr, int k, vector<vector<char> > &result)
{
    if (k == arr.size() - 1)
    {
        result.push_back(arr);
        return;
    }
    for (int i = k; i < arr.size(); i++)
    {
        if (!isDuplicate(arr, k, i))  //排除重复元素生成的排列
            continue;
        swap(arr[i], arr[k]);
        permutation(arr, k + 1, result);
        swap(arr[i], arr[k]);
    }
}

int main()
{
    vector<char> test_case1;
    test_case1.push_back('A');
    test_case1.push_back('B');
    test_case1.push_back('C');
    test_case1.push_back('D');

    vector<vector<char> > result1;
    permutation(test_case1,0,result1);
    print_result(result1);

    vector<char> test_case2;
    test_case2.push_back('2');
    test_case2.push_back('4');
    test_case2.push_back('1');
    test_case2.push_back('6');
    test_case2.push_back('9');

    vector<vector<char> > result2;
    permutation(test_case2, 0, result2);
    print_result(result2);

    vector<char> test_case3;
    test_case3.push_back('2');
    test_case3.push_back('4');
    test_case3.push_back('1');
    test_case3.push_back('2');

    vector<vector<char> > result3;
    permutation(test_case3, 0, result3);
    print_result(result3);

    return 0;
}
