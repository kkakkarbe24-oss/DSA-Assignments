// sparse_triplet.cpp
#include <bits/stdc++.h>
using namespace std;
using T = tuple<int,int,int>; // r, c, val

struct Sparse {
    int rows, cols;
    vector<T> triplets;
    Sparse(int r=0,int c=0): rows(r), cols(c) {}
    void addTriplet(int r,int c,int v){ if(v!=0) triplets.emplace_back(r,c,v); }
    void normalize() {
        // Combine same (r,c) entries and remove zeros; sort by (r,c)
        sort(triplets.begin(), triplets.end(), [](const T& a,const T& b){
            if (get<0>(a)!=get<0>(b)) return get<0>(a)<get<0>(b);
            return get<1>(a)<get<1>(b);
        });
        vector<T> merged;
        for (auto &t: triplets) {
            if (!merged.empty() && get<0>(merged.back())==get<0>(t) && get<1>(merged.back())==get<1>(t)) {
                int nv = get<2>(merged.back()) + get<2>(t);
                merged.back() = {get<0>(t), get<1>(t), nv};
            } else merged.push_back(t);
        }
        triplets.clear();
        for (auto &t: merged) if (get<2>(t)!=0) triplets.push_back(t);
    }

    Sparse transpose() const {
        Sparse res(cols, rows);
        for (auto &t: triplets) res.addTriplet(get<1>(t), get<0>(t), get<2>(t));
        res.normalize();
        return res;
    }

    // Addition: dimensions must match
    Sparse add(const Sparse& B) const {
        if (rows!=B.rows || cols!=B.cols) throw runtime_error("Dimension mismatch");
        Sparse res(rows, cols);
        // merge two sorted lists by (r,c)
        vector<T> A_trip = triplets;
        vector<T> B_trip = B.triplets;
        sort(A_trip.begin(), A_trip.end());
        sort(B_trip.begin(), B_trip.end());
        size_t i=0,j=0;
        while(i<A_trip.size() && j<B_trip.size()){
            if (A_trip[i] < B_trip[j]) { res.triplets.push_back(A_trip[i++]); }
            else if (B_trip[j] < A_trip[i]) { res.triplets.push_back(B_trip[j++]); }
            else {
                int r=get<0>(A_trip[i]), c=get<1>(A_trip[i]);
                int s = get<2>(A_trip[i]) + get<2>(B_trip[j]);
                if (s!=0) res.triplets.emplace_back(r,c,s);
                ++i; ++j;
            }
        }
        while(i<A_trip.size()) res.triplets.push_back(A_trip[i++]);
        while(j<B_trip.size()) res.triplets.push_back(B_trip[j++]);
        return res;
    }

    // Multiplication: C = A * B
    Sparse multiply(const Sparse& B) const {
        if (cols != B.rows) throw runtime_error("Dimension mismatch for multiplication");
        // Build row-wise map for A: row -> vector<pair<col,val>>
        unordered_map<int, vector<pair<int,int>>> Arows;
        for (auto &t: triplets) Arows[get<0>(t)].emplace_back(get<1>(t), get<2>(t));
        // Build col-wise map for B: col -> vector<pair<row,val>> OR row-wise map for B
        unordered_map<int, vector<pair<int,int>>> BrowsByRow;
        for (auto &t: B.triplets) BrowsByRow[get<0>(t)].emplace_back(get<1>(t), get<2>(t));

        // For each row i in A and each entry (i, k) and for each (k, j) in B, add to C(i,j)
        unordered_map<long long, long long> Cvals; // key = i*(B.cols)+j
        for (auto &ar : Arows) {
            int i = ar.first;
            for (auto [k, aval] : ar.second) {
                // find row k in B
                auto it = BrowsByRow.find(k);
                if (it==BrowsByRow.end()) continue;
                for (auto [j, bval] : it->second) {
                    long long key = 1LL*i * B.cols + j;
                    Cvals[key] += 1LL * aval * bval;
                }
            }
        }
        Sparse C(rows, B.cols);
        for (auto &p : Cvals) {
            if (p.second==0) continue;
            int i = (int)(p.first / B.cols);
            int j = (int)(p.first % B.cols);
            C.addTriplet(i,j,(int)p.second);
        }
        C.normalize();
        return C;
    }

    void print() const {
        cout << "Triplet (r,c,val):\n";
        for (auto &t: triplets) cout << "("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")\n";
    }
};

int main(){
    // Example: A 3x3 sparse matrix
    Sparse A(3,3);
    A.addTriplet(0,0,1);
    A.addTriplet(0,2,2);
    A.addTriplet(1,1,3);
    A.normalize();

    Sparse B(3,3);
    B.addTriplet(0,1,4);
    B.addTriplet(2,2,5);
    B.normalize();

    cout << "A:\n"; A.print();
    cout << "B:\n"; B.print();

    auto At = A.transpose();
    cout << "A^T:\n"; At.print();

    auto S = A.add(B);
    cout << "A+B:\n"; S.print();

    auto P = A.multiply(B);
    cout << "A*B:\n"; P.print();
    return 0;
}
