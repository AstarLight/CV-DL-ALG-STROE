/*
输入一个链表，输出该链表中倒数第k个结点
*/



/*
    思路：定义两个指针，一个快指针一个慢指针，快指针先跑K-1，然后两指针同时跑，
    当快指针到达链表尾部时，慢指针刚好到达指定位置。当然，需要注意边界和特殊情
    况，比如K值比链表长度短的情况，直接返回null。
*/



/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(!pListHead || k==0) return NULL;
        ListNode* pFast = pListHead;
        ListNode* p = pListHead;
        for(unsigned int i=1;i<k;i++)
        {
            if(pFast->next)
                pFast = pFast->next;
            else
                return NULL;
        }
        
        while(pFast->next)
        {
            pFast = pFast->next;
            p = p->next;
        }
        
        return p;
    }
};
