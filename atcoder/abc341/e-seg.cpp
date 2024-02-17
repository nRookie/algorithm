#include <iostream>
using namespace std;

const int N = 500010; // Adjust based on problem constraints
struct Node {
    int l, r;
    int lnode, rnode; // Tracks the leftmost and rightmost bit values
    bool ans; // Represents if the segment is a "good string"
    bool tag; // Flip flag for lazy propagation
} tr[4 * N];

const int N = 500010;
int n,q;
int a[N];

void push_up(Node& root, Node left, Node right) {
    root.lnode = left.lnode;
    root.rnode = right.rnode;
    root.ans = left.ans && right.ans && (left.rnode != right.lnode);
}

void push_up(int u) {
    push_up(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void opt_tag(int u) {
    tr[u].lnode ^= 1;
    tr[u].rnode ^= 1;
    tr[u].tag ^= 1;
}

void push_down(int u) {
    if (tr[u].tag) {
        opt_tag(u << 1);
        opt_tag(u << 1 | 1);
        tr[u].tag = false;
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r, a[l], a[r], true, false};
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
}


void modify (int u,int l,int r) {
	if (l <= tr[u].l && tr[u].r <= r) {
		opt_tag (u);
		return ;
	}
	push_down (u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify (u << 1,l,r);
	if (r >= mid + 1) modify (u << 1 | 1,l,r);
	push_up (u);
}

Node query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u];
    push_down(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (r <= mid) return query(u << 1, l, r);
    if (l >= mid) return query(u << 1 | 1, l, r);
    Node ans;
    push_up(ans, query(u << 1, l, r), query(u << 1 | 1, l, r));
    return ans;
}

int main () {
	scanf ("%d%d",&n,&q);
	for (int i = 1;i <= n;i++) scanf ("%1d",&a[i]);
	build (1,1,n);
	while (q--) {
		int op,l,r;
		scanf ("%d%d%d",&op,&l,&r);
		if (op == 1) modify (1,l,r);
		else {
			if (query (1,l,r).ans) puts ("Yes");
			else puts ("No");
		}
	}
	return 0;
}