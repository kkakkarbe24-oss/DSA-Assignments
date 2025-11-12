// distinct_count_set.cpp
#include <bits/stdc++.h>
using namespace std;
int distinctUsingSet(const vector<int>& a){
    unordered_set<int> s(a.begin(), a.end());
    return (int)s.size();
}
int main(){
    vector<int> a = {1,2,2,3,4,4,4,5};
    cout << "Distinct count (set): " << distinctUsingSet(a) << '\n';
    return 0;
}
// distinct_count_sort.cpp
#include <bits/stdc++.h>
using namespace std;
int distinctUsingSort(vector<int> a){
    if (a.empty()) return 0;
    sort(a.begin(), a.end());
    auto it = unique(a.begin(), a.end());
    return (int)distance(a.begin(), it);
}
int main(){
    vector<int> a = {1,2,2,3,4,4,4,5};
    cout << "Distinct count (sort+unique): " << distinctUsingSort(a) << '\n';
    return 0;
}
