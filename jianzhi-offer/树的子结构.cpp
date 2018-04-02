/*
输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
*/

/*
思路：在A树中先找出与B中根节点相等的节点，然后再迭代遍历遍历该节点下的子树。
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



class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        bool result = false;
        if(pRoot1 && pRoot2)
        {
            if(pRoot1->val == pRoot2->val)
                result = DoesTreeHasTree2(pRoot1, pRoot2);
            if(!result)
                result = HasSubtree(pRoot1->left, pRoot2);
            if(!result)
                result = HasSubtree(pRoot1->right, pRoot2);
        }
        return result;
    }
private:
    bool DoesTreeHasTree2(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot2) return true;
        if(!pRoot1) return false;
        
        if(pRoot1->val != pRoot2->val) return false;
        
        return DoesTreeHasTree2(pRoot1->left,pRoot2->left) && DoesTreeHasTree2(pRoot1->right,pRoot2->right);
    }
};
