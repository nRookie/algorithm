#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

typedef long long ll;
int main() {
    long long cnt = 0, maxx = 1;

    priority_queue<ll, vector<ll>, greater<ll> > heap;


    int n;
    cin >> n;
    int x = n;

    heap.push(1);
    heap.push(1);
    heap.push(1);
    cnt = 3;
    while(heap.size()) {
        if (x == 1) {
            break;
        }
        ll t = heap.top();
        heap.pop();
        t = t * 10 + 1;
        heap.push(t);
        while(heap.size() && heap.top() < t) {
            heap.pop();
        }
        
        while(heap.size() < 3) {
            heap.push(1);
        }
        x --;
    }
    long long res = 0;
    // cout << cnt << " " << maxx <<  endl;
    while(heap.size()) {
        res += heap.top();
        heap.pop();
    }

    cout << res << endl;


    return 0;
}