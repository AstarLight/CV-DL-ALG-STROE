
/*
思路一：借助哈希表，遍历链表时将每个节点的地址放进哈希表，如果遇到一个节点的地址在哈希表内已经有了，
表明该点就是第一个公共节点。
思路二：双指针法，两指针同时遍历，总有一个指针是先到链表尾部，到达尾部的指针需要将该指针指向另一个链表的
开头，遍历时检查节点地址是否一样。
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
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        map<ListNode*,int> m_map;
        while(pHead1 && pHead2)
        {
            if(m_map[pHead1] == 1)
                return pHead1;
            else
                m_map[pHead1] = 1;
            
            if(m_map[pHead2] == 1)
                return pHead2;
            else
                m_map[pHead2] = 1;
            
            pHead1 = pHead1->next;
            pHead2 = pHead2->next;
        }
        while(pHead1)
        {
            if(m_map[pHead1] == 1)
                return pHead1;
            else
                m_map[pHead1] = 1;
            pHead1 = pHead1->next;
        }
        while(pHead2)
        {
            if(m_map[pHead2] == 1)
                return pHead2;
            else
                m_map[pHead2] = 1;
            pHead2 = pHead2->next;
        }
        return NULL;
    }

};
#endif

class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1 || !pHead2) return NULL;
        ListNode* p1 = pHead1;
        ListNode* p2 = pHead2;
        
        while(p1 || p2)
        {
            if(p1 == p2) return p1;
            if(p1->next == NULL && p2->next == NULL) return NULL;
            
            if(!p1->next) 
                p1 = pHead2;
            else
                p1 = p1->next;
            
            if(!p2->next) 
                p2 = pHead1;
            else
                p2 = p2->next;
        }
        
        return NULL;
    }
};
