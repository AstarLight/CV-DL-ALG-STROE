class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int count = 0;
        for(int i=1;i<=n;i++)
        {
            int m = i;
            while(m)
            {
                if(m%10 == 1)
                {
                    count++;
                }
                m /= 10;
            }
        }
        return count;
    }
};
