/*
思路：本题主要需要依靠multiset作为数据结构（最小堆）和advance来找到中间位置的元素的值。
*/

class Solution {
public:
    void Insert(int num)
    {
        s.insert(num);
    }

    double GetMedian()
    { 
        auto it1 = s.begin();
        if(s.size()%2 == 0)
        {
            auto it2 = it1;
            advance(it1,s.size()/2);
            advance(it2,s.size()/2-1);
            return ((*it1) + (*it2))/2.0;
        }
        else
        {
            advance(it1,s.size()/2);
            return *it1;
        }
    }
private:
    multiset<int> s;

};
