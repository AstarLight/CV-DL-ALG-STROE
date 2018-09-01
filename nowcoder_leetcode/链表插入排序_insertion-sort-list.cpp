/*Sort a linked list using insertion sort.*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#if 0  //迭代代码我觉得有问题，因为最后一个节点的next没有指向NULL，会造成环形链表
class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        ListNode* dumy = new ListNode(-10000);
        ListNode* pre = dumy;
        ListNode* p = head;
        while(p)
        {
            ListNode* next = p->next;
            pre = dumy;
            while(pre->next && pre->next->val < p->val)
            {
                pre = pre->next;
            }
            p->next = pre->next;
            pre->next = p;
            p = next;
        }
        return dumy->next;
    }
};
#endif

class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if(!head || !head->next)
            return head;
        
        ListNode* dumy = new ListNode(0);
        dumy->next = insertionSortList(head->next);
        
        ListNode* p = dumy;
        
        while(p && p->next && head->val > p->next->val)
        {
            p = p->next;
        }
        
        head->next = p->next;
        p->next = head;
        
        return dumy->next;
    }
};
