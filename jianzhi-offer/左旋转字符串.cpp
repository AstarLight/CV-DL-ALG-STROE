class Solution {
public:
    string LeftRotateString(string str, int n) {
        int i = 0;
        string::iterator it;
        for(it = str.begin();it != str.end();it++,i++)
        {
            if(i == n)
            {
                break;
            }
            str += *it;
        }
        
        string res(it, str.end());
        return res;
    }
};
