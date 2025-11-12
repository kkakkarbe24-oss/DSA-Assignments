// missing_linear.cpp
#include <bits/stdc++.h>
using namespace std;

// Using sum formula (careful about overflow for large n, use long long)
int missingBySum(const vector<int>& a, int n) {
    long long total = 1LL * n * (n+1) / 2;
    long long s = 0;
    for (int v : a) s += v;
    return (int)(total - s);
}

// Using XOR (safe against overflow)
int missingByXOR(const vector<int>& a, int n) {
    int xr = 0;
    for (int i=1;i<=n;++i) xr ^= i;
    for (int v: a) xr ^= v;
    return xr;
}

int main(){
    int n = 7; // elements 1..7, but one missing
    vector<int> a = {1,2,3,4,6,7}; // missing 5 (sorted)
    cout << "Missing (sum): " << missingBySum(a,n) << '\n';
    cout << "Missing (xor): " << missingByXOR(a,n) << '\n';
    return 0;
}
