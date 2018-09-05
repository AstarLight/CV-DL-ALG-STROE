#include <stdio.h>
#include <algorithm>

using namespace std;

struct Node
{
    Node* next;
    int val;

    Node(int v): val(v), next(NULL)
    {

    }
};

Node* Partition(Node* pBegin, Node* pEnd)
{
    int key = pBegin->val;
    Node* p = pBegin;
    Node* q = pBegin->next;
    // 慢节点永远对应不大于轴元素的最后一个节点
    while(q != pEnd)
    {
        if(q->val < key)
        {
            p = p->next;
            swap(q->val, p->val);
        }
        q = q->next;
    }
    swap(p->val, pBegin->val);
    return p;
}

void QuickSort(Node* pBegin, Node* pEnd)
{
    if(pBegin != pEnd)
    {
        Node* pivot = Partition(pBegin, pEnd);
        QuickSort(pBegin, pivot);
        if(pivot->next)
            QuickSort(pivot->next, pEnd);
    }
}

void QuickSort(Node* pHead)
{
    QuickSort(pHead, NULL);
    printf("Hey! Quicksort completed\n");
}


int main()
{
    Node* dumy = new Node(0);
    Node* pHead = dumy;
    for(int i=100;i>=0;i--)
    {
        Node* p = new Node(rand()%1000);
        pHead->next = p;
        pHead = pHead->next;
    }

    QuickSort(dumy->next);

    Node* p = dumy->next;
    while(p)
    {
        printf("%d\n", p->val);
        p = p->next;
    }

    return 0;
}
