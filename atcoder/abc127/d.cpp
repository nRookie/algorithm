#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef pair<int,int> PII;


typedef long long ll;



int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);

    ll sum = 0;


    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
        sum += a[i];
        heap.push(a[i]);
    }



    vector<PII> bc(m + 1);

    for (int i = 1; i <= m; i ++) {
        int b, c;
        scanf("%d%d", &b, &c);
        bc[i] = {c, b};
    }

    sort(bc.begin() + 1, bc.end() );
    reverse(bc.begin() + 1, bc.end());

    for (int i = 1; i <= m; i ++) {
            int count = bc[i].second;
            int x = bc[i].first;
            for (int j = 0; j < count && x > heap.top(); j ++) {
                sum += x - heap.top();
                heap.pop();
                heap.push(x);
            }
    }

    cout << sum << endl;
}