#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>


using namespace std;



// int h[N], e[M], ne[M], idx;


// int q[N];


// void add (int a, int b) {
//     e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
// }

void bfs(int root) {

}

int M, D;

int y,m,d;
int main() {
    scanf("%d %d", &M, &D);

    scanf("%d %d %d", &y, &m, &d);

    int year_added = 0;
    int month_added = 0;
    d += 1;
    while (d > D) {
        d -= D;
        month_added ++;
    }
    m += month_added;
    while (m > M) {
        m -= M;
        year_added ++;
    }

    y += year_added;

    printf("%d %d %d\n",y, m, d);
    return 0;

}