#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    vector<int> v = {1, 45, 54, 71, 76, 12};
    // int max = *max_element(v.begin(),v.end());
    int arr[] = {10,4,6,-10,0};
    int n = sizeof(arr)/sizeof(int);
    int max = *max_element(arr,arr+n);
    cout << max;
    // sort(v.begin(),v.end(),greater<int>());
    // for (int i = 0; i < v.size(); i++)
    // {
    //     cout << v[i] << " ";
    // }
    
}