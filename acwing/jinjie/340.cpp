#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

const int N = 1010, M = 2 * 1e6 + 10;

int h[N], ne[N], e[M], w[M];
int idx = 0;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c; h[a] = idx ++;
}

int dist[N];
bool st[N];


int n, m, k ;



bool check(int bound) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[1] = 0;

    deque<int> dq;

    dq.push_back(1);


    while(dq.size()) {
        int t = dq.front(); 
        dq.pop_front();

        if (st[t]) continue;
        st[t] = true;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i], v = w[i] > bound;
            if (dist[j] > dist[t] + v) {
                if (v) {
                    dq.push_back(j);
                } else {
                    dq.push_front(j);
                }
            }

        }
    }

    return dist[n] <= k;
}
int main() {

    cin >> n >> m >> k;

    while (m --) {
        int a, b ,c;
        cin >> a >> b >> c ;

        add (a,b,c);
        add (b,a,c);
    }

        int l = 0, r = 1e6 + 1;
    
    while(l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    
    if (r == 1e6 + 1) r = -1;
    cout << r << endl;
    return 0;
}