/*

重点分析pattern下一个字符为‘*’时，稍微复杂一些，因为‘*’可以代表0个或多个。
这里把这些情况都考虑到：
   a>当‘*’匹配0个字符时，str当前字符不变，pattern当前字符后移两位，
    跳过这个‘*’符号；
   b>当‘*’匹配1个或多个时，str当前字符移向下一个，pattern当前字符
    不变。（这里匹配1个或多个可以看成一种情况，因为：当匹配一个时，
    由于str移到了下一个字符，而pattern字符不变，就回到了上边的情况a；
    当匹配多于一个字符时，相当于从str的下一个字符继续开始匹配。这里return时为什么
    还要return match(str, pattern+2)?因为模式串的*号也可以不匹配任何字符。
*/

class Solution {
public:
    bool match(char* str, char* pattern)
    {
        if(*str=='\0' && *pattern=='\0')
            return true;
        if(*str!='\0' && *pattern=='\0')
            return false;
        if(*(pattern+1) != '*')
        {
            if(*pattern==*str || (*str!='\0' && *pattern=='.'))
                return match(str+1, pattern+1);
            else
                return false;
        }
        else
        {
            if(*pattern==*str || (*str!='\0' && *pattern=='.'))
                 return match(str, pattern+2) || match(str+1, pattern);
            else
                return match(str, pattern+2);
        }
    }
};
