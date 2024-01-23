#include<iostream>
#include<set>
#include<unordered_set>
#include<vector>
using namespace std;


 
int main() {
    unordered_set<int> visited;
    int n, m;
    cin >> n >> m;
    vector<int> error(n + 1, 0);
    vector<int> correct(n + 1, 0);
    for (int i = 0; i < m ; i ++) {
        int p;
        string s;
        cin >> p ;
        cin >> s ;

        if (correct[p] == 1) {
            
        } else {
            if (s == "WA") {
                error[p] ++;
            } else {
                correct[p] ++;
            }
        }
    }

    int sum1 = 0, sum2 = 0;

    for (int i = 1; i <= n; i ++) {
        if (correct[i] == 1) {
            sum1 += correct[i];
            sum2 += error[i];
        }
    }

    cout << sum1 << " " << sum2 << endl;

    return 0;

}