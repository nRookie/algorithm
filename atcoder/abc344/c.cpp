#include<iostream>
#include<vector>
#include<set>
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
    int n, m , l;
    cin >> n;

    vector<int> a (n);
    set<ll> sum;
    for (int i = 0; i < n; i ++) cin >> a[i];
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i ++) cin >> b[i];
    cin >> l;
    vector<int> c(l);
    for (int i = 0; i < l; i ++) cin >> c[i];
    int q;

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++)
            for (int k = 0; k < l; k ++)  {
                sum.insert((ll)a[i] + b[j] + c[k]) ;
            }
    }

    cin >> q;
    vector<int> x(q);
    for (int i =0 ; i < q; i ++) cin >> x[i];

    for (int i = 0; i < q; i ++) {

        if (sum.count(x[i]) == false) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}