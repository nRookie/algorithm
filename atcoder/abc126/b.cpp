#include<iostream>
#include<cstring>
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



int main() {
    string s;
    cin >> s;

    int first = (s[0] - '0') * 10  + s[1] - '0';
    int second = (s[2] - '0') * 10 + s[3] - '0';

    if (first <= 12 && first >= 1) {
        if (second <= 12 && second >= 1) {
            cout << "AMBIGUOUS" << endl;
        } else {
            cout << "MMYY" << endl;
        } 
    } else {
        if (second <= 12 && second >= 1) {
            cout << "YYMM" << endl;
        } else {
            cout << "NA" << endl;
        }
    }
    return 0;
}