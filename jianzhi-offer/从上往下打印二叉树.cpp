/*
从上往下打印出二叉树的每个节点，同层节点从左至右打印
*/

/*
就是层次遍历二叉树，需要用到队列
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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> ret;
        if(!root) return ret;
        TreeNode* p = root;
        queue<TreeNode*> node_queue;
        while(p)
        {
            ret.push_back(p->val);
            if(p->left)
                node_queue.push(p->left);
            if(p->right)
                node_queue.push(p->right);
            if(node_queue.empty()) break;
            
            p = node_queue.front();
            node_queue.pop();
        }
        
        return ret;
    }
};
