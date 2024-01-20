#include<iostream>
#include<cstring>
using namespace std;

const int N = 110;


int dp[N]; 
// dp[i] = 0;
// dp[i] = 1;
// dp[i] = 2;
int main() {
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    string s;
    cin >> s;
    s = " " + s;
    // cout << s << endl;
    
    for (int i = 1; i < s.size(); i ++) {
        if (s[i] == 'A') {
            if(dp[i - 1] ==  0 || dp[i - 1] == 1) {
                dp[i] = 1;
            } else {
                // cout << dp[i - 1] <<endl;
                // cout <<"A" << endl;
                cout << "No" << endl;
                return 0;
            }
        } else if (s[i] == 'B') {
            if(dp[i - 1] == 0 || dp[i - 1] ==  1 || dp[i - 1] == 2) {
                dp[i] = 2;
            } else {
                // cout <<"B" << endl;
                cout << "No" << endl;
                return 0;
            }
        } else if (s[i] == 'C') {
            if(dp[i - 1] == 0 || dp[i - 1] ==  1 || dp[i - 1] == 2 || dp[i - 1] == 3) {
                dp[i] = 3;
            } else {
                // cout <<"C" << endl;
                cout << "No" << endl;
                return 0;
            }
        }
    }

    cout << "Yes" << endl;
}