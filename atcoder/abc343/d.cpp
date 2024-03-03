#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

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


// N players numbered 1 to N.

// 1,2,...,T
// Ai, Bi 
// 10, 20, 30, and 20 point at some moment.
// 
int main() {
    int n,m;

    unordered_map<ll, int> cnt;
    cin >> n >> m;
    cnt[0] = n;
    vector<ll> scores(n + 1, 0);
    while (m --) {
        int a, b;
        cin >> a >> b;
        cnt[scores[a]] --;
        if (cnt[scores[a]] == 0) {
            cnt.erase(scores[a]);
        }
        scores[a] += b;
        cnt[scores[a]] ++;
        cout << cnt.size() << endl;
    }

    return 0;
}