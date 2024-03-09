#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;



const int N = 2* 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



// a, 
// 'b' key, it acts like an unusal backspace

// B last uppercase
// 

// press is completely ignored

//  ARaBbbitBaby
void solve() {
    string s;

    cin >> s;
    int n = s.size();

    vector<pair<char, int>> low;
    vector<pair<char, int>> upper;
    for (int i = 0; i < n; i ++) {
        if (s[i] == 'b') {
            if (low.size()) low.pop_back();
        } else if (s[i] == 'B') {
            if(upper.size()) upper.pop_back();
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            low.push_back({s[i], i});
        } else {
            upper.push_back({s[i], i});
        }
    } 

    for (auto x : upper) {
        low.emplace_back(x);
    }
    sort(low.begin(), low.end(), [](pair<char,int> a, pair<char,int> b) {
        return a.second < b.second;
    });

    for (auto x : low) {
        cout<<x.first;
    }
    cout << endl;

    


 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}