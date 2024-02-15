#include<iostream>

using namespace std;


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



// N side dies,  a fair coin, 

//1.   throw a die socre is the result of die
//2.   score is between 1... N - 1, keep flipping the coin,  score is doubled if the coin lands head up, 0 

//3. game ends when score becomes 0 or becomes K or above.

int main() {
    double n, k;


    cin >> n >> k;
    double res = 0;
    for (int i = 1; i <= n; i ++) {
        double sub = 1.0 / double(n);
        int point = i;
        while(point < k) {
            point *= 2;
            sub *= (1.0 /2.0);
        }
        // cout << sub << endl;
        res += sub;
    }
    // 0.145833333333
    // 0.145833333333

    printf("%0.12f\n", res);
}