
/*
思路：借助层次遍历的思路，记录每一层队列的长度。然后记录每一层的高度，奇数层
就数组背部插入元素，偶数层就头部插入元素。
*/
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
class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int> > res;
        if(!pRoot)
            return res;
        queue<TreeNode*> q;
        q.push(pRoot);
        int level = 1;
        vector<int> vec;

        while(!q.empty())
        {
            int q_size = q.size();
            for(int i=0;i<q_size;i++)
            {
                TreeNode* node = q.front();
                q.pop();
                
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
                
                if(level % 2 == 0)
                    vec.insert(vec.begin(),node->val);
                else
                    vec.push_back(node->val);
            }
            
            level++;
            res.push_back(vec);
            vec.clear();
        }
        return res;
    }
    
};
