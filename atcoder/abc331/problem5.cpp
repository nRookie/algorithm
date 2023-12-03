#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int N,Q;
string P[10000];
int cnt[10010][10010];
long g(int x,int y)
{
	return cnt[x][y];
}

long f(int x,int y)
{
    long leftTop = g(N,N)*(x/N)*(y/N);
    long rightTop =  g(N, y % N) * (x/N);
    long leftBottom = g(x % N, N) * (y / N);
    long rightBottom = g(x%N, y%N);
	return   leftTop + rightTop + leftBottom + rightBottom;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>N>>Q;
	for(int i= 0;i< N;i++)cin>>P[i];
	for(int i= 1;i<=N;i++)for(int j= 1;j <= N;j++)
	{
		cnt[i][j]=(P[i - 1][j - 1]=='B')+cnt[i][j - 1]+cnt[i - 1][j]-cnt[i - 1][j - 1];
	}
	for(;Q--;)
	{
		int A,B,C,D;
		cin>>A>>B>>C>>D;
        // use C + 1, D + 1, calculate the number of blocks.
		cout<<f(C + 1,D + 1)-f(C + 1,B)-f(A,D + 1)+f(A,B)<<"\n";
	}
}

