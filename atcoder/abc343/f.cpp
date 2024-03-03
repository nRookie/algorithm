#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

const int MAXN = 2e5 + 5;
int n, q;
vector<int> a(MAXN);

struct Node {
    int max1, freq1, max2, freq2; // max1 is the largest, max2 is the second largest
    Node(int val = 0) : max1(val), freq1(1), max2(-1), freq2(0) {}
    void merge(const Node &left, const Node &right) {
        max1 = max(left.max1, right.max1);
        freq1 = 0;
        if (max1 == left.max1) freq1 += left.freq1;
        if (max1 == right.max1) freq1 += right.freq1;
        max2 = max(left.max2, right.max2);
        if (left.max1 < max1) max2 = max(max2, left.max1);
        if (right.max1 < max1) max2 = max(max2, right.max1);
        freq2 = 0;
        if (max2 == left.max2) freq2 += left.freq2;
        if (max2 == right.max2) freq2 += right.freq2;
        if (max2 == left.max1) freq2 += left.freq1;
        if (max2 == right.max1) freq2 += right.freq1;
    }
} seg[4 * MAXN];

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = Node(a[l]);
    } else {
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        seg[id].merge(seg[id * 2], seg[id * 2 + 1]);
    }
}

void update(int id, int l, int r, int pos, int val) {
    if (l == r) {
        seg[id] = Node(val);
    } else {
        int mid = (l + r) / 2;
        if (pos <= mid) update(id * 2, l, mid, pos, val);
        else update(id * 2 + 1, mid + 1, r, pos, val);
        seg[id].merge(seg[id * 2], seg[id * 2 + 1]);
    }
}

Node query(int id, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return Node(-1); // Return a dummy node
    if (ql <= l && qr >= r) return seg[id];
    int mid = (l + r) / 2;
    Node left = query(id * 2, l, mid, ql, qr);
    Node right = query(id * 2 + 1, mid + 1, r, ql, qr);
    Node result;
    result.merge(left, right);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, val;
            cin >> pos >> val;
            update(1, 1, n, pos, val);
        } else {
            int l, r;
            cin >> l >> r;
            Node result = query(1, 1, n, l, r);
            cout << (result.max2 == -1 ? 0 : result.freq2) << '\n';
        }
    }

    return 0;
}
