class Solution
{
public:
    //Insert one char from stringstream
    void Insert(char ch)
    {
        if(!m.count(ch))
        {
            m[ch] = 1;
            q.push(ch);
        }
        else
            m[ch] += 1;
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        while(!q.empty() && m[q.front()] > 1)
            q.pop();
        
        return q.empty()?'#':q.front();
    }
private:
    queue<char> q;
    map<char,int> m;
};
