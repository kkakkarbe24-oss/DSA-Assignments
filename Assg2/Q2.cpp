// bubble_sort.cpp
#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n-1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n-1-i; ++j) {
            if (a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break; // already sorted
    }
}

int main(){
    vector<int> a = {64,34,25,12,22,11,90};
    cout << "Before: ";
    for(int x: a) cout<<x<<' ';
    cout << "\n";
    bubbleSort(a);
    cout << "After: ";
    for(int x: a) cout<<x<<' ';
    cout << "\n";
    return 0;
}
