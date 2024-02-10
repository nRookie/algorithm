#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_map>
using namespace std;

typedef long long ll;


unordered_map<ll,ll> hash1;
ll dfs(ll n) {

    if (n < 2 ) {
        return 0;
    }
    if (hash1.count(n)) {
        return hash1[n];
    }
    hash1[n] = dfs( (n + 2 - 1) / 2) + dfs(n / 2) + n;
    
    return  hash1[n];
}
int main() {
    // choose x >= 2
    // erase it ,  write  x + 2 / 2,       x / 2

    //pay x yen

    ll n;

    cin >> n;

    cout << dfs(n) << endl;
    // int res = 0;
    // while (n >= 2) {
    //     if (n & 1) {

    //     }

    // }
    // vector<int> number;
    // int res = 0;
    // number.emplace_back(n);
    // while (number.size()) {
    //     for (int i = 0; i <  ; i ++) {

    //     }


    // }

    return 0;
}