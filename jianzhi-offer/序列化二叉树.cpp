/*
思路：二叉树序列化的意思就是，将二叉树的节点存的数据以字符串的形式存储下来，比如1,#,1,2,#
反序列化就是指将一个字符串转化为一个二叉树，之间的转化需要定义好编解码规则，
比如编解码时用的都是先序遍历。
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
    char* Serialize(TreeNode *root) {    
        if(!root)
            return NULL;
        preOrderCode(root, s);
        return const_cast<char *>(s.c_str());
    }
    TreeNode* Deserialize(char *str) {
        if(str==NULL||*str=='\0')
            return NULL;
        int num=0;  //记录当前操作的元素位置
        return preOrderDecode(str,num);
    }
private:
    string s;
    void preOrderCode(TreeNode *root, string& s)
    {
        if(!root)
        {
            s += "#,";
            return;
        }
        s += to_string(root->val) + ",";
        preOrderCode(root->left, s);
        preOrderCode(root->right, s);
    }
    
    TreeNode* preOrderDecode(char* str, int &num)
    {
        int val = 0;
        if(str[num] == '#')
        {
            num += 2;
            return NULL;
        }
        while(str[num]!=',' && str[num]!='\0')
        {
            val = val*10+str[num]-'0';
            num++;
        }
        num++; //跳过','，到达下一个元素
        TreeNode *root = new TreeNode(val);
        root->left = preOrderDecode(str,num);
        root->right = preOrderDecode(str,num);
        return root;
    }
};
