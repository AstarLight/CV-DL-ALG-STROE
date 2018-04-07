#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

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
void LevelOrder(ListNode* root);


int main()
{
    int key_words[] = {2,31,4,90,1,23,88,89,20,5,889,3,7};
    int num = sizeof(key_words) / sizeof(int);
    ListNode* pRoot;
    Bulid_BST(pRoot, key_words, num);

    LevelOrder(pRoot);

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
    if(!root) return;

    stack<ListNode*> s;
    s.push(root);
    while(!s.empty())
    {
        ListNode* pNode = s.top();
        visit(pNode);
        s.pop();

        //谨记，先右孩子入栈，再左孩子入栈
        if(pNode->right)
            s.push(pNode->right);
        if(pNode->left)
            s.push(pNode->left);
    }
}

void InOrder(ListNode* root)
{
    if(!root) return;

    stack<ListNode*> s;
    s.push(root);
    ListNode* p = root;
    while(p || !s.empty())
    {
        if(p)   //向左一路狂奔，一边跑一边把走过的左孩子节点存入栈，直到跑到空节点
        {
            s.push(p);
            p = p->left;
        }
        else  //跑到了空节点，表明跑到尽头了
        {
            p = s.top();
            s.pop();
            visit(p);
            p = p->right;
        }
    }
}


void PostOrder(ListNode* root)
{
    stack<ListNode*> s;
    s.push(root);
    ListNode* c = root;  //表示的是最近栈的元素
    while(!s.empty())
    {
        ListNode* cur = s.top();
        if(cur->left!=NULL && cur->left!=c && cur->right!=c)
        {
            s.push(cur->left);
        }
        else if(cur->right!=NULL && c!=cur->right)
        {
            s.push(cur->right);
        }
        else
        {
            s.pop();
            c=cur;
            visit(cur);
        }
    }
}

void LevelOrder(ListNode* root)
{
    if(NULL == root) return;

    queue<ListNode*> q;
    q.push(root);
    while(!q.empty())
    {
        ListNode* pNode = q.front();
        q.pop();
        visit(pNode);

        if(pNode->left)
            q.push(pNode->left);
        if(pNode->right)
            q.push(pNode->right);

    }
}
