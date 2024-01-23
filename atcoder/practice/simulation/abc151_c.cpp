#include<iostream>
#include<set>
#include<unordered_set>
using namespace std;


 
int main() {
    unordered_set<int> visited;
    int n, m;
    cin >> n >> m;
    int correct = 0, error = 0;
    for (int i = 0; i < m ; i ++) {
        int p;
        string s;
        cin >> p ;
        cin >> s ;

        if (visited.count(p)) {
            
        } else {
            if (s == "WA") {
                error ++;
            } else {
                visited.insert(p);
                correct ++;
            }
        }
    }

    cout << correct << " " << error << endl;

    return 0;

}