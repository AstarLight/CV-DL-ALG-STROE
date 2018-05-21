/*
思路：定义出一个新的排序比较函数，比如紧紧靠近的两个元素n,m，若nm < mn，则交换m在前n在后
*/
class Solution {
public:
    string PrintMinNumber(vector<int> numbers) {
        sort(numbers.begin(),numbers.end(),cmp);
        string res;
        for(int i=0;i<numbers.size();i++)
        {
            string str(to_string(numbers[i]));
            res += str;
        }
        return res;
    }
private:
    static bool cmp(int a, int b)
    {
        string a_str(to_string(a));
        string b_str(to_string(b));
        string ab = a_str + b_str;
        string ba = b_str + a_str;
        return ab<ba;
    }
};
