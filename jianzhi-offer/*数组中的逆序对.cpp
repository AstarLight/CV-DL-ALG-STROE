

class Solution {
public:
    long countRes ;
    int InversePairs(vector<int> data) {
        countRes = 0;
        if(data.size() == 0)
            return 0;
        MergeSort(data,0,data.size()-1);
        return countRes%1000000007 ;
    }
     
    void MergeSort(vector<int>& data,int first,int end){
        if(first < end){
            int mid = (first + end)/2;
            MergeSort(data,first,mid);
            MergeSort(data,mid+1,end);
            vector<int> tmp;
            MergeArray(data,first,mid,end,tmp);
        }
    }
    void MergeArray(vector<int>& data,int first,int mid,int end,vector<int> tmp){
        int i = first;int m = mid;
        int j = mid + 1;int n = end;
     
        while(i<=m && j<=n){
            if(data[i] > data[j]){
                tmp.push_back(data[i++]);
                countRes += n - j + 1;
            }
            else{
                tmp.push_back(data[j++]);
            }
        }
        while(i<=m)
            tmp.push_back(data[i++]);
        while (j<=n)
            tmp.push_back(data[j++]);
 
        //更新data数组
        int k = 0;
        for (int i = first; i <= end &&k<tmp.size(); i++)
            data[i] = tmp[k++];
         
    }
};
