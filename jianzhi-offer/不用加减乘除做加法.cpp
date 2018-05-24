class Solution {
public:
    int Add(int num1, int num2)
    {
        while(num2 != 0)
        {
           //位运算，第一步，先两个数二进制对应位数相加但不计进位，即异或
           int tmp = num1 ^ num2;
           //第二步，计算进位，即与和左移一位
            int carry = (num1 & num2) << 1;
            num1 = tmp;
            num2 = carry;
        }
        return num1;
    }
};
