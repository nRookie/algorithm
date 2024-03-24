#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<climits>
using namespace std;


int main() {
    int n;
    string s;

    cin >> n;
    cin >> s;

    vector<int> c(n);
    vector< vector< vector<long long> > > f(n + 1, vector<vector<long long > > (2, vector<long long> (2, LLONG_MAX)));
    for (int i = 0; i < n; i ++) cin >> c[i];

    if (s[0] == '0') {
        f[1][0][0] = 0;  
        f[1][0][1] = c[0];
    } else {
        f[1][0][1] = 0;
        f[1][0][0] = c[0];
    }



    for (int i = 2; i <= n; i ++) {
        if (s[i - 1] == '0') {
            f[i][1][0] = min(f[i - 1][0][0], f[i - 1][1][1]);
            f[i][1][1] = min(f[i - 1][1][0] + c[i - 1], f[i - 1][0][1] + c[i - 1]);  // f[i - 1][0][1]
            f[i][0][1] = f[i - 1][0][0] + c[i - 1];
            f[i][0][0] = f[i - 1][0][1];
        } else {// s[i - 1] == '1'
            f[i][1][1] = min(f[i - 1][0][1], f[i - 1][1][0] ); 
            f[i][1][0] = min(f[i - 1][1][1] + c[i - 1], f[i - 1][0][0] + c[i - 1]); 
            f[i][0][0] = f[i - 1][0][1] + c[i - 1];
            f[i][0][1] = f[i - 1][0][0];  

        }
        // cout << i << " " << s[i - 1] << endl;
        // cout << f[i][1][0] << endl;
        // cout << f[i][1][1] << endl;
        // cout << f[i][0][0] << endl;
        // cout << f[i][0][1] << endl;
        // cout << endl;
        
    }

    std::cout << min(f[n][1][0], f[n][1][1]) << endl;

}