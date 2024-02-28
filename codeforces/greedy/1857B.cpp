#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;



const int N = 2* 1e6 + 10, M = 4 * N;

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



// a, 
// 
void solve() {
    string x;

    cin >> x;
    x = '0' + x;
    int digit = x.size();

    for (int i = digit - 1; i >= 0 ; i  --) {
        if (x[i] >= '5') x[i - 1] ++,  digit = i;
    }

    for(int i=(x[0]=='0');i<x.size();i++)
    {
        cout<< (i>=digit ?'0':x[i]);
    }
    cout<<"\n";
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}