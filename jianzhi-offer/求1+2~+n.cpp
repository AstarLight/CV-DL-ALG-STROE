#if 0
class Solution {
public:
    int Sum_Solution(int n) {
        if(n == 0)
            return 0;
        return n+Sum_Solution(n-1);
    }
};
#endif

class Solution {
public:
    int Sum_Solution(int n) {
        return (1+n)*n/2;
    }
};
