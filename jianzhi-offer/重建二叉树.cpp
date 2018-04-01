/*
    思路：我们知道只要知道了中序，再知道前序或者后序就可以重建二叉树了。因为，前序或后序表明根节点的位置，
    中序确定左右子树。
    第一次尝试：取前序数组的第一个元素作为节点，并在中序数组中找到它的位置，将中序数组分为两半，左边是左子树数组，
    右边是右子树数组，并生成左右子树前序的新数组，继续对坐子树数组递归求解，继续对右子树数组递归求解。
*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//https://blog.csdn.net/zgljl2012/article/details/48493143

class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        return reConstructBinaryTreeCore(pre,vin);
    }
private:
    TreeNode* reConstructBinaryTreeCore(vector<int> pre,vector<int> vin)
    {
        if(pre.size() == 0 || vin.size() == 0) return NULL;
        
        TreeNode* root = (TreeNode*)new TreeNode(pre[0]);
        int cur = -1;
        for(int i=0;i<vin.size();i++)
        {
            if(root->val == vin[i])
            {
                cur = i;
                break;
            }                
        }
                    
        if(cur == -1) return NULL; // 查找不到对应的节点
        
        //重建左子树
        vector<int> lpre;
        vector<int> lin;
        for(int i=0;i<cur;i++)
            lin.push_back(vin[i]);
        for(int i=1;i<lin.size()+1;i++)
            lpre.push_back(pre[i]);
        
        root->left = reConstructBinaryTreeCore(lpre,lin);

        //重建右子树
        vector<int> rpre;
        vector<int> rin;
        for(int i=cur+1;i<vin.size();i++)
            rin.push_back(vin[i]);
        for(int i=1+lin.size();i<pre.size();i++)
            rpre.push_back(pre[i]);
        
        root->right = reConstructBinaryTreeCore(rpre,rin);
        
        return root;
    }
};


