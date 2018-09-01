/*Sort a linked list using insertion sort.*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
