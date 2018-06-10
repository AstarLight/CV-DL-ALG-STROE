

class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if (pHead==NULL)
            return NULL;
        if (pHead!=NULL && pHead->next==NULL)
            return pHead;
                 
        ListNode* current;
         
        if (pHead->next->val==pHead->val)  //如果当前节点与下一个节点的值相同
        {
            current=pHead->next->next; //跳到下下个节点
            while (current != NULL && current->val==pHead->val)  //如果当前节点与原始节点的值相同，则往后跳
                current=current->next;
            return deleteDuplication(current);   ///next应指向下一个无重复节点的链表           
        }
        else
        {
            current=pHead->next;
            pHead->next=deleteDuplication(current);  //next应指向下一个无重复节点的链表
            return pHead;
        }    
    }
};
