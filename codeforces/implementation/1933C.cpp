#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
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
   int a, b, l;
    cin >> a >> b >> l;
    set<int> ans;
    for(int i = 0; i <= 34; ++i){
        int x = l;
        bool fail = false;
        for(int _ = 0; _ < i; ++_){
            if(x % a){
                fail = true;
                break;
            }
            x /= a;
        }
        if(fail) break;
        while(true){
            ans.insert(x);
            cout <<  "x:" <<  x << endl;
            if(x % b) break;
            x /= b;
        }
    }
    cout << ans.size() << endl;
}


void solve1() {
    int a, b, l;

    cin >> a >> b >> l;

    set <int> ans;

    for (int i = 0; i < 34; i ++) {
        bool fail = false;
        int x = l;

        for (int _ = 0; _ < i; _ ++) {
            if (x % a) {
                fail = true;
                break;
            }
            x /= a;
        }

        if (fail) break;

        while (true) {
            ans.insert(x);
            if (x % b) break;
            x /= b;
        }
    } 

    cout << ans.size() << endl;
}

int main() {
    int t;
    cin >> t;

    while (t --) {
        solve1();
    }
}