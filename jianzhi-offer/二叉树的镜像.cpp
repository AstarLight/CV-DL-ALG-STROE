/*
操作给定的二叉树，将其变换为源二叉树的镜像。
*/

/*
    递归版的求解很好写，将根节点的左指针和右指针交换就可以了，并以此递归遍历所有节点。
    非递归版需要借助stack来遍历每个节点
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
    void Mirror(TreeNode *pRoot) {
        if(!pRoot) return;
            
        swap(pRoot->left,pRoot->right);
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};
#endif
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(!pRoot) return;
        
        stack<TreeNode*> m_stack;
        TreeNode* p;
        m_stack.push(pRoot);
        while(!m_stack.empty())
        {
            p = m_stack.top();
            m_stack.pop();
            swap(p->left,p->right);
            if(p->left)
                m_stack.push(p->left);
            if(p->right)
                m_stack.push(p->right);
        }
    }
};

// execrise on 2018.08.19
#if 0
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
    }
};
        if(pRoot == NULL)
            return;
        swap(pRoot->left, pRoot->right);
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};
#endif

class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot == NULL)
            return;
        stack<TreeNode*> s;
        s.push(pRoot);
        while(!s.empty())
        {
            TreeNode* p = s.top();
            s.pop();
            
            swap(p->left, p->right);
            
            if(p->left)
                s.push(p->left);
            if(p->right)
                s.push(p->right);
        }
    }
};
