
#include <bits/stdc++.h>

using namespace std;

bool isPrime(int n)
{
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n % i == 0)
            return false;
    }
    return true;
}


int main()
{
    string s;
    isPrime(97)?s="yes":s="no";
    cout<< s << endl;

    return 0;
}
