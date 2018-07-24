#include <bits/stdc++.h>

/*
 * 来源：拼多多提前批
 * 题目描述：有一批货物重量为W1,W2,W3.....，其中100<=Wi<=300,用核载300的货车拉最少需要多少次
 *测试用例：
 *  4
    130 140 150 160
    2

    7
    130 140 150 160 100 100 100
    3

    9
    100 100 100 100 100 100 200 200 200
    4

 * 分析：
贪心策略：
step1:将货物按重量从小到大排序，将重量大于200的直接装箱
step2:设置左右两个区间游标left和right，接着考虑到100+200这种临界情形，
      先将right左移到第一个小于200的下标处，将left右移到第一个大于100的下标处，
      将left~right区间内的货物首尾匹配，如果<=300就装箱，并mark这两个位置已经访问过，
      如果大于300就不装箱(right这个位置的货物也不装)将right左移一个位置继续匹配直到left == right
step3:在step2的基础上再将100和200重的货物加进来，并将left置0，right置为最后一个货重<=200的货物下标处，
      首尾匹配，先检验left和right这两个货物是否已mark过，如果mark了就left++或者right--，若都未被标记，
      当right处货重为100则直接将区间剩余货物一次性3箱这样带走，当right处货重>100时且和重<=300则
      将left和right处的货物一块装箱带走同时缩进left和right，>300则只能将right处货物装箱带走并缩进right
tips:比较关键的一个点就是100+200这种临界情况要考虑清楚，还有容易疏忽的就是区间内剩下货物全是100的时候就不能
      再首尾匹配了而应该3箱3箱这样子装箱带走
 *
 * */

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> w(n);
    vector<int> mark(n, 0);  //标记该货物有没有被运输走
    for(int i=0;i<n;i++)
    {
        scanf("%d", &w[i]);
    }

    //1. 货物按重量从小到大排序，将重量大于200的直接装箱
    sort(w.begin(), w.end());
    int left = 0;
    int right = n-1;
    int car_num = 0;  // 记录当前已使用几辆货车
    while(right>=0 && w[right] > 200)
    {
        car_num++;
        right--;
    }

    //2. 保存第一个<=200的下标,移动left和right让他们指向非100和200的位置
    int first_right = right;
    while(right>=0 && w[right]==200)
    {
        right--;
    }
    while(left<n && w[left]==100)
    {
        left++;
    }

    //3. 处理100 < w <200的货物
    while(left < right)
    {
        if(w[left]+w[right] <= 300)
        {
            car_num++;
            mark[left] = 1;
            mark[right] = 1;
            left++;
            right--;
        }
        else
        {
            right--;

        }
    }
    cout<< car_num <<endl;
    // 4. 处理100, 200货物
    right = first_right;
    left = 0;
    while(left<=right)
    {
        if(mark[left])
            left++;
        else if(mark[right])
            right--;
        else if(left == right)
        {
            car_num++;
            break;
        }
        else if(w[right] == 100)
        {
            int len = right -left +1;
            car_num = car_num + len/3 +(len%3  > 0? 1:0);
            break;
        }
        else if(w[left]+w[right]<=300)
        {
            car_num++;
            left++;
            right--;
        }
        else
        {
            car_num++;
            right--;
        }
    }
    cout<< car_num <<endl;

    return 0;
}
