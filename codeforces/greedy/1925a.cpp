#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int t;

    cin >> t;

    while (t --) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i ++)
            for (char c = 'a'; c < 'a' + k; c ++)
                cout << c;
        cout << '\n';
    }
    return 0;
}