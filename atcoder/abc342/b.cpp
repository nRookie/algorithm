#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}


typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll&  y) {
    
        if (b == 0) {
            x = 1;
            return a;
        }
        ll d = exgcd(b, a % b, y , x);
        y -= a/b * x;  
        
        return d;
}



int main() {

    int n;
    cin >> n;
    vector<int> p(n);
    unordered_map<int, int> hash;
    for (int i =0 ; i < n; i ++) {
        cin >> p[i];
        hash[p[i]] = i;
    }


    int q;
    cin >> q;

    while (q --) {
        int a, b;
        cin >> a >> b;

        if (hash[a] < hash[b]) {
            cout << a << endl;
        } else {
            cout << b << endl;
        }
    }

    return 0;


}