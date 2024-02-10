#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;



int main() {
    int q;

    cin >> q;
    vector<int> a;
    while(q--) {
        int op;
        cin >> op;
        int x;
        cin >> x;
        
        if (op == 1) {
            a.push_back(x);
        } else {
            cout << a[a.size() - x] << endl;
        } 
    }
    return 0;
}