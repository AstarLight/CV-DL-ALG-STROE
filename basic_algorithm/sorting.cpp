#include <iostream>
#include <stdio.h>

using namespace std;

/*升序排序*/
void quick_sort(int data[], int len);
void merge_sort(int data[], int len);
void bubble_sort(int data[], int len);
void heap_sort(int data[], int len);
void select_sort(int data[], int len);
void insert_sort(int data[], int len);
void shell_sort(int data[], int len);

int main()
{
    int test_data[] = {82,9,0,1,1,28,7,6,27,87,28,99,128,990,236,2,23,67};

    int num = sizeof(test_data)/sizeof(int);
    heap_sort(test_data,num);

    for(int i=0;i<num;i++)
        printf("%d ",test_data[i]);
    printf("\n");


    return 0;
}

int Partition(int data[],int low,int high)
{
    int pivot = data[low];  //以当前数组序号最小的元素作为枢轴
    while(low < high)
    {
        while(low<high && data[high] >= pivot) high--;
        data[low] = data[high];

        while(low<high && data[low] <= pivot) low++;
        data[high] = data[low];
    }
    data[low] = pivot; //枢轴元素放到最终位置
    return low; //返回枢轴的最终位置
}

void QuickSortCore(int data[], int low, int high)
{
    if(low < high)
    {
        int pivot_pos = Partition(data,low,high);
        QuickSortCore(data,low,pivot_pos-1);
        QuickSortCore(data,pivot_pos+1,high);
    }
}

void quick_sort(int data[], int len)
{
    QuickSortCore(data, 0, len-1);
}

void insert_sort(int data[], int len)
{
    int i,j;
    for(i=1;i<len;i++)
    {
        int tmp = data[i];
        if(data[i] < data[i-1])
        {
            for(j=i-1;j>=0;j--)
            {
                if(tmp < data[j])
                    data[j+1] = data[j];
                else
                    break;
            }
            data[j+1] = tmp;
        }
    }
}

void shell_sort(int data[], int len)
{
    int i,j,dk;  //dk就是增量，d(k+1) = d(k)/2
    for(dk=len/2;dk>=1;dk/=2)
    {
        for(i=dk;i<len;i++)
        {
            int tmp = data[i];
            if(data[i] < data[i-dk])
            {
                for(j=i-dk;j>=0;j-=dk)
                {
                    if(tmp < data[j])
                        data[j+dk] = data[j];
                    else
                        break;
                }
                data[j+dk] = tmp;
            }
        }
    }
}


void select_sort(int data[], int len)
{
    int i,j;
    for(i=len-1;i>=1;i--)
    {
        int max_id = i;
        for(j=0;j<i;j++)
        {
            if(data[max_id] < data[j])
            {
                max_id = j;
            }
        }

        if(max_id != i)
            swap(data[max_id], data[i]);
    }
}

void bubble_sort(int data[], int len)
{
    for(int i=0;i<len-1;i++)
    {
        bool end_flag = true;
        for(int j=0;j<len-i-1;j++)
        {
            if(data[j] > data[j+1])
            {
                swap(data[j],data[j+1]);
                end_flag = false;
            }
        }
        if(end_flag) return;
    }
}

void Merge(int data[], int vec[], int low, int mid, int high)
{
    int i,j,k;

    for(int k=low;k<=high;k++)
        vec[k] = data[k];

    for(i=low,j=mid+1,k=i;i<=mid && j<=high;k++)
    {
        if(vec[i] <= vec[j])
            data[k] = vec[i++];
        else
            data[k] = vec[j++];
    }
    while(i <= mid) data[k++] = vec[i++];
    while(j <= high) data[k++] = vec[j++];
}

void MergeSortCore(int data[], int vec[], int low, int high)
{
    if(low < high)
    {
        int mid = (low+high) / 2;
        MergeSortCore(data, vec, low, mid);
        MergeSortCore(data, vec, mid+1, high);
        Merge(data, vec, low, mid, high);
    }
}

void merge_sort(int data[], int len)
{
    int* pVec = (int*)malloc((len)*sizeof(int));
    MergeSortCore(data, pVec, 0, len-1);
    free(pVec);
}



void AdjustDown(int data[], int k, int len)
{
    int i;
    int tmp = data[k];  //先把当前节点的值存下来
    for(i=2*k+1;i<len;i=i*2+1) //2*k+1就是k节点的左孩子，i=i*2+1表示跳到该点的左孩子那里
    {
        if(i+1<len && data[i]<data[i+1]) i++;

        if(tmp > data[i])   //不用交换就直接返回，处理上层节点
            break;
        else
        {
            data[k] = data[i];
            k = i;
        }
    }
    data[k] = tmp;
}


void BuildMaxHeap(int data[], int len)
{
    for(int i=len/2-1;i>=0;i--)
        AdjustDown(data,i,len);
}

void heap_sort(int data[], int len)
{
    BuildMaxHeap(data, len);
    for(int i=len-1;i>=1;i--)
    {
        swap(data[i],data[0]);
        AdjustDown(data, 0,i);
    }
}

