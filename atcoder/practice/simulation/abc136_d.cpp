#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    int maxL = 0, maxR = 0;
    vector<int> a(n, 0);
    vector<int> L(n, 0);
    vector<int> R(n, 0);
    for (int i = 0; i < n; ) {
        int even = 0, odd = 0;
        while(s[i] == 'R') {
            i ++;
            if(i & 1) odd ++;
            else even ++;
        }
        int loc = i - 1;
        if (i & 1) {
            a[loc] += odd;
            a[loc + 1] += even;
        } else {
            a[loc] += even;
            a[loc + 1] += odd;
        }

        even = 0, odd = 0;
        while(s[i] == 'L') {
            i ++;
            if(i & 1) odd ++;
            else even ++;
        }

        if (i & 1) {
            a[loc] += even;
            a[loc + 1] += odd;
        } else {
            a[loc] += odd;
            a[loc + 1] += even;
        }
    }

    for (int i = 0; i < n; i ++) {
        cout << a[i] << " ";
    }

    return 0;

    
}
        