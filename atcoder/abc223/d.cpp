#include<iostream>
#include<cstring>
#include<queue>
using namespace std;


const int N = 2 * 1e5 + 10, M = 2 * 1e5 + 10;

int h[N], ne[M], e[M], idx;

int ind[N];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}


int n, m;
int main() {
    memset(h , -1, sizeof h);
    cin >> n >>  m;

    while(m --) {
        int a, b;
        cin >> a>> b;
        // a - > b
        add(a, b);
        ind[b]++;
    }
    queue<int> q;

    vector<int> res; 
    int cnt  = 0;
    priority_queue<int, vector<int>, greater<int>> heap;

    for (int i = 1; i <= n; i ++) {
        if (ind[i] == 0) {
            heap.push(i);
        }
    }

    while (heap.size()) {
        int t = heap.top();
        heap.pop();
        res.push_back(t);
        for (int i = h[t];  ~i; i = ne[i]) {
            int j = e[i];
            ind[j] --;
            if (ind[j] == 0) {
                heap.push(j);
            }
        }
    }


    // while(q.size() ) {

    //     while(heap.size()) {
    //         res.push_back(heap.top());
    //         heap.pop();
    //     }
    //     int t = q.front();
    //     q.pop();
    //     for (int i = h[t]; ~i; i = ne[i]) {
    //         int j = e[i];
    //         ind[j] --;

    //         if(ind[j] == 0) {
    //             q.push(j);
    //             heap.push(j);
    //         }
    //     }
    // }

    if (res.size() != n) {
        cout << -1 << endl;
        return 0;
    }
    for (auto x: res) cout << x << " ";

    cout << endl;

    return 0;

}



// topological sort with heap