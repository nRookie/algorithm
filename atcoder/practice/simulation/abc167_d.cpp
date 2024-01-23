#include<iostream>
#include<queue>
#include<cstring>
#include<unordered_map>
using namespace std;


const int N = 2 * 1e5 + 10, M = N;

int h[N], ne[M], e[M], idx;
bool st[N];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int step = 0;
long long n, k;
int entry = -1;
unordered_map<int,int> location;
unordered_map<int,int> circle_location;
void bfs() {
    queue<int> q;

    q.push(1);
    st[1] = true;
    
    while (q.size()) {
        int t = q.front();
        // cout << "first bfs t is " << t << endl;
        q.pop();
        location[step] = t;
        step ++;

        if (step > k) {
            return;
        }
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            if (!st[j]) {
                st[j] = true;
                q.push(j);
            } else if (st[j]) { // the entry point of the circle
                entry = j;
                return ;
            }
        }
    }
}

void bfs1() {
    queue<int> q;
    memset(st, 0 ,sizeof st);
    q.push(1);
    st[1] = true;
    while (q.size()) {
        int t = q.front();
        if (t != entry) k --;
        else {
            break;
        }
        q.pop();
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            if (!st[j]) {
                st[j] = true;
                q.push(j);
            }
        }
    }
    int circle_step = 0;
    while(q.size()) {
        int t = q.front();
        q.pop();
        // cout << "t is " << t << endl;
        circle_location[circle_step] = t;
        circle_step ++;
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            if (!st[j]) {
                st[j] = true;
                q.push(j);
            }
        }
    }
}

int main() {

    memset(h, -1, sizeof h);
 
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) {
        int a;
        cin >> a ;
        add (i , a);
    }

    bfs();

    if (entry == -1) {
        cout << location[k] << endl;
    } else {
        bfs1();

        //cout << "entry is " << entry << endl;
     
        int circle_size = circle_location.size();
        //cout << k << " " << circle_size <<  endl;
        cout <<  circle_location[k % circle_size] << endl;
    }

    return 0;

}


// 4 5
// 3 2 4 1


// 1 -> 3
// 2 -> 2
// 3 -> 4
// 4 - >1


// 0 1  
// 1  3  
// 2  4  
// 3  1  
// 4  3 
// 5  4





// 1 -> 6
// 2 -> 5
// 3 -> 2
// 4 -> 5
// 5 -> 3
// 6 - > 2