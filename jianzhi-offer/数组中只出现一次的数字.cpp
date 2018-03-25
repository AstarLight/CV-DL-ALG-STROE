/*
一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
*/


class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        map<int,int> m_map;

        for(int i=0;i<data.size();i++)
        {
            m_map[data[i]] += 1;
        }
        bool set_flag = false;
        for(map<int,int>::iterator it = m_map.begin();it != m_map.end();it++)
        {
            if(it->second == 1)
            {
                if(!set_flag)
                {
                    *num1 = it->first;
                    set_flag = true;
                }
                else
                    *num2 = it->first;
            }
        }
    }
};

#if 0   
class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        int sum = data[0];
        for(int i=1;i<data.size();i++)
        {
            sum = sum ^ data[i];
        }
        int flag = 1;
        while(flag)
        {
            if((sum & flag) != 0) break;
            flag = flag << 1;
        }
        vector<int> vec1;
        vector<int> vec2;
        for(int i=0;i<data.size();i++)
        {
            if((data[i] & flag) == 0)
            {
                vec1.push_back(data[i]);
            }
            else
            {
                vec2.push_back(data[i]);
            }
        }
        *num1 = vec1[0];
        for(int i=1;i<vec1.size();i++)
        {
            *num1 = *num1 ^ vec1[i];
        }
        *num2 = vec2[0];
        for(int i=1;i<vec2.size();i++)
        {
            *num2 = *num2 ^ vec2[i];
        }

    }
};
#endif
