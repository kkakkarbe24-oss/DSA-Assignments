// missing_binary_search.cpp
#include <bits/stdc++.h>
using namespace std;

int missingBinarySearch(const vector<int>& a) {
    int l = 0, r = (int)a.size()-1;
    // If first element is not 1 -> missing is 1
    if (a.empty() || a[0] != 1) return 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == mid + 1) { // left part OK -> missing on right
            l = mid + 1;
        } else {
            // a[mid] > mid+1 -> missing on left including mid
            r = mid - 1;
        }
    }
    // l is index where a[l] != l+1, missing number is l+1
    return l + 1;
}

int main(){
    vector<int> a = {1,2,3,4,6,7}; // missing 5
    cout << "Missing (binary search): " << missingBinarySearch(a) << '\n';
    return 0;
}
