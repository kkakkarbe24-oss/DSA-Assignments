// compact_matrices.cpp
#include <bits/stdc++.h>
using namespace std;

// Diagonal Matrix: store only diagonal elements (n)
struct Diagonal {
    int n;
    vector<int> d;
    Diagonal(int n): n(n), d(n,0) {}
    void set(int i,int j,int val){ if(i==j) d[i]=val; }
    int get(int i,int j) const { return (i==j)? d[i] : 0; }
};

// Tri-diagonal matrix: three arrays: lower( n-1 ), diag(n), upper(n-1)
struct Tridiagonal {
    int n;
    vector<int> lower, diag, upper;
    Tridiagonal(int n): n(n), lower(max(0,n-1),0), diag(n,0), upper(max(0,n-1),0) {}
    void set(int i,int j,int val){
        if (i==j) diag[i]=val;
        else if (i==j+1) lower[j]=val; // i=j+1 -> lower at index j
        else if (i+1==j) upper[i]=val; // upper at index i
    }
    int get(int i,int j) const {
        if (i==j) return diag[i];
        if (i==j+1) return lower[j];
        if (i+1==j) return upper[i];
        return 0;
    }
};

// Lower triangular stored row-wise using n*(n+1)/2
struct LowerTri {
    int n;
    vector<int> A; // size n*(n+1)/2
    LowerTri(int n): n(n), A(n*(n+1)/2,0) {}
    int index(int i,int j) const { // i,j are 0-based, we store only if i>=j
        // number of elements in previous rows: sum_{r=0 to i-1} (r+1) = i*(i+1)/2
        return i*(i+1)/2 + j;
    }
    void set(int i,int j,int val){ if (i>=j) A[index(i,j)] = val; }
    int get(int i,int j) const { return (i>=j) ? A[index(i,j)] : 0; }
};

// Upper triangular stored row-wise (only j>=i)
struct UpperTri {
    int n;
    vector<int> A; // size n*(n+1)/2
    UpperTri(int n): n(n), A(n*(n+1)/2,0) {}
    int index(int i,int j) const {
        // For upper triangle, map (i,j) with j>=i -> offset = sum_{r=0 to i-1} (n-r) = i*n - (i*(i-1))/2
        return i * n - (i*(i-1))/2 + (j - i);
    }
    void set(int i,int j,int val){ if (j>=i) A[index(i,j)] = val; }
    int get(int i,int j) const { return (j>=i) ? A[index(i,j)] : 0; }
};

// Symmetric: store lower triangle (or upper). Use same mapping as LowerTri.
struct Symmetric {
    int n;
    vector<int> A;
    Symmetric(int n): n(n), A(n*(n+1)/2,0) {}
    int index(int i,int j) const {
        if (i < j) swap(i,j);
        return i*(i+1)/2 + j;
    }
    void set(int i,int j,int val){ A[index(i,j)] = val; }
    int get(int i,int j) const { return A[index(i,j)]; }
};

int main(){
    // small demo
    Diagonal D(4);
    D.set(1,1,5);
    cout << "Diagonal (1,1) = " << D.get(1,1) << ", (1,2) = " << D.get(1,2) << '\n';

    Tridiagonal T(4);
    T.set(0,0,10); T.set(1,0,2); T.set(1,2,3);
    cout << "Tri (1,0) = " << T.get(1,0) << ", (1,1) = " << T.get(1,1) << '\n';

    LowerTri L(3);
    L.set(2,1,7);
    cout << "Lower (2,1) = " << L.get(2,1) << ", (0,2) = " << L.get(0,2) << '\n';

    UpperTri U(3);
    U.set(0,2,9);
    cout << "Upper (0,2) = " << U.get(0,2) << '\n';

    Symmetric S(3);
    S.set(0,2,42);
    cout << "Symmetric (2,0) = " << S.get(2,0) << '\n';
    return 0;
}
