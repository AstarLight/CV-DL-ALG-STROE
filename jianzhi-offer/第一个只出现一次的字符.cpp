/*
在一个字符串(1<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置
*/

#if 0
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        map<char, int> m_map;
        for(int i=0;i<str.size();i++)
        {
            m_map[str[i]] += 1;
        }
        
        for(int i=0;i<str.size();i++)
        {
            if(m_map[str[i]] == 1) return i;
        }
        
        return -1;
    }
};
#endif

class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        char flag[256] = {0};
        for(int i=0;i<str.size();i++)
        {
            flag[str[i]] += 1;
        }
        
        for(int i=0;i<str.size();i++)
        {
            if(flag[str[i]] == 1) return i;
        }
        
        return -1;
    }
};
