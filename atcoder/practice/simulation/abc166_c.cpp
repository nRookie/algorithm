#include<iostream>
#include<cstring>
using namespace std;


const int N = 1e5, M = 3 *1e5;

int h[N], ne[M], e[M], idx;
int d[N];

int w[N];
int st[N];

int n, m;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a] , h[a] = idx ++;
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++) {
        cin>> w[i];
    }

    while(m --) {
        int a, b;
        cin >> a >> b ;
        if (w[a] > w[b]) d[b] ++;
        else if (w[a] == w[b])  d[a] ++, d[b] ++;
        else  d[a] ++;
    }
    int res = 0;
    for (int i = 1; i <= n; i ++) {
        if(d[i] == 0)  res ++;
    }

    cout << res << endl;
    return 0;

}