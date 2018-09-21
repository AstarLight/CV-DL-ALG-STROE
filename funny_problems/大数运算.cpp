/*
 * 大数加法，支持正数＋正数，负数＋负数
 * 大数减法，支持大数减小数，也支持小数减大数
 * 大数乘法，支持正负数相乘
 * */

#include<string>
#include<vector>
#include <iostream>

#define MAX 1000    // 大数的最大位数

using namespace std;

void add(string num1,string num2, string& sum)
{
    int i, j;
    int a[MAX+10] = {0};
    int b[MAX+10] = {0};
    int c[MAX+10] = {0};
    int num1_sign = 0;
    int num2_sign = 0;

    for(j=0,i=num1.size()-1;i>=0;i--)
    {
        if(num1[i] == '-')  //跳过负号
        {
            num1_sign = 1;
            continue;
        }
        a[j++] = num1[i]-'0';
    }

    for(j = 0, i = num2.size()-1; i >= 0; i--)
    {
        if(num2[i] == '-')  //跳过负号
        {
            num2_sign = 1;
            continue;
        }
        b[j++] = num2[i]-'0';
    }

    int carry = 0;
    for(i=0;i<MAX;i++)
    {
        int total = a[i] + b[i] + carry;
        c[i] += total % 10;
        carry = total/10;
    }

    for(i = MAX+10-1; c[i]==0 && i>=0; i--); //跳过高位的0

    for(; i>=0; i--)
        sum+=(c[i]+'0');

    if(num1_sign && num2_sign)
    {
        sum = '-' + sum;
    }
}

void mul(string num1,string num2, string& sum)
{
    int i, j, len, len1, len2;
    int a[MAX+10] = {0};
    int b[MAX+10] = {0};
    int c[MAX*2+10] = {0};

    int num1_sign = 0;
    int num2_sign = 0;

    len1 = num1.size();
    for(j = 0, i = len1-1; i >= 0; i--) //把数字字符转换为整型数，逆序存储
    {
        if(num1[i] == '-')  //跳过负号
        {
            num1_sign = 1;
            continue;
        }
        a[j++] = num1[i]-'0';
    }

    len2 = num2.size();
    for(j = 0, i = len2-1; i >= 0; i--)
    {
        if(num2[i] == '-')  //跳过负号
        {
            num2_sign = 1;
            continue;
        }
        b[j++] = num2[i]-'0';
    }

    for(i = 0; i < len2; i++)//用第二个数乘以第一个数,每次一位
    {
        for(j = 0; j < len1; j++)
        {
            c[i+j] += b[i] * a[j]; //先乘起来,后面统一进位
        }
    }

    for(i=0; i<MAX*2; i++) //循环统一处理进位问题
    {
        if(c[i]>=10)
        {
            c[i+1]+=c[i]/10;
            c[i]%=10;
        }
    }

    for(i = MAX*2; c[i]==0 && i>=0; i--); //跳过高位的0

    for(; i>=0; i--)
        sum+=(c[i]+'0');

    if(num1_sign ^ num2_sign)
    {
        sum = '-' + sum;
    }

}

int main()
{
    int i, len;
    vector<char> num1;
    vector<char> num2;
    string add_sum, mul_sum;
    string s1, s2;
    cin >> s1;
    cin >> s2;

    mul(s1, s2, mul_sum);
    add(s1, s2, add_sum);

    cout << "add sum = " << add_sum << endl;
    cout << "mul sum = " << mul_sum << endl;

    return 0;
}
