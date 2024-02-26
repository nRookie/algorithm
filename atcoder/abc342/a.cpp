#include<iostream>
#include<vector>
#include<algorithm>
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



int main() {
    string s;
    cin >> s;
    int n = s.size();
    int cnt[26] = {0};
    bool st[26] = {0};
    for (int i = 0; i < n; i ++) {
        cnt[s[i] - 'a'] ++;
        st[s[i] - 'a'] = true;
    }
    for (int i = 0; i < n; i ++) {
        if (cnt[s[i] - 'a'] == 1) {
            cout << i + 1 << endl;
        }
    }
    return 0;
}