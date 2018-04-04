/*
输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
*/

/*
    思路：前序递归遍历二叉树，每访问一个节点，就将它放入path内，并把cur_num加上当前节点的值。
    需要判断当前访问的点是不是叶子节点，是的话就判断一下总路径值
    是否等于expectNumber，若等于则将该路径存入全局路径vecor内。如果这个点并非叶子节点，那就继续
    遍历其左右子树。需要注意，函数返回时，需要把路径中的该点给删除，同时cur_num减去该点的值。
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
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        if(!root) return vec;
        vector<int> path;
        int cur_num = 0;
        FindPath(root,expectNumber,path,cur_num);
        return vec;
    }
    
private:
    vector<vector<int> > vec;
    
    void FindPath(TreeNode* root, int expectNumber, vector<int>& path, int& cur_num)
    {
        cur_num += root->val;
        path.push_back(root->val);
        
        bool isLeaf = (!root->left && !root->right);
        if(cur_num == expectNumber && isLeaf)
        {
            vec.push_back(path);
        }
        
        if(root->left)
            FindPath(root->left,expectNumber,path,cur_num);
        if(root->right)
            FindPath(root->right,expectNumber,path,cur_num);
            
        //在返回父节点之前，在路径上删除当前节点
        cur_num -= root->val;
        path.pop_back();
    }
};
