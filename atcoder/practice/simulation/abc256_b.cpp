#include<iostream>
#include<cstring>
using namespace std;

int main() {
    

    vector<int> squares(0);
    int n;
    cin >> n;
    vector<int> a(n);
    int P = 0;
    for (int i = 0; i < n; i ++) {
        squares.push_back(1);
        cin >> a[i];
        for (int j =  squares.size() - 1; j >= 0; j --) {
            squares[j] += a[i];
        }
    }

    for (int i = 0; i < squares.size(); i ++) {
        if (squares[i] > 4) {
            P ++;
        }
    }

    cout << P << endl;
    return 0;
}