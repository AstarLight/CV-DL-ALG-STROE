#include <stdio.h>
#include <stdlib.h>


struct ListNode
{
    ListNode* left;
    ListNode* right;
    int key;

    ListNode(int x): key(x) {}
};


int BST_Insert(ListNode* &tree, int key);
void Bulid_BST(ListNode* &root, int str[], int n);
void PreOrder(ListNode* root);
void InOrder(ListNode* root);
void PostOrder(ListNode* root);


int main()
{
    int key_words[] = {2,31,4,90,1,23,88,89,20,5,889,3,7};
    int num = sizeof(key_words) / sizeof(int);
    ListNode* pRoot;
    Bulid_BST(pRoot, key_words, num);

    PreOrder(pRoot);

    return 0;
}


int BST_Insert(ListNode* &tree, int key)
{
    if(tree == NULL)  //没有该节点就新建
    {
        tree = new ListNode(key);
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
void Bulid_BST(ListNode* &root, int str[], int n)
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
void visit(ListNode* root)
{
    printf("node key: %d\n", root->key);
}

void PreOrder(ListNode* root)
{
    if(root)
    {
        visit(root);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}


void InOrder(ListNode* root)
{
    if(root)
    {
        InOrder(root->left);
        visit(root);
        InOrder(root->right);
    }
}


void PostOrder(ListNode* root)
{
    if(root)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        visit(root);
    }
}
