
// G glass
// M mug
// G < M
#include<iostream>
using namespace std;

int G, M;
void dfs(int k, int & g, int & m) {
    if (k == 0) {
        return ;
    }
    // cout << "k g m" << endl;
    // printf("%d %d %d \n", k, g, m);
    if (g == G) {
        g -= G;
 
    } else if (m == 0) {
        m += M;
 
    } else {
        if ( m + g <= G) {
            g += m;
            m = 0;
        } else if (m + g > G) {
            // printf("m: %d g: %d , G:%d res:%d \n", m, g, G, m + g - G);
            m = m + g - G;
            g = G;
 
        } else {
            // cout <<" else branch" << endl;
        }
 
    }
    dfs(-- k, g, m);
}
int main() {
    int K;
    cin  >> K >> G >> M;
    int g = 0, m = 0;
    dfs(K, g, m);

    cout << g << " " <<  m << endl;

}