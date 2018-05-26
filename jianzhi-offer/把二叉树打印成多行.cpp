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
                    
                    vec.push_back(node->val);
                }
                
                res.push_back(vec);
                vec.clear();
            }
            
            return res;
        }
    
};
