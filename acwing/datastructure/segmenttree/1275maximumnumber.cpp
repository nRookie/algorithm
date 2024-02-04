#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;


const int N = 200010;

// 本题是一个动态的问题，
// 不能用RMQ来处理


struct Node {
    int l, r;
    int v; // 区间[l,r的最大值]
}tr[N * 4] ; // 开四倍


int m, p;


void pushup(int u) {  // 由子节点的信息，来计算父节点的信息
    tr[u].v = max(tr[u << 1].v , tr[u << 1 | 1].v);
}


void build (int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r); // 左右儿子没有并点
}

int query(int u, int l, int r) {// u是当前的节点
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v; //树中节点已经被完全包含在l r中了

    int mid = tr[u].l + tr[u].r  >> 1;  //当前树中区间的中点
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r); 
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));
    return v;
}


// 单点操作
void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v; //找到叶子节点了。
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

int main() {

    int n = 0, last = 0; // 上一个询问的答案

    scanf("%d%d", &m, &p);
    build(1,1,m);

    int x;

    char op[2];

    while (m --) {
        scanf("%s%d", op, &x);

        if (*op == 'Q') {
            // 查询的是后L个数
            last = query(1, n - x + 1, n);
            printf("%d\n", last);
        } else {
            modify(1, n + 1, (last + x) % p);
            n ++ ;
        }
    }
    return 0;
}