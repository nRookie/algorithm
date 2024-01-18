#include<iostream>
#include<cstring>
using namespace std;

const int N = 1010, M = 5000 * 3;


int wf[N];
int h[N],e[M], ne[M], idx, wt[M];
double dist[N];
int q[N], cnt[N];
bool st[N];

int n, m;


void add (int a ,int b, int c) {
    e[idx] = b , ne[idx] = h[a], wt[idx] = c, h[a] = idx ++;
}

bool check(double mid) {
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);

    int hh =0, tt = 0;
    for (int i = 1; i <= n; i ++) {
        q[tt ++] = i;
        st[i] = true;
    }

    while (hh != tt) {
        int t = q[hh ++];
        if (hh == N) hh = 0;

        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];

            if (dist[j] < dist[t] + wf[t] - mid * wt[i]) {
                dist[j] = dist[t] + wf[t] - mid * wt[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return true; 
                if (!st[j]) {
                    q[tt ++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 1; i<= n; i ++) cin >> wf[i];

    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add (a, b, c);
    }


    double l = 0, r = 1e6;
    //两位， 多两位
    while(r - l > 1e-4) {
        double mid = (l + r ) / 2;
        if (check(mid)) l = mid;
        else r= mid;
    }

    printf("%.2lf\n", l);
    return 0;
}