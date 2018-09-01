
/*题目：Sort a linked list in O(n log n) time using constant space complexity.*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*
  考点：
  1. 快慢指针；2. 归并排序。
  此题经典，需要消化吸收。
  复杂度分析:
             T(n)            拆分 n/2, 归并 n/2 ，一共是n/2 + n/2 = n
            /    \           以下依此类推：
          T(n/2) T(n/2)      一共是 n/2*2 = n
         /    \  /     \
        T(n/4) ...........   一共是 n/4*4 = n
 
       一共有logn层，故复杂度是 O(nlogn)

所以对应此题目，可以划分为三个小问题：
1）找到链表中点 （快慢指针思路，快指针一次走两步，慢指针一次走一步，快指针在链表末尾时，慢指针恰好在链表中点）；
2）写出merge函数，即如何合并链表。 （见merge-two-sorted-lists 一题解析）
3）写出mergesort函数，实现上述步骤
 */

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (!head || !head->next) 
            return head;
        
        //快慢指针求链表中点
        ListNode* p = head, *q = head->next;
        while(q && q->next) {
            p = p->next;
            q = q->next->next;
        }
         
        ListNode* right = sortList(p->next);
        p->next = NULL;
        ListNode* left = sortList(head);
         
        return merge(left, right);
    }
    
private:
    //合并两个排好序的链表
    ListNode* merge(ListNode *left, ListNode* right)
    {
        ListNode dummy(0);
        ListNode *p = &dummy;
        while(left && right)
        {
            if(left->val < right->val)
            {
                p->next = left;
                left = left->next;
            }
            else
            {
                p->next = right;
                right = right->next;
            }
            p = p->next;
        }
        
        if (left) p->next = left;
        if (right) p->next = right;
        return dummy.next;
    }
};
