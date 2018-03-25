/*
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0
*/

/*
    比较简单，但要注意细节：１．第一位的正负号，正数可能不带正号，所以要分情况讨论；
    ２．字符串中可能有非０～９的数；３．字符串为空；４．字符串超出ｉｎｔ范围(long long解决)
*/


class Solution {
public:
    int StrToInt(string str) {
        if(str.size() == 0) return 0;
        long long long_int = 0;
        int res_int = 0;
        int i = str.size()-1; //point to the last char
        int base = 1;
        while(i>=0)
        {
            if((i==0 && str[0]=='-') || (i==0 && str[0]=='+'))
                break;
            
            if(str[i] > '9' || str[i] < '0') return 0;
            
            long_int += (str[i] - '0')*base; 
            base *= 10;
            i--;
        }
        long_int = str[0]=='-'?-long_int:long_int;
        if(long_int > INT_MAX || long_int < INT_MIN) return 0;
        res_int = (int)long_int;
        return res_int;
        
    }
};
