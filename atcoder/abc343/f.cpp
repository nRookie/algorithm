#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;


typedef pair<int,int> PII;
const int N = 2000010;

int a[N];
struct node {
    int l, r;
    int m1, m2, c1,c2;
}tr[4 * N];

PII tmp[4];
int n, q;
void push_up(node & root, node left, node right) {
    int m1 = max(left.m1, right.m1);
    int c1 = 0;
    if (m1 == left.m1) c1 += left.c1;
    if (m1 == right.m1) c1 += right.c1;

    int m2 = max(left.m2, right.m2);
    int c2 = 0;
    if (left.m1 < m1) m2 = max(m2, left.m1);
    if (right.m1 < m1) m2 = max(m2, right.m1);

    if (m2 == left.m2) c2 += left.c2;
    if (m2 == right.m2) c2 += right.c2;
    if (m2 == left.m1) c2 += left.c1;
    if (m2 == right.m1) c2 += right.c1;
    root.m1 = m1, root.m2 = m2, root.c1 = c1, root.c2 = c2;
}

        // max1 = max(left.max1, right.max1);
        // freq1 = 0;
        // if (max1 == left.max1) freq1 += left.freq1;
        // if (max1 == right.max1) freq1 += right.freq1;
        // max2 = max(left.max2, right.max2);
        // if (left.max1 < max1) max2 = max(max2, left.max1);
        // if (right.max1 < max1) max2 = max(max2, right.max1);
        // freq2 = 0;
        // if (max2 == left.max2) freq2 += left.freq2;
        // if (max2 == right.max2) freq2 += right.freq2;
        // if (max2 == left.max1) freq2 += left.freq1;
        // if (max2 == right.max1) freq2 += right.freq1;


void push_up(int u) {
    push_up(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r){ 
    tr[u] = {l, r, a[l], -1, 1, 0};
    if (l == r) {
        tr[u] = {l, r, a[l], -1, 1, 0};
    } else {
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        push_up(u);
    }
}

void modify (int u, int x, int d) {
    if (tr[u].l == tr[u].r)  {
        tr[u].m1 = d;
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1;

    if (x <= mid) modify(u << 1, x, d);
    else  modify (u << 1 | 1 , x, d);
    push_up(u);

}

node query(int u, int l, int r) {
    // -------------------------------
    //        tr[u].l     tr[u].r
    //     l,                r
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u];
    } else  {
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        // -------------------------------
        //      tr[u].l     mid   tr[u].r
        //  l,           r
        else if (l >= mid + 1) return query (u << 1 | 1, l, r);
        // -------------------------------
        //      tr[u].l     mid   tr[u].r
        //                       l,           r
        else {
            // -------------------------------
            //      tr[u].l     mid   tr[u].r
            //               l,      r 
            auto left = query(u << 1, l, r);
            auto right = query(u << 1 | 1, l, r);
            node root;
            push_up(root, left, right);
            return root;
        }
    }
}



int main() {
    cin >> n >> q;

    for (int i = 1;i <= n; i ++) cin >> a[i];
    build(1, 1, n);

    while (q --) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) modify(1, l, r);
        else cout << query(1, l, r).c2 << endl;
    }

    return 0;
}
