
/*
输入一个链表，反转链表后，输出链表的所有元素
*/

/*
    遍历每个节点，记录下一个节点的位置和前一个节点的位置pre，让当前节点的next指向前一个节点的位置。
    注意最后需要将原来的头结点的next设为NULL，返回的新链表的头结点就是pre
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
    ListNode* ReverseList(ListNode* pHead) {
        if(!pHead || !pHead->next) return pHead;
        ListNode* cur = pHead->next;
        ListNode* pre = pHead;
        ListNode* next;
        while(cur)
        {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        
        //尾节点next指向NULL
        pHead->next = NULL;
        return pre;
    }
};
