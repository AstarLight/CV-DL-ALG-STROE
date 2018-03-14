
/*
输入一个链表，从尾到头打印链表每个节点的值。
*/

/*
    思路一：用栈辅助
    思路二：递归
*/


/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/

#if 0
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        stack<int> node_stack;
        ListNode* p = head;
        vector<int> ret;
        while(p)
        {
            node_stack.push(p->val);
            p = p->next;
        }
        while(!node_stack.empty())
        {
            ret.push_back(node_stack.top());
            node_stack.pop();
        }
        return ret;
    }
};

#endif


class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> ret;
        if(!head) return ret;
        recursion_print(head,ret);
        return ret;
    }
private:

    void recursion_print(ListNode* head,vector<int>& ret)
    {
        if(head->next)
        {
            recursion_print(head->next,ret);
        }
        ret.push_back(head->val);
    }

};
