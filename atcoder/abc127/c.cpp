#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

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


// N ID cards,  M gates
// ith gate,   Lith, Li + 1-th,    ... Rith card
// 

typedef pair<int,int> PII;
int main() {
    int n, m;

    cin >> n >> m;

    vector<PII> a;

    while (m --) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, r});
    }

    sort(a.begin(), a.end());

    int ed = a[0].second;
    int st = a[0].first;
    for (int i = 1; i < a.size(); i ++) {
        if (ed >= a[i].first) {
            st = max(st, a[i].first);
            ed = min(ed, a[i].second);
        } else {
            cout << 0 << endl;
            return 0;
        }
    }

    cout << ed - st + 1 << endl;
    return 0;
}