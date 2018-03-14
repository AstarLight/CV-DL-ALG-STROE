/*
定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。
*/

/*
  思路：开两个栈：stack1和stack2，stack1是主栈，stack2是辅助栈，stack2中存的都是
  stack1当前元素中最小的元素。每当我们对stack1入栈时，我们需要判断入栈的元素是否比stack2
  的栈顶元素小，若是，则stack2同样push进这个元素，否则push栈2的栈顶元素进入stack2。min函数
  直接返回的stack2栈顶元素就是satck1当前的最小元素。
*/

class Solution {
public:
    void push(int value) {
        m_stack1.push(value);
        if(m_stack2.empty())
        {
            m_stack2.push(value);
        }
        else
        {
            m_stack2.push(value<m_stack2.top()?value:m_stack2.top());
        }
    }
    void pop() {
        m_stack1.pop();
        m_stack2.pop();
    }
    int top() {
        return m_stack1.top();
    }
    int min() {
        return m_stack2.top();
    }
private:
    stack<int> m_stack1;
    stack<int> m_stack2;
};
