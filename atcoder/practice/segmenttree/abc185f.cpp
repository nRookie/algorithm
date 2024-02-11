#include<iostream>
using namespace std;


const int N = 300010;


struct Node {
    int l, r;
    int xors ;
}tr[N * 4];


int w[N];

void pushup(int u) {
    tr[u].xors = tr[u << 1].xors ^ tr[u << 1 | 1].xors; 
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, w[l]};
    } else {
        tr[u] = {l, r};

        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r );
        pushup(u);
    }
}


int query(int u, int l, int r) {
    // l, r
                      //m
    // tr[u].l  --------- tr[u].r
    //      l ---------------------- r
    if (l <= tr[u].l && r >= tr[u].r) return tr[u].xors;
    else {
            //                  mid
            // tr[u].l  -------------------  tr[u].r
             //            l --------- r
            int mid = tr[u].l + tr[u].r  >> 1;
            
            //                  mid
            // tr[u].l  -------------------  tr[u].r
             //  l --------- r |
            int ans = 0;
            if (l <= mid) {
                ans = ans ^ query(u << 1, l, r);
            } 
            //                  mid
            // tr[u].l  -------------------  tr[u].r
                    //  l --------- r |
            if (r >= mid + 1) {
                ans = ans ^ query(u << 1 | 1, l, r);
            }
            return ans;
    }
}


void modify(int u, int x, int v) {
    if (tr[u].l == tr[u].r && tr[u].l == x) {
        tr[u].xors = tr[u].xors ^ v;
    }  else {
            //                  mid
            // tr[u].l  -------------------  tr[u].r
             //  x
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x,  v);
        pushup(u);
    }
}

int main() {

    int n,q ;
    cin >> n>> q;
    for (int i = 1; i <= n; i ++) {
        cin >> w[i];
    }
    build(1, 1, n);
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            modify(1, x, y);
        } else {
            cout << query(1, x, y) << endl;
        }
    }

 
    return 0;


}
