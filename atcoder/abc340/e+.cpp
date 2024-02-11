#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long LL;

const int N = 200010;

struct Node{
    int l, r;
    LL sum, add;
}tr[N * 4];

int w[N];




void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}


void opt_add (int u,LL d) {
    tr[u].sum += (LL)d * (tr[u].r - tr[u].l + 1);
    tr[u].add += d;
}
void pushdown(int u) {
    if (tr[u].add) {
        opt_add (u << 1,tr[u].add),opt_add (u << 1 | 1,tr[u].add);
        tr[u].add = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], 0};
    } else {
        tr[u] = {l, r, 0, 0}; // 为什么要把 w[l] 加进来？
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
 
}

// void build (int u,int l,int r) {
//     tr[u] = {l,r,w[l],0};
//     if (l == r) return ;
//     int mid = l + r >> 1;
//     build (u << 1,l,mid),build (u << 1 | 1,mid + 1,r);
//     pushup (u);
// }

// void modify(int u, int l, int r, int d) {
//     if (tr[u].l >= l && tr[u].r <= r) {
//         opt_add (u,d);
//     }
//     else {  // 当前区间太大了，一定要分裂
//         pushdown(u);
//         int mid = tr[u].l + tr[u].r >> 1;
//         if (l <= mid) modify(u << 1, l, r, d);
//         if (r > mid) modify(u << 1| 1, l, r, d);
//         pushup(u);
//     }
// }

void modify (int u,int l,int r,LL d) {
    if (l <= tr[u].l && tr[u].r <= r) {
        opt_add (u,d);
        return ;
    }
    pushdown (u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) modify (u << 1,l,r,d);
    if (r >= mid + 1) modify (u << 1 | 1,l,r,d);
    pushup (u);
}



// LL query(int u, int l, int r) {
//     if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;

//     pushdown(u);
//     int mid = tr[u].l + tr[u].r >> 1;
//     LL sum = 0;
//     if (l <= mid) sum += query(u << 1, l, r);
//     if (r > mid) sum += query(u << 1 | 1, l, r);
//     return sum;
// }
LL query (int u,int l,int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
    pushdown (u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL ans = 0;
    if (l <= mid) ans += query (u  << 1,l,r);
    if (r >= mid + 1) ans += query (u << 1 | 1,l,r);
    return ans;
}
int n, m;

int main() {
    int n, m;
    cin >> n >> m;
    build(1, 1, n);  

    for (int i = 1; i <= n; ++i) {
        int w;
        cin >> w;
        modify(1, i, i, w);
    }

    while (m--) {
        int b;
        cin >> b;
        if (n == 1) continue;
        b = b + 1;
        LL balls = query(1, b, b);
        // cout << "balls" << " " <<  b << " " << balls << endl;
        modify(1, b, b, -balls);
        LL x = balls % (n);
            // add
        modify(1, 1, n, balls / (n));
        if (!x) continue;

        if (b + x > n ) {
            if (b + 1 <= n) modify(1, b + 1, n, 1);
            modify(1, 1, b + x - n, 1);
        } else {
            if (b + 1 <= n) modify(1, b + 1, b + x, 1);
        }

    }

    for (int i = 1; i <= n; ++i) {
        cout << query(1, i, i) << " "; 
    }
    cout << endl;
 

    return 0;
}


