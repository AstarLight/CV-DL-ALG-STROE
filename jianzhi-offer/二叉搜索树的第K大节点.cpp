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
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if(!pRoot || k==0)
            return NULL;
        vector<TreeNode*> v;
        inOrder(pRoot, v);
        if(v.size() >= k)
            return v[k-1];
        else
            return NULL;
    }
private:
    void inOrder(TreeNode* pRoot, vector<TreeNode*> &v)
    {
        if(!pRoot)
            return;
        inOrder(pRoot->left, v);
        v.push_back(pRoot);
        inOrder(pRoot->right, v);
    }
};
#endif


class Solution {
public:
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if(!pRoot)
            return NULL;
        
        TreeNode* node = KthNode(pRoot->left, k);
        if(node)
            return node;
        if(++index == k)
            return pRoot;
        return node = KthNode(pRoot->right, k);
    }
private:
    int index = 0;
};
