#include <iostream>

using namespace std;

struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    int key;

    TreeNode(int x):key(x) {}
};

//建立搜索二叉树
void Bulid_BST(TreeNode* &root, int str[], int n);


//求二叉树的高度
int GetTreeHeigth(TreeNode* tree);
//求二叉树中叶子结点的个数
int GetLeafNum(TreeNode* tree);
//求二叉树中某层次结点的个数
int GetLevelNodeNum(TreeNode* tree, int level);
//求二叉树的宽度
int GetTreeWidth(TreeNode* tree);
// 求二叉树中所有结点的个数
int GetAllNodeNum(TreeNode* tree);
// 判断二叉树是否为满二叉树
bool isFullBinaryTree(TreeNode* tree);
// 判断二叉树是否为完全二叉树
bool isCompleteBinaryTree(TreeNode* tree);



int main()
{
    int key_words[] = {2,31,4,90,1,23,88,89,20,5,889,3,7};
    int num = sizeof(key_words) / sizeof(int);

    TreeNode* pRoot;
    Bulid_BST(pRoot, key_words, num);

    printf("tree all node num: %d\n",GetAllNodeNum(pRoot));


    return 0;
}


int BST_Insert(TreeNode* &tree, int key)
{
    if(tree == NULL)  //没有该节点就新建
    {
        tree = new TreeNode(key);
        tree->left = NULL;
        tree->right = NULL;
        return 0;
    }

    if(tree->key == key)  //已存在该点，直接返回
        return 0;
    else if(tree->key > key)
        return BST_Insert(tree->left, key);
    else
        return BST_Insert(tree->right, key);
}

/*用关键字数组str[]建立BST*/
void Bulid_BST(TreeNode* &root, int str[], int n)
{
    root = NULL;
    int i=0;
    while(i < n)
    {
        BST_Insert(root, str[i]);
        i++;
    }
}

//对该节点进行操作
void visit(TreeNode* root)
{
    printf("node key: %d\n", root->key);
}


int GetTreeHeigth(TreeNode* tree)
{
    if(tree == NULL)
        return 0;

    return 1 + max(GetTreeHeigth(tree->left), GetTreeHeigth(tree->right));
}


int GetLeafNum(TreeNode* tree)
{
    if(tree == NULL)
        return 0;

    if(tree->left == NULL && tree->right == NULL)
        return 1;

    return GetLeafNum(tree->left)+ GetLeafNum(tree->right);
}

int GetLevelNodeNum(TreeNode* tree, int level)
{
    if(tree == NULL || level < 1)
        return 0;

    if(level == 1)
        return 1;

    return GetLevelNodeNum(tree->left, level-1) + GetLevelNodeNum(tree->right, level-1);
}


int GetTreeWidth(TreeNode* tree)
{
    //对每一层调用GetLevelNodeNum求结点数目
    int width = GetLevelNodeNum(tree, 1);
    int height = GetTreeHeigth(tree);
    for(int i=2;i<=height;i++)
    {
        int m_width = GetLevelNodeNum(tree, i);
        if(m_width > width)
            width = m_width;
    }
    return width;
}


int GetAllNodeNum(TreeNode* tree)
{
    if(tree == NULL)
        return 0;

    return 1 + GetAllNodeNum(tree->left) + GetAllNodeNum(tree->right);
}
