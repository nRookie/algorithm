#include<iostream>
#include<algorithm>
#include<limits.h>
using namespace std;


const int N = 200010;

struct Node{
    int l, r;
    int v;
}tr[N * 4];



void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}


void build(int u, int l , int r) {
    if (l == r) {
        tr[u] = {l, r};
        return;
    }
    tr[u] = {l, r};
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}


void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) {
        tr[u].v = v;
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

int query(int u, int l, int r) {
    if (tr[u].l >=l && tr[u].r <= r) return tr[u].v ;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        int v = 0;
        if (l <= mid) v = query(u << 1, l, r);
        // -----mid-----Tr
        //   ------r
        if (r > mid) v = max(v, query(u << 1 | 1, l, r));
        return v;
    }
}

int dp[N];

int n;

void normalize(std::vector<int> &v) {
  std::vector<int> aux = v;
  std::sort(aux.begin(), aux.end());
  aux.erase(std::unique(aux.begin(), aux.end()), aux.end());
  for(int i = 0; i < v.size(); i++)
    v[i] = std::lower_bound(aux.begin(), aux.end(), v[i]) - aux.begin() + 1;
}
 


int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++)
        std::cin >> v[i];
    normalize(v);
    
    int maxv = 0;
    for (int i = 0; i < n; i ++) {
        maxv = max(maxv, v[i] );
    }
    // a[i] + min num
    build(1, 1, maxv + 1);
    int ans = 0;
    for (int i = 0; i < n; i ++) {
        dp[i] = query(1, 1,  v[i] - 1) + 1;
        //cout << dp[i] << " "; 
        ans = max(ans, dp[i]);
        modify(1, v[i] , dp[i]);
    }

    cout << ans << endl;
    
    // -4 -3 - 2 - 1 
    // 8 2 
    // 6 
    
    // maxNum - minNum
    // a[i] - minNum
    

}