/*
思路一，利用栈来存储分割出来的单词
*/
class Solution {
public:
    string ReverseSentence(string str) {
        stack<string> s;
        string m_str = "";
        for(int i=0;i<=str.size();i++)
        {
            if(str[i] == ' ' || str[i] == '\0')
            {
                s.push(m_str);
                if(str[i] == ' ')
                    s.push(" ");
                m_str = "";
            }
            else
                m_str += str[i];
        }
        
        string res;
        while(!s.empty())
        {
            res += s.top();
            s.pop();
        }
        return res;
    }
};
