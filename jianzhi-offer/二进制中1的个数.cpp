/*
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
*/


#if 0
class Solution {
public:
     int  NumberOf1(int n) {
         int count = 0;
         while(n)
         {
            n = (n-1) & n;
            count++;
         }         
         return count;
     }
};

#endif

class Solution {
public:
     int  NumberOf1(int n) {
         unsigned int flag = 1;
         int count = 0;
         while(flag)
         {
             if(flag & n)
             {
                 count++;
             }
             flag = flag<<1;
         }
         return count;
     }
};
