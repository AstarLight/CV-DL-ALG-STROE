/*
根据递归版的中序遍历和非递归版的中序遍历，可以给出两个版本的转化方式。
非递归版：先一步狂奔直到左孩子节点为空，需要一个辅助指针pre，用于记录以一个节点的地址。
访问当前节点时，需要将当前节点的left设为双向链表的前向指针，并将前一个节点的right设为
当前节点的地址，这就完成了双向链表中的前后指针的更新。
*/

/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
#if 0
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        //非递归中序遍历，访问节点的顺序是从小到大的
        if(!pRootOfTree)
            return NULL;
        
        stack<TreeNode*> s;
        TreeNode* p = pRootOfTree;
        TreeNode* pHead, *pre;
        bool isHead = true;
        while(p || !s.empty())
        {
            while(p)
            {
                s.push(p);
                p = p->left;
            }
            
            p = s.top();
            s.pop();
            if(isHead)
            {
                pHead = p;
                pre = p;
                isHead = false;
            }
            else
            {
                p->left = pre;
                pre->right = p;
                pre = p;
            }
            p = p->right;
        }
        return pHead;
    }
};
#endif

class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(!pRootOfTree)
            return NULL; 
        TreeNode* pLastNode = NULL; //指向双向链表的尾节点
        convertNode(pRootOfTree, &pLastNode);
        
        //找链表的头节点
        TreeNode* pHead = pLastNode;
        while(pHead != NULL && pHead->left != NULL)
            pHead = pHead->left;
        
        return pHead;
    }
private:
    void convertNode(TreeNode* pNode, TreeNode** pLastNodeInList)
    {
        if(!pNode)
            return;
        TreeNode* pCurrent = pNode;
        
        if(pCurrent->left)
            convertNode(pCurrent->left, pLastNodeInList);
        
        pCurrent->left = *pLastNodeInList;
       //将已经转换好的链表的最后一个节点的右指针指向当前节点
        if(*pLastNodeInList)
            (*pLastNodeInList)->right = pCurrent;
        //更新已经转换好的链表的最后一个节点
        *pLastNodeInList = pCurrent;

        //递归处理右子树
        if(pCurrent->right)
            convertNode(pCurrent->right, pLastNodeInList);
    }
};


//exercise on 2018.08.19
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(!pRootOfTree)
            return NULL;
        TreeNode* pLast = NULL;
        Convert(pRootOfTree, &pLast);
        
        while(pLast && pLast->left)
        {
            pLast = pLast->left;
        }
        
        return pLast;
    }
    
   void Convert(TreeNode* pRoot, TreeNode** pLast)
    {
        if(pRoot == NULL)
            return;
        Convert(pRoot->left, pLast);
        
        pRoot->left = *pLast;
        if(*pLast != NULL)
            (*pLast)->right = pRoot;
        *pLast = pRoot;
        
        Convert(pRoot->right, pLast);
    }
};
