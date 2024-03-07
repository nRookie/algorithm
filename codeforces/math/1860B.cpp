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
// a1 regular ,    infinitely
// k burles ,  ak regular coins,   infinitely

// 
void solve() {
      int m, k, a1, ak;
        cin >> m >> k >> a1 >> ak;
        
        // Step 1: Take as many k-value coins as possible
        int maxKCoins = m / k;
        int remainingCost = m % k;
        
        // Calculate how many regular and fancy coins of each type are used
        int usedRegularK = min(ak, maxKCoins);
        int usedFancyK = max(0, maxKCoins - ak);
        
        int usedRegular1 = min(a1, remainingCost);
        int usedFancy1 = max(0, remainingCost - a1);
        
        // Calculate potential replacements
        // This is either the number of unused regular 1-value coins divided by k (to see how many k-value replacements we can make)
        // or the number of used fancy k-value coins, whichever is smaller.
        int unusedRegular1 = a1 - usedRegular1;
        int replacements = min(unusedRegular1 / k, usedFancyK);
        
        
        // The total number of fancy coins used is the sum of fancy k and fancy 1 coins after replacements
        cout << usedFancyK + usedFancy1 - replacements << endl;
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}