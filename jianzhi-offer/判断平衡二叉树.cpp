/*
法一：递归求解，需要遍历每个节点并求该子树的高度，浪费时间和空间。
法二：后序遍历，经过每一个节点就记录这个节点的深度
*/
#if 0
class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        if(pRoot == NULL)
            return true;
        
        if(abs(GetTreeHeight(pRoot->left)-GetTreeHeight(pRoot->right)) >= 2)
            return false;
        
        return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);
    }
    
private:
    int GetTreeHeight(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return 0;
        return 1 + max(GetTreeHeight(pRoot->left), GetTreeHeight(pRoot->right));
    }
};
#endif

class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        int depth = 0;
        return IsBalanced_Solution(pRoot, depth);
    }
private:
    bool IsBalanced_Solution(TreeNode* pRoot, int & depth)
    {
        if(pRoot == NULL)
        {
            depth = 0;
            return true;
        }
        
        int left, right;
        if(IsBalanced_Solution(pRoot->left,left) && 
              IsBalanced_Solution(pRoot->right,right))
        {
            if(abs(left-right) < 2)
            {
                depth = 1 + (left>right?left:right);
                return true;
            }
        }
        return false;
    }
};
