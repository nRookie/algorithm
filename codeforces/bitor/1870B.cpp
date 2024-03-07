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
    int n, m;
    cin >> n >> m;

    int all = 0; 
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    for (int i = 0; i < m; i ++) {
        cin >> b[i];
        all |= b[i];
    }


    
    if (n & 1) {
        vector<int> c(n);
        for (int i = 0; i < n; i ++) c[i] |= all | a[i] ;
        int maxx = c[0];
        for (int i =1 ; i < n; i ++) maxx ^= c[i];
        int minn = a[0];
        for (int i =1 ; i < n; i ++) minn ^= a[i];
        cout << minn << " " << maxx << endl;
    } else {
        vector<int> c(n);
        for (int i = 0; i < n; i ++) c[i] |= all | a[i];
        int minn = c[0];
        for (int i =1 ; i < n; i ++) minn ^= c[i];
        int maxx = a[0];
        for (int i =1 ; i < n; i ++) maxx ^= a[i];
        cout << minn << " " << maxx << endl;
    }
 
}


int main() {
    int t;
    cin >> t;

    while (t --) {
        solve();
    }
}




/*
Effect of OR Operation with Even 
�
n: When we perform the OR operation on every element of 
�
a with any element from 
�
b, we set certain bits to 1 across all elements in 
�
a. If 
�
n is even, any bit that has been set to 1 in this manner will appear in an even number of elements. Because XOR-ing an even number of 1s results in 0, such bits do not contribute to the final XOR result. This means that the effect of setting these bits to 1 in all elements of 
�
a does not increase the overall XOR sum of 
�
a.

Maximum Value of 
�
x for Even 
�
n: Given the above, the confusion might arise from the question of how the maximum value of 
�
x could be obtained without performing any operations, considering that operations could potentially increase the number of 1 bits in the final XOR result. However, the key point is that for even 
�
n, the introduction of more 1 bits through OR operations with elements of 
�
b does not actually increase the final XOR result due to the even occurrences cancelling out. Therefore, the maximum value of 
�
x is already present without any modification — it is the XOR of all original elements in 
�
a. This is because adding more 1s through OR operations does not beneficially affect the XOR result when 
�
n is even, as these additional 1s do not contribute to the final XOR calculation (they cancel out).

In summary, when 
�
n is even, the OR operations with elements of 
�
b do not create a scenario where the XOR value of 
�
a increases beyond its original calculation, because the even distribution of newly set bits results in their cancellation in the context of an XOR operation.
*/