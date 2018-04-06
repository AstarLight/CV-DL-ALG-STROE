//
// Created by lijunshi on 18-4-6.
//

#include <stdio.h>

int BinarySearch(int data[], int len, int target);
int BinarySearch2(int data[], int len, int target);

int main()
{
    int test_data[] = {1,2,4,64,77,90,121,122,123,123,678,899,900};
    int num = sizeof(test_data) / sizeof(int);
    int index = BinarySearch2(test_data,num,900);

    printf("target index is %d\n",index);
    return 0;
}

int BinarySearchCore(int data[], int low, int high, int target)
{
    if(low <= high)
    {
        int mid = (low+high) / 2;
        if(data[mid] == target)
            return mid;
        else if(data[mid] < target)
            return BinarySearchCore(data, mid+1, high, target);
        else
            return BinarySearchCore(data, low, mid-1, target);
    }
    return -1;
}

//递归
int BinarySearch2(int data[], int len, int target)
{
    return BinarySearchCore(data, 0, len-1, target);
}

//非递归
int BinarySearch(int data[], int len, int target)
{
    int low = 0,high = len-1, mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(data[mid] == target)
            return mid;
        else if(data[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}
