// count_inversions.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

long long mergeCount(vector<int>& a, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(a.begin()+l, a.begin()+m+1);
    vector<int> R(a.begin()+m+1, a.begin()+r+1);
    int i=0,j=0,k=l;
    long long inv=0;
    while(i<n1 && j<n2){
        if (L[i] <= R[j]) a[k++] = L[i++];
        else {
            a[k++] = R[j++];
            inv += (n1 - i); // all remaining in L are > R[j]
        }
    }
    while(i<n1) a[k++] = L[i++];
    while(j<n2) a[k++] = R[j++];
    return inv;
}

long long mergeSortCount(vector<int>& a, int l, int r){
    long long inv = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        inv += mergeSortCount(a, l, m);
        inv += mergeSortCount(a, m+1, r);
        inv += mergeCount(a, l, m, r);
    }
    return inv;
}

int main(){
    vector<int> a = {2, 4, 1, 3, 5};
    vector<int> b = a; // copy
    long long inv = mergeSortCount(b, 0, (int)b.size()-1);
    cout << "Number of inversions: " << inv << '\n';
    return 0;
}
