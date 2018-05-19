/*
思路一：先遍历顺序复制链表，并记录<原始节点addr，新链表节点的addr>的映射关系。第二次遍历时
对新链表节点的random指针通过查阅map进行赋值,时间复杂度O(N)，空间复杂度O(n)

思路二：对原来链表的每个节点进行复制，并将复制节点连接在当前节点之后，最后再将这个链表拆分成
两个链表，时间复杂度O(n)，空间复杂度O(1)
*/

/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/

#if 0
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(pHead == NULL)
            return NULL;
        
        map<RandomListNode*,RandomListNode*> addr_map;
        RandomListNode* pHeadNode = new RandomListNode(pHead->label);
        RandomListNode* pre = pHeadNode;
        RandomListNode* p = pHead->next;
        addr_map[pHead] = pHeadNode;
        while(p)
        {
            RandomListNode* pCurNode = new RandomListNode(p->label);
            addr_map[p] = pCurNode;
            pre->next = pCurNode;
            pre = pCurNode;
            p = p->next;
        }
        
        p = pHead;
        RandomListNode* p1 = pHeadNode;
        while(p && p1)
        {
            p1->random = addr_map[p->random];
            p = p->next;
            p1 = p1->next;
        }
        
        return pHeadNode;
    }
};
#endif

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(pHead == NULL)
            return NULL;
        
        RandomListNode* p = pHead;
        while(p)
        {
            RandomListNode* node = new RandomListNode(p->label);
            node->next = p->next;
            p->next = node;
            p = node->next;
        }
        
        RandomListNode* pClone = pHead->next;
        p = pHead;
        while(p && pClone)
        {
            pClone->random = p->random->next;
            p->next = pClone->next;
            p = p->next;
            pClone->next = p->next;
        }

        //split linkedlist
        pClone = pHead->next;
        RandomListNode* pCloneHead = pClone;
        p = pHead;
        while(p && pClone)
        {
            p->next = pClone->next;
            p = p->next;
            pClone->next = p->next;
            pClone = pClone->next;
        }
        
        return pCloneHead;
    }
    
};
