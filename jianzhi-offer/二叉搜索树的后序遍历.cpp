/*
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

*/

/*
    思路：根据bst和后序遍历的特点可知，所给数组的最后一个数必定为根节点，然后根据bst特点可以知道，
    在根节点的左子树的值比根节点的值小，根节点右子树的值比根节点大，根据这个性质，我们去从头遍历函数给的
    数组，首先检测左子树是哪些（根据元素值与根节点值的比较），依次存起来；再检测右子树，依次存起来，然后递归
    求解各个子树。
*/

class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.size() < 1) return false;

        bool left = true;
        bool right = true;
        int root = sequence.back();
        vector<int> lTree,rTree;
        //将数组中比根节点小的数给存起来，这是左子树
        int i = 0;
        for(;i<sequence.size()-1;i++)
        {
            if(sequence[i] > root)
                break;
            lTree.push_back(sequence[i]);
        }
        //将数组中比根节点大的数给存起来，这是右子树
        int j = i;
        for(;j<sequence.size()-1;j++)
        {
            if(sequence[j] < root)
                return false;
            rTree.push_back(sequence[j]);
        }
        //递归求解左子树
        if(lTree.size() >= 2) 
            left = VerifySquenceOfBST(lTree);
        //递归求解右子树
        if(rTree.size() >= 2)
            right = VerifySquenceOfBST(rTree);
        return (left && right);
    }
};
