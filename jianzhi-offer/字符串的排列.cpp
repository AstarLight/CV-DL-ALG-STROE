/*
链接：https://www.nowcoder.com/questionTerminal/fe6b651b66ae47d7acce78ffdd9a96c7
来源：牛客网

输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。 
输入描述:
输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。
*/


/*
    递归思路，先从左往右固定一个字符，让后面所有字符依次与其交换位置，然后递归执行，
    递归返回后继续对刚交换的字符再交换回来，以保持输入字符串不变。
    以这种方式遍历所有字符。还有就是注意审题，题目中要求打印要按照字典序进行，针对这个要
    求，我们可以对得到的全排列进行排序再返回。
*/


class Solution {
public:
    vector<string> Permutation(string str) {
        if(str.empty()) return str_list;
        Permutation(str,0);
        sort(str_list.begin(),str_list.end()); //保证以字典序输出
        return str_list;
    }
private:
    vector<string> str_list;
    
    void Permutation(string& str,int index)
    {
        if(index == str.size())
        {
            /*检查是否有重复字符串*/
            for(int i=0;i<str_list.size();i++)
            {
                if(str == str_list[i]) return;
            }
            str_list.push_back(str);
        }
        else
        {
            for(int i=index;i<str.size();i++)
            {
                char tmp = str[i];
                str[i] = str[index];
                str[index] = tmp;
                Permutation(str,index+1);
                
                //又换回来，保持字符串原样
                tmp = str[i];
                str[i] = str[index];
                str[index] = tmp;
            }
        }
        
    }
};
