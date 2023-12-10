#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, plain;
string s;

int main() {

    cin >> n >> plain;
    cin >> s;

    int ap = plain, needed = 0, maxNeeded = 0;

    for (int i = 0; i <= s.length(); i ++) {
        if (s[i] == '2') {
            needed ++;
        } else if (s[i] == '1') {
            if (ap == 0) {
                needed ++;
            } else {
                ap --;
            }
        } else {
            maxNeeded = max(needed, maxNeeded);
            needed = 0;
            ap = plain;
        }
    }

    maxNeeded = max(needed, maxNeeded);

    cout << maxNeeded << endl;
}