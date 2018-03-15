/*
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
*/

/*
    本题不难，但是有一个大坑，容易进去了出不来，就是exponent的正负号，如果
    exponent是负的，那么如果我们在循环条件用了i<exponent作为结束条件，那
    当exponent为负数时这个循环将一次都不会进入。所以正确做法是将exponent取
    绝对值来作为循环的结束条件。
*/

class Solution {
public:
    double Power(double base, int exponent) {
        if(exponent == 0) return 1.0;
        if(base>=-0.00001 && base <= 0.00001) return 0;
        
        double result = 1.0;
        int absexp = abs(exponent);
        for(int i=0;i<absexp;i++)
        {
            result *= base;
        }
        return exponent > 0?result:(double)(1.0/result);


    }
};
