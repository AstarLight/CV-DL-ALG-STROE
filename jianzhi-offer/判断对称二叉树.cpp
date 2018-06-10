/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
#if 0
class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return true;
        return isSame(pRoot->left, pRoot->right);
    }
private:
    bool isSame(TreeNode* pLeft, TreeNode* pRight)
    {
        if(!pLeft && !pRight)
            return true;
        if(!pLeft || !pRight)
            return false;
        if(pRight->val != pLeft->val)
            return false;
        return isSame(pLeft->left, pRight->right) && isSame(pLeft->right, pRight->left);
    }
};
#endif

class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return true;
        queue<TreeNode*> q1, q2;
        q1.push(pRoot->left);
        q2.push(pRoot->right);
        while(!q1.empty() && !q2.empty())
        {
            TreeNode* pLeft = q1.front();
            TreeNode* pRight = q2.front();
            q1.pop();
            q2.pop();
            
            if(!pLeft && !pRight)
                continue;
            if(!pLeft || !pRight)
                return false;
            if(pLeft->val != pRight->val)
                return false;
            q1.push(pLeft->left);
            q1.push(pLeft->right);
            q2.push(pRight->right);
            q2.push(pRight->left);
        }
        return true;
    }
};
