#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int main() {
    
    int n;
    cin >> n;
    vector<string> ss;
    for (int i = 0; i < n; i ++) {
        string s;
        cin >>  s;
        ss.push_back(s);
    }

    for (int i = n - 1; i >= 0;  i--) {
        cout <<ss[i] << endl;
    }

    return 0;
}