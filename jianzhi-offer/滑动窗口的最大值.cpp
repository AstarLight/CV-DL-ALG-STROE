class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> res;
        if(num.size() <= 0 || size > num.size() || size <=0)
            return res;
        for(unsigned int i=0;i<num.size();i++)
        {
            if(i+size <= num.size())
            {
                unsigned int end = i+size;
                vector<int> tmp;
                for(unsigned int j = i;j<end;j++)
                {
                    tmp.push_back(num[j]);
                }
                int max_val =  *max_element(tmp.begin(),tmp.end());  
                res.push_back(max_val);
            }
        }
        return res;
    }
};
