#include <iostream>
#include <vector>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;


const int N = 500010;
 

struct Node {
    int l, r;
    int v;  
}tr[N * 4] ;  


int m, p;


void pushup(int u) {  
    tr[u].v = max(tr[u << 1].v , tr[u << 1 | 1].v);
}


void build (int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);  
}

int query(int u, long long l, long long r) { 
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;  

    int mid = tr[u].l + tr[u].r  >> 1;   
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r); 
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));
    return v;
}


void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v; 
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}



int main() {
    long long N, D;
    cin >> N >> D;
    vector<long long > A(N);
    long long  m = 0;
    for (long long & a : A) {
        cin >> a;
        m = max(a, m);
    }
    build(1, 1, m + 1);
    int ans = 0;
    vector<int> dp(N, 1);
    // dp[i] = maximum length ending with the number i

    for (int i = 0; i < N; i ++) {
        dp[i] = query(1, max(A[i] - D, 0ll) + 1, min(A[i] + D, m) + 1) +1;
        modify(1, A[i] + 1, dp[i]);
        ans = max(ans,dp[i]);
    }

    printf("%d\n", ans);
    return 0;
}
