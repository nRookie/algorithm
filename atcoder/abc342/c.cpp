#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
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
    string s;
    cin >> s;

    vector<int> dict(26, 0);

    for (int i = 0; i < 26; i ++)  dict[i] = i;
    int q;

    cin >> q;
    vector<bool> st(26, false);
    while(q --) {
        char a, b;
        cin >> a >> b;

        for (int i = 0; i < 26; i ++) {
            if (dict[i] == (a - 'a') ) {
                dict[i] = b - 'a';
            }
        }
    }

    for (int i = 0; i < n; i ++) {
        s[i] = (dict[s[i] - 'a'] + 'a');
    }

    cout << s << endl;

    return 0;


}