#include <iostream>
#include <algorithm>
#include <vector>
#include<cstring>
#include<limits.h>
using namespace std;

const int N = 21;


int overlap[N][N];


int dp[(1 << N)][N];


int calcOverlap(const string &a, const string & b) {
    int maxOverlap = 0;

    for (int i = 1; i <= min(a.size(), b.size()); ++i) {
        if (a.substr(a.size() - i) == b.substr(0 , i )) {
            maxOverlap = i;
        }
    }

    return maxOverlap;
}

int main() {
    int n;

    cin >> n; 
    vector<string> strings(n);

    for (int i = 0; i < n; ++i) {
        cin >> strings[i];
    }


    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && strings[i].find(strings[j]) != string::npos) {
                strings[j] = "";
            }
        }
    }
    strings.erase(remove(strings.begin(), strings.end(), ""), strings.end());

    n = strings.size();


    for (int i = 0; i < n; i ++) 
        for (int j = 0; j < n; j ++) {
            if (i != j) {
                overlap[i][j] = calcOverlap(strings[i], strings[j]);
            }
        }
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < n; i ++) {
        dp[1 << i][i] = strings[i].length();
    }

    for (int mask = 1; mask < (1 << n); mask ++) 
        for (int last = 0; last < n; last ++) {
            if (dp[mask][last] == -1) continue;
            for (int next = 0; next < n; next ++) {
                if (mask & (1 << next)) continue;
                int nextMask = mask | (1 << next);
                int newLength = dp[mask][last] + strings[next].length() - overlap[last][next];
                if (dp[nextMask][next] == -1 || dp[nextMask][next] > newLength) {
                    dp[nextMask][next] = newLength;
                }
            }
        }
    

    int minLength = INT_MAX;

    for (int i =0 ; i < n; i ++) {
        if (dp[(1 << n) - 1][i] < minLength ) {
            minLength = dp[(1 << n) - 1][i];
        }
    }

    cout << minLength << endl;

    return 0;
}
