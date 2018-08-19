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
    int TreeDepth(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return 0;
        return 1 + max(TreeDepth(pRoot->left),TreeDepth(pRoot->right));
    }
};
#endif
class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if (pRoot == NULL)
            return 0;
        queue<TreeNode *> q;
        q.push(pRoot);
        int res = 0;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; ++i)
            {
                TreeNode *tmp = q.front();
                q.pop();
                if (tmp->left)
                {
                    q.push(tmp->left);
                }
                if (tmp->right)
                {
                    q.push(tmp->right);
                }
            }
            res++;
        }
	    return res;
    }
};

// exercise on 2018.08.19
class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return 0;
        return 1+max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
    }
};
