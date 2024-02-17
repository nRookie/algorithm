#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 15;
int p[N], a[N][N], b[N], ans;
int n, m;

void dfs (int x) {
    if (x > n) {
        for (int i = 1; i <= m; i++) {
            int sum = 0;
            for (int j = 1; j <= a[i][0]; j++) {
                if (b[a[i][j]])     sum ++;
            }
            if (sum % 2 != p[i])    return ;
        }
        ans ++;
        return ;
    }
    b[x] = 0, dfs (x + 1);
    b[x] = 1, dfs (x + 1);
}

int main () {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i][0];
        for (int j = 1; j <= a[i][0]; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= m; i++)    cin >> p[i];
    dfs (1);
    cout << ans;
}




/*
#include<iostream>
 #define endl '\n'
 using namespace std;
 const int N=12;
 int a[N][N],num[N],p[N];
 int n,m,ans;
 ​
 bool check(int i){
     for(int j=0;j<m;j++){
         int t=0;
         for(int k=0;k<num[j];k++){
             t+=i>>(a[j][k]-1);
         }
         if(t%2!=p[j])return 0;
     }
     return 1;
 }
 ​
 int main(){ios::sync_with_stdio(false),cin.tie(nullptr);
     cin>>n>>m;
     for(int i=0;i<m;i++){
         cin>>num[i];
         for(int j=0;j<num[i];j++)
             cin>>a[i][j];
     }
     for(int i=0;i<m;i++)cin>>p[i];
     for(int i=0;i<(1<<n);i++) // 0000...00 ~ 1111...11（共n位）
         if(check(i))ans++;
     cout<<ans<<endl;
     return 0;
 }
 */