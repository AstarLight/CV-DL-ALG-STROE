/*
链接：https://www.nowcoder.com/questionTerminal/d77d11405cc7470d82554cb392585106
来源：牛客网

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。
例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈
序列的弹出序列。（注意：这两个序列的长度是相等的）

*/



/*
    思路：每当压入一个元素，我们都检查一下当前栈顶元素与输出序列中当前的头元素是否相同，
    若是，则弹出栈顶元素，序列指针后移继续执行以上程序。若不相同，则继续将元素入栈，当
    所有元素都入栈了则表明该序列不可能是弹出序列，若最后栈为空则为弹出序列。
*/

class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        std::stack<int> m_stack;
        int pop_index = 0;
        for(int i=0;i<pushV.size();i++)
        {
            m_stack.push(pushV[i]);
            while(!m_stack.empty() && m_stack.top() == popV[pop_index])
            {
                m_stack.pop();
                pop_index++;
            }
        }
        
        return m_stack.empty()?true:false;
    }
};
