/*
请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
*/


/*
    思路：首先遍历字符串，统计空格个数，然后找到替换后结束指针p2所指向
    的位置，也记录原始串的结束指针p1指向的位置。分别指向从后往前遍历，遇到空格就替换成3个指定字符。
*/


class Solution {
public:
	void replaceSpace(char *str,int length) {
        char* pEnd,*pStart;
        pStart = str;
        char space_num = 0;
        //一次遍历统计空格个数
        while(*pStart != '\0')
        {
            if(*pStart == ' ') 
                space_num++;
            pStart++;
        }
        pEnd = pStart;
        //假设str指向的内存足够大
        char* pReize_end = pEnd + space_num*2;
        while(pEnd != str)
        {
            if(*pEnd == ' ')
            {
                *pReize_end-- = '0';
                *pReize_end-- = '2';
                *pReize_end = '%';
            }
            else
            {
                *pReize_end = *pEnd;
            }
            
            pReize_end --;
            pEnd--;
        }
        if(*pEnd == ' ')
        {
            *pReize_end-- = '0';
            *pReize_end-- = '2';
            *pReize_end = '%';
        }
        else
        {
            *pReize_end = *pEnd;
        }
	}

};


