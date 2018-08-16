#include<iostream>  

using namespace std;

/*二分法，缺点是数值可能会溢出*/
double get_genhao_v1(double n)
{
    if (n < 0)
        return -1;
    double low = 0;
    double high = n;
    while (high - low > 0.0000000001)
    {
        double mid = (high + low) / 2;
        if (mid*mid > n)
            high = mid;
        else if (mid*mid < n)
            low = mid;
        else
            return mid;
    }
    return (high + low) / 2;
}

/*牛顿迭代法*/
double get_genhao_v2(double a)
{
    if (a < 0)
        return -1;
    double x1 = a;
    double x2 = a / 2;
    while (fabs(x1 - x2) > 0.00000001)
    {
        x1 = x2;
        x2 = (x1 + a / x1) / 2;     ///////迭代的核心代码
    }
    return x1;
}

int main()
{
    cout << get_genhao_v1(998.3) << endl;
    cout << get_genhao_v2(998.3) << endl;
    system("pause");

    return 0;
}
