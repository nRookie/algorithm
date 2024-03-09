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
// notify to n people

// cost of p 

// 
void solve() {
    int n, p;
    cin >> n >> p;

    vector<int> a(n), b(n);

    for (int i = 0; i < n; i ++) cin >> a[i];

    for (int i = 0; i < n; i ++) cin >> b[i];
    vector<pair<int,int>> shares; 

    for (int i = 0; i < n; i ++) {
        shares.push_back({b[i], a[i]});
    }

    shares.push_back({p, - 1});

    sort(shares.begin(), shares.end());

    ll totalCost = p;

    int sharesNeeded = n - 1;

    for (auto &[cost, quantity] : shares) {
        if (sharesNeeded <= 0) break;
 
        if (quantity == -1) {
            totalCost += (ll) cost * sharesNeeded;
            break;
        } else {
            if (sharesNeeded >= quantity) {
                totalCost += (ll)cost * quantity;
                sharesNeeded -= quantity;
            } else {
                totalCost += (ll)sharesNeeded * cost;
                break;
            }
        }
    }

    cout << totalCost << "\n";
}



int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}