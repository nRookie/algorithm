#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long LL;

const int N = 2 * 100010;

struct Node{
    int l, r;
    LL sum, add;
}tr[N * 4];

int w[N];




void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}


void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add, left.sum += (LL)(left.r - left.l + 1) * root.add;
        right.add += root.add, right.sum += (LL)(right.r - right.l + 1) * root.add;
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l], 0};
    } else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
 
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    }
    else {  // 当前区间太大了，一定要分裂
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1| 1, l, r, d);
        pushup(u);
    }
}



LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;

    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL sum = 0;
    if (l <= mid) sum = query(u << 1, l, r);
    if (r > mid) sum += query(u << 1 | 1, l, r);
    return sum;
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
        LL count = balls / (n);
        LL x = balls % (n);
            // add
        if (count) modify(1, 1, n, count);
        if (!x) continue;
        if (b + x >= n + 1) {
            if (x == n) modify(1, 1, x, 1);
            else  modify(1, x + 1, n, 1), modify(1, 1, b + x - n , 1);
            
        } else {
            modify(1, b + 1, b + x ,1);

            // for (int i = 1; i <= n; ++i) {
            //     cout << query(1, i, i) << " "; 
            // }
            // cout << endl;
        }

    }

    for (int i = 1; i <= n; ++i) {
        cout << query(1, i, i) << " "; 
    }
    cout << endl;
 

    return 0;
}