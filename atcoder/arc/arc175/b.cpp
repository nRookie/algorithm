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



// Correct Parenthesis Sequence reformulation

//The condition of being a correct parenthesis can be reformulated as follows: the string has an equal number of (s and )s , and the minimum cumulative sum of the sequence 
// obtained by replacing ( with  + 1 and ) with - 1 is 0




// In the first operation, the number of ( s does not change, so it is necessary to equalize the number of (s and )s by the second operation

// Let p b the number of ( s and q be the number of )s , then the required number of second operations can be determined as |p -m| / 2.


// From the reformulated conditions, it can be seen that if we are to replace ( with ), it is optimal to do it from right to left.


// and it is optimal to replace ) with ( from left to right.

// Next we consider the number of operations required to satisfy the condition that " the minimum cumulative sum of the sequence obtained by replacing ( with +1 and ) with -1
//is 0" by the 

int main() {
    int N;
    long long  A , B;

    cin >> N >> A >> B ;

    string S;
    cin >> S;

    A = min(A, 2 * B);

    int p = count(S.begin(), S.end(), '(');
    int m = 2 * N - p;

    int d = p - m ;

    long long res = 0;

    if (p > m) {
        for (int i = 2 * N - 1; i >= 0; -- i) {
            if (S[i] == '(' && d) {
                d -= 2;
                S[i] = ')';
                res += B;
            }
        }
    } else {
        for (int i = 0; i < 2 * N ; i ++) {
            if (S[i] == ')' && d) {
                d += 2;
                S[i] = '(';
                res += B;
            }
        }
    }

    long long cum = 0, mn = 0;


    for (int i = 0; i < 2 * N; i ++) {
        cum += (S[i] == '(' ? 1 : -1);
        mn = min(mn, cum);
    }

    res = res +  (-mn + 1) / 2 * A;
    cout << res << endl;


    


}