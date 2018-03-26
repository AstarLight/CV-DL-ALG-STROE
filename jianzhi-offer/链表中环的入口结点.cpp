/*
一个链表中包含环，请找出该链表的环的入口结点。
*/

/*
    思路１：借助哈希表，将每个节点的地址存入哈希表，访问每个节点时判定哈希表内是否存在该key。
    时间复杂度：O(n)，空间复杂度O(n)
    思路２：断链法，当且仅当环一定存在时此法有效。
    设置两个指针，当前指针cur和pre指针，遍历链表，将pre指针的next设置为null，当cur变为null时，
    cur即为所求入口。
*/

#if 0
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(!pHead) return NULL;
        map<ListNode*,int> m_map;
        ListNode* p = pHead;
        while(p)
        {
            if(m_map.count(p)) return p; 
            m_map[p] = 1;
            p = p->next;
        }
        return NULL;
    }
};


class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(!pHead->next) return NULL;
        ListNode* cur = pHead->next;
        ListNode* pre = pHead;
        while(cur)
        {
            pre->next = NULL;
            pre = cur;
            cur = cur->next;
        }
        return pre;
    }
};
#endif
