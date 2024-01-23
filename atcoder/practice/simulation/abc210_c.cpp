#include<iostream>
#include<unordered_map>
using namespace std;


const int N = 3 * 1e5 + 10;

int c[N];
int n, k ;

// bool check(int mid) {
//     unordered_map<int, int> visited;

//     for (int i = 0; i < k ; i ++) visited[c[i]] ++;
    
//     // 1 1 1 1  2 3 1 4
//     //       
//     int count = visited.size();
//     int count = visited.size();
//     int maxC = count;
//     for (int i = k ; i < n; i ++) {
//         visited[c[i - k]] --;
//         if (visited[c[i - k]] == 0) {
//             count --;
//         }
//         visited[c[i]] ++;
//         if (visited[c[i]] == 1) {
//             count ++;
//         }
//         maxC = max(count, maxC);
//     }

//     return mid <= maxC;
// }
int main() {

    cin >> n >> k;

    
    for (int i = 0; i < n; i ++) {
        cin >> c[i];
    }

    unordered_map<int, int> visited;

    for (int i = 0; i < k ; i ++) visited[c[i]] ++;
     
    int count = visited.size();
    int maxC = count;
    for (int i = k ; i < n; i ++) {
        visited[c[i - k]] --;
        if (visited[c[i - k]] == 0) {
            count --;
        }
        visited[c[i]] ++;
        if (visited[c[i]] == 1) {
            count ++;
        }
        maxC = max(count, maxC);
    }

    cout << maxC << endl;

    return 0;
}