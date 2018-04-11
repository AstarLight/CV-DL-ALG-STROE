#include <stdio.h>
#include <vector>
#include <math.h>
#include<stdlib.h>


using namespace std;

float GetRandomMoney(float total_money, int package_num);
vector<float> AllocateRedPackage(float total_money, int package_num);

int main()
{
    vector<float> random_packages;
    random_packages = AllocateRedPackage(100.0, 10);

    for(int i=0;i<random_packages.size();i++)
    {
        printf("%.1f ", random_packages[i]);
    }
    printf("\n");

    return  0;
}

vector<float> AllocateRedPackage(float total_money, int package_num)
{
    vector<float> ret;
    while(total_money && package_num)
    {
        float random_money = GetRandomMoney(total_money, package_num);
        ret.push_back(random_money);
        total_money -= random_money;
        package_num--;
    }
    return ret;
}


float GetRandomMoney(const float total_money, const int package_num)
{
    if(package_num == 1)
    {
        return (float)round(total_money*10)/10;
    }

    float r = (float)(rand() % 10) / 10;
    float min = 0.1;
    float max = total_money / package_num * 2;  //额度在0.01和剩余平均值*2之间
    float money = r * max;
    money = money<=min?min:money;
    money = money * 10 / 10;
    return money;
}
