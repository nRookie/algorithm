#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

int main() {
    int N, Q;
    cin >> N;

    list<int> seq;
    unordered_map<int, list<int>::iterator> posMap;
    for (int i = 0, val; i < N; ++i) {
        cin >> val;
        seq.push_back(val);
        posMap[val] = prev(seq.end()); 
    }

    cin >> Q;
    while (Q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x, y;
            cin >> x >> y;
            auto it = posMap[x]; 
            it++; 
            seq.insert(it, y);  
            posMap[y] = prev(it);
        } else if (type == 2) {
            int x;
            cin >> x;
            seq.erase(posMap[x]);
            posMap.erase(x); 
        }
    }

    for (int x : seq) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
