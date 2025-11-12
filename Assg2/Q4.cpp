// string_programs.cpp
#include <bits/stdc++.h>
using namespace std;

string concatenate(const string& a, const string& b) {
    return a + b;
}

string reverseStr(string s) {
    reverse(s.begin(), s.end());
    return s;
}

string deleteVowels(const string& s) {
    string out;
    for(char c: s) {
        char lc = tolower(c);
        if (lc=='a' || lc=='e' || lc=='i' || lc=='o' || lc=='u') continue;
        out.push_back(c);
    }
    return out;
}

vector<string> sortStrings(vector<string> arr) {
    sort(arr.begin(), arr.end());
    return arr;
}

char toLowercase(char c) {
    return (char)tolower(c);
}

int main(){
    // demo
    string a="Hello", b="World";
    cout << "Concat: " << concatenate(a,b) << '\n';
    cout << "Reverse: " << reverseStr(a) << '\n';
    cout << "Delete vowels: " << deleteVowels(\"Beautiful\") << '\n';

    vector<string> names = {\"zeta\",\"apple\",\"Mango\",\"banana\"};
    auto sorted = sortStrings(names);
    cout << "Sorted strings:\n";
    for(auto &s: sorted) cout << s << '\n';

    char C = 'G';
    cout << "Lowercase of " << C << " is " << toLowercase(C) << '\n';
    return 0;
}
