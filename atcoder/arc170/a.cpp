#include<iostream>
using namespace std;

int main() {


    string s;
    string t;
    int n; 
    cin >> n;
    cin >> s;
    cin >> t;

    vector<int> ta(n, 0);
    vector<int> tb(n, 0);
    vector<int> sa(n, 0);
    vector<int> sb(n, 0);
    int res = 0;
    for (int i = 0; i < n; i ++) {
        if (i) {
            ta[i] = ta[i - 1];
            tb[i] = tb[i - 1];
            sa[i] = sa[i - 1];
            sb[i] = sb[i - 1];
        }
        if (t[i] == 'B') {
            tb[i] ++;
        } else {
            ta[i] ++;
        }

        if (s[i] == 'B') {
            sb[i] ++;
        } else {
            sa[i] ++;
        }

        if (tb[i] > ta[i]) {
            if (s[i] != 'B') {
                cout << - 1 << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i ++) {
        if (i) {
            ta[i] = ta[i - 1];
            tb[i] = tb[i - 1];
        }
        if (t[i] == 'B') {
            tb[i] ++;
        } else {
            ta[i] ++;
        }

        if (tb[i] > ta[i]) {
            if (s[i] != 'B') {
                cout << - 1 << endl;
                return 0;
            }
        }
    }
    return 0;
}