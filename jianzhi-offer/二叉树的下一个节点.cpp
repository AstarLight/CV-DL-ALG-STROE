/*
可分为三种情况：
1、有右子树的，那么下个结点就是右子树最左边的点；
2、没有右子树的，也可以分成两类:
a)是父节点左孩子,那么父节点就是下一个节点
b)是父节点的右孩子（eg：H，J，K，M）找他的父节点的父节点的父节点...
直到当前结点是其父节点的左孩子位置.
c)如果没有,那么他就是尾节点。

*/

/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        TreeLinkNode* p = pNode;
        if(!p)
            return NULL;
        if(p->right)  //对应情况1
        {
            p = p->right;
            while(p->left)
            {
                p = p->left;
            }
            return p;
        }
        if(p->next && p->next->left == p)  //对应情况2.a
            return p->next;
        else    //对应情况2.b
        {
            while(p->next)
            {
                TreeLinkNode* p2 = p->next;
                if(p2->left == p)
                    return p2;
                p = p->next;
            }
        }
        return NULL;  //对应情况2.c
    }
};
