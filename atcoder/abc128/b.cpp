#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



const int N = 1e6 + 10, M = 4 * N;

typedef pair<int,int> PII;
int h[N], ne[M], e[M], w[M], idx;

void add (int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

// i in Si,
// 100-point, Pi.
// 


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
struct Node {
    string name;
    int pp, id;

    bool operator < (const Node &W) const {
        if (name < W.name) {
            return true;
        } else if (name > W.name) {
            return false;
        } else {
            if (pp > W.pp) {
                return true;
            } else {
                return false;
            }
        }
    }
};


int main() {

    vector<Node > name;


    int n;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        string s;
        int pp;
        cin >> s;
        cin >> pp;
        name.push_back({s, pp, i + 1});
    }

    sort(name.begin(), name.end());


    for (auto na : name) {
        cout << na.id << endl;
    }
    return 0;
}