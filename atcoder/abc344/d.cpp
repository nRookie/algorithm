#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

int main() {
    string T;
    cin >> T;
    int N;
    cin >> N;

    vector<vector<string>> bags(N);
    for(int i = 0; i < N; ++i) {
        int Ai;
        cin >> Ai;
        bags[i].resize(Ai);
        for(int j = 0; j < Ai; ++j) {
            cin >> bags[i][j];
        }
    }

    vector<int> dp(T.length() + 1, numeric_limits<int>::max());
    dp[0] = 0; 

    for(int i = 0; i < N; ++i) {
        vector<int> new_dp = dp;  
        for(const string& s : bags[i]) {
            for(int j = 0; j <= T.length(); ++j) {
                if(dp[j] != numeric_limits<int>::max() && j + s.length() <= T.length() && T.substr(j, s.length()) == s) {
                    new_dp[j + s.length()] = min(new_dp[j + s.length()], dp[j] + 1);
                }
            }
        }
        dp = new_dp; 
    }

    if(dp[T.length()] != numeric_limits<int>::max()) {
        cout << dp[T.length()] << endl;
    } else {
        cout << "-1" << endl;
    }

    return 0;
}
