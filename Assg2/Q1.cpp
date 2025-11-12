// binary_vs_linear.cpp
#include <bits/stdc++.h>
using namespace std;

int linearSearch(const vector<int>& a, int key) {
    for (size_t i=0;i<a.size();++i)
        if (a[i]==key) return (int)i;
    return -1;
}

int binarySearch(const vector<int>& a, int key) {
    int l=0, r=(int)a.size()-1;
    while(l<=r){
        int mid = l + (r-l)/2;
        if(a[mid]==key) return mid;
        else if(a[mid] < key) l = mid+1;
        else r = mid-1;
    }
    return -1;
}

int main(){
    vector<int> arr = {2,4,6,8,9,12,15};
    int key = 9;
    cout << "Linear search index: " << linearSearch(arr, key) << '\n';
    cout << "Binary search index: " << binarySearch(arr, key) << '\n';
    return 0;
}
