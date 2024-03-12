#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
#include <numeric>
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

struct Mycompare {
    bool operator() (const PII& a, const PII& b) {
        if (a.first == b.first) {
            return a.second > b.second;
        } else {
            return a.first < b.first;
        }
    }
};


// a, 
// 

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a (n);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
        a[i] %= k;
        if (a[i] == 0) a[i] = k;
    }

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    stable_sort(ord.begin(), ord.end(), [&](int i, int j) {
      return a[i] > a[j];
    });
    for (auto &x : ord) cout << x + 1 << ' ';
    cout << endl;
}
void solveHeap() {
    int n, k;
    cin >> n >> k;
    priority_queue<PII, vector<PII>, Mycompare> heap;
    for (int i = 1; i <= n; i ++) {
        int a;
        cin >> a;
        heap.push({a, i});
    }

    while(heap.size()) {
        int t = heap.top().first, index= heap.top().second;
        heap.pop();
        //cout << t << " " << index << endl;
        if (t - k <= 0) {
            cout << index << " ";
        } else {
            heap.push({t - k, index});
        }
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