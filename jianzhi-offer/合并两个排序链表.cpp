/*
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
*/


/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
            val(x), next(NULL) {
    }
};*/
 
 #if 0
/*递归版本*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        
        if(!pHead1) return pHead2;
        if(!pHead2) return pHead1;
        
        ListNode* pMergeHead = NULL;
        if(pHead1->val < pHead2->val)
        {
            pMergeHead = pHead1;
            pMergeHead->next = Merge(pHead1->next, pHead2);
        }
        else
        {
            pMergeHead = pHead2;
            pMergeHead->next = Merge(pHead1, pHead2->next);
        }
        
        return pMergeHead;
    }
};
#endif

/*非递归版本*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(!pHead1) return pHead2;
        if(!pHead2) return pHead1;
        
        ListNode* pMergeHead = NULL;
        //先确定新链表头结点的位置，这是往下顺利执行的前提
        if(pHead1->val < pHead2->val) 
        {
            pMergeHead = pHead1;
            pHead1 = pHead1->next;
        }
        else
        {
            pMergeHead = pHead2;
            pHead2 = pHead2->next;
        }
        //存储新链表的头结点，用于返回
        ListNode* pHead = pMergeHead;
        
        while(pHead1 && pHead2)
        {
            if(pHead1->val < pHead2->val)
            {
                pMergeHead->next = pHead1;
                pMergeHead = pMergeHead->next;
                pHead1 = pHead1->next;
            }
            else
            {
                pMergeHead->next = pHead2;
                pMergeHead = pMergeHead->next;
                pHead2 = pHead2->next;
            }
        }
        //将没有遍历完的链表链接在新链表的背后
        if(pHead1) pMergeHead->next = pHead1;
        if(pHead2) pMergeHead->next = pHead2;
        
        return pHead;
    }
    
};


//exercise on 2018.08.18
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(!pHead1) return pHead2;
        if(!pHead2) return pHead1;
        
        ListNode* pMergeHead　= NULL;
        if(pHead1->val < pHead2->val)
        {
            pMergeHead = pHead1;
            pMergeHead->next = Merge(pHead1->next, pHead2);
        }
        else
        {
            pMergeHead = pHead2;
            pMergeHead->next = Merge(pHead2->next, pHead1);
        }
        return pMergeHead;
    }
};
