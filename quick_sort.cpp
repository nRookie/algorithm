#include <bits/stdc++.h>
using namespace std;


 

int partition(vector<int> &arr,int first,int last) {

int pivot_index=first;

for(int i=first+1;i<=last;i++)
    if(arr[i]<arr[pivot_index])
    {
        int temp = arr[i];
        for(int j =i; j > pivot_index;j--)
        {
            arr[j]=arr[j-1];
        }
        arr[pivot_index] =temp;
        pivot_index++;
    }
    return pivot_index;
}

void quickSort(vector <int> &arr,int first,int last) {
    // Complete this function
    if(last-first<=0)
        return;
    int pivot_index=partition(arr,first,last);
    //getchar();
    //for(int i=0;i<arr.size();i++)
    //cout<<arr[i]<<" ";
    //cout<<endl;
    //getchar();
    quickSort(arr,first,pivot_index-1);  //or pivot_index , the exit condition change to <
    quickSort(arr, pivot_index+1,last);
    
    for(int i=first;i<=last;i++)
    cout<<arr[i]<<" ";
    cout<<endl;
}
int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr,0,n-1);

    return 0;
}


