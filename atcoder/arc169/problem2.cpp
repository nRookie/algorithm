#ifndef LOCAL
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#endif

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
 // Include for setprecision


using namespace std;

using ll=long long;
#define int ll

#define rng(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,b) rng(i,0,b)
#define gnr(i,a,b) for(int i=int(b)-1;i>=int(a);i--)
#define per(i,b) gnr(i,0,b)
#define pb push_back
#define eb emplace_back
#define a first
#define b second
#define bg begin()
#define ed end()
#define all(x) x.bg,x.ed
#define si(x) int(x.size())
#ifdef LOCAL
#define dmp(x) cerr<<__LINE__<<" "<<#x<<" "<<x<<endl
#else
#define dmp(x) void(0)
#endif

template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;

using pi=pair<int,int>;
using vi=vc<int>;

template<class t,class u>
ostream& operator<<(ostream& os,const pair<t,u>& p){
	return os<<"{"<<p.a<<","<<p.b<<"}";
}

template<class t> ostream& operator<<(ostream& os,const vc<t>& v){
	os<<"{";
	for(auto e:v)os<<e<<",";
	return os<<"}";
}

using uint=unsigned;
using ull=unsigned long long;


ll read(){
	ll i;
	cin>>i;
	return i;
}

vi readvi(int n,int off=0){
	vi v(n);
	rep(i,n)v[i]=read()+off;
	return v;
}

pi readpi(int off=0){
	int a,b;cin>>a>>b;
	return pi(a+off,b+off);
}

template<class t>
void print_single(t x,int suc=1){
	cout<<x;
	if(suc==1)
		cout<<"\n";
	if(suc==2)
		cout<<" ";
}

template<class t,class u>
void print_single(const pair<t,u>&p,int suc=1){
	print_single(p.a,2);
	print_single(p.b,suc);
}

template<class T>
void print_single(const vector<T>&v,int suc=1){
	rep(i,v.size())
		print_single(v[i],i==int(v.size())-1?suc:2);
}

template<class T>
void print_offset(const vector<T>&v,ll off,int suc=1){
	rep(i,v.size())
		print_single(v[i]+off,i==int(v.size())-1?suc:2);
}

template<class T,size_t N>
void print_single(const array<T,N>&v,int suc=1){
	rep(i,N)
		print_single(v[i],i==int(N)-1?suc:2);
}

template<class T>
void print(const T&t){
	print_single(t);
}

template<class T,class ...Args>
void print(const T&t,const Args&...args){
	print_single(t,2);
	print(args...);
}

string readString(){
	string s;
	cin>>s;
	return s;
}

template<class T>
T sq(const T& t){
	return t*t;
}

void YES(bool ex=true){
	cout<<"YES\n";
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}
void NO(bool ex=true){
	cout<<"NO\n";
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}
void Yes(bool ex=true){
	cout<<"Yes\n";
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}
void No(bool ex=true){
	cout<<"No\n";
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}
//#define CAPITAL
/*
void yes(bool ex=true){
	#ifdef CAPITAL
	cout<<"YES"<<"\n";
	#else
	cout<<"Yes"<<"\n";
	#endif
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}
void no(bool ex=true){
	#ifdef CAPITAL
	cout<<"NO"<<"\n";
	#else
	cout<<"No"<<"\n";
	#endif
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}*/
void possible(bool ex=true){
	#ifdef CAPITAL
	cout<<"POSSIBLE"<<"\n";
	#else
	cout<<"Possible"<<"\n";
	#endif
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}
void impossible(bool ex=true){
	#ifdef CAPITAL
	cout<<"IMPOSSIBLE"<<"\n";
	#else
	cout<<"Impossible"<<"\n";
	#endif
	if(ex)exit(0);
	#ifdef LOCAL
	cout.flush();
	#endif
}

constexpr ll ten(int n){
	return n==0?1:ten(n-1)*10;
}

const ll infLL=LLONG_MAX/3;

#ifdef int
const int inf=infLL;
#else
const int inf=INT_MAX/2-100;
#endif

int topbit(signed t){
	return t==0?-1:31-__builtin_clz(t);
}
int topbit(ll t){
	return t==0?-1:63-__builtin_clzll(t);
}
int topbit(ull t){
	return t==0?-1:63-__builtin_clzll(t);
}
int botbit(signed a){
	return a==0?32:__builtin_ctz(a);
}
int botbit(ll a){
	return a==0?64:__builtin_ctzll(a);
}
int botbit(ull a){
	return a==0?64:__builtin_ctzll(a);
}
int popcount(signed t){
	return __builtin_popcount(t);
}
int popcount(ll t){
	return __builtin_popcountll(t);
}
int popcount(ull t){
	return __builtin_popcountll(t);
}
int bitparity(ll t){
	return __builtin_parityll(t);
}
bool ispow2(int i){
	return i&&(i&-i)==i;
}
ll mask(int i){
	return (ll(1)<<i)-1;
}
ull umask(int i){
	return (ull(1)<<i)-1;
}
ll minp2(ll n){
	if(n<=1)return 1;
	else return ll(1)<<(topbit(n-1)+1);
}

bool inc(int a,int b,int c){
	return a<=b&&b<=c;
}

template<class t,class u>
int lwb(const vc<t>&v,const u&a){
	return lower_bound(all(v),a)-v.bg;
}
template<class t,class u>
bool bis(const vc<t>&v,const u&a){
	return binary_search(all(v),a);
}

vvc<int> readGraph(int n,int m){
	vvc<int> g(n);
	rep(i,m){
		int a,b;
		cin>>a>>b;
		//sc.read(a,b);
		a--;b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	return g;
}

vvc<int> readTree(int n){
	return readGraph(n,n-1);
}

template<class t>
vc<t> presum(const vc<t>&a){
	vc<t> s(si(a)+1);
	rep(i,si(a))s[i+1]=s[i]+a[i];
	return s;
}
vc<ll> presum(const vi&a){
	vc<ll> s(si(a)+1);
	rep(i,si(a))s[i+1]=s[i]+a[i];
	return s;
}
//BIT で数列を管理するときに使う (CF850C)
template<class t>
vc<t> predif(vc<t> a){
	gnr(i,1,si(a))a[i]-=a[i-1];
	return a;
}
template<class t>
vvc<ll> imos(const vvc<t>&a){
	int n=si(a),m=si(a[0]);
	vvc<ll> b(n+1,vc<ll>(m+1));
	rep(i,n)rep(j,m)
		b[i+1][j+1]=b[i+1][j]+b[i][j+1]-b[i][j]+a[i][j];
	return b;
}

//verify してないや
void transvvc(int&n,int&m){
	swap(n,m);
}
template<class t,class... Args>
void transvvc(int&n,int&m,vvc<t>&a,Args&...args){
	assert(si(a)==n);
	vvc<t> b(m,vi(n));
	rep(i,n){
		assert(si(a[i])==m);
		rep(j,m)b[j][i]=a[i][j];
	}
	a.swap(b);
	transvvc(n,m,args...);
}
//CF854E
void rotvvc(int&n,int&m){
	swap(n,m);
}
template<class t,class... Args>
void rotvvc(int&n,int&m,vvc<t>&a,Args&...args){
	assert(si(a)==n);
	vvc<t> b(m,vi(n));
	rep(i,n){
		assert(si(a[i])==m);
		rep(j,m)b[m-1-j][i]=a[i][j];
	}
	a.swap(b);
	rotvvc(n,m,args...);
}

//ソートして i 番目が idx[i]
//CF850C
template<class t>
vi sortidx(const vc<t>&a){
	int n=si(a);
	vi idx(n);iota(all(idx),0);
	sort(all(idx),[&](int i,int j){return a[i]<a[j];});
	return idx;
}
//vs[i]=a[idx[i]]
//例えば sortidx で得た idx を使えば単にソート列になって返ってくる
//CF850C
template<class t>
vc<t> a_idx(const vc<t>&a,const vi&idx){
	int n=si(a);
	assert(si(idx)==n);
	vc<t> vs(n);
	rep(i,n)vs[i]=a[idx[i]];
	return vs;
}
//CF850C
vi invperm(const vi&p){
	int n=si(p);
	vi q(n);
	rep(i,n)q[p[i]]=i;
	return q;
}

template<class t,class s=t>
s SUM(const vc<t>&a){
	return accumulate(all(a),s(0));
}

template<class t>
t MAX(const vc<t>&a){
	return *max_element(all(a));
}

template<class t>
pair<t,int> MAXi(const vc<t>&a){
	auto itr=max_element(all(a));
	return mp(*itr,itr-a.bg);
}

template<class t>
t MIN(const vc<t>&a){
	return *min_element(all(a));
}

template<class t>
pair<t,int> MINi(const vc<t>&a){
	auto itr=min_element(all(a));
	return mp(*itr,itr-a.bg);
}

vi vid(int n){
	vi res(n);iota(all(res),0);
	return res;
}

template<class S>
void soin(S&s){
	sort(all(s));
}

template<class S,class F>
void soin(S&s,F&&f){
	sort(all(s),forward<F>(f));
}

template<class S>
S soout(S s){
	soin(s);
	return s;
}

template<class S>
void rein(S&s){
	reverse(all(s));
}

template<class S>
S reout(S s){
	rein(s);
	return s;
}

template<class t,class u>
pair<t,u>&operator+=(pair<t,u>&a,pair<t,u> b){
	a.a+=b.a;a.b+=b.b;return a;}
template<class t,class u>
pair<t,u>&operator-=(pair<t,u>&a,pair<t,u> b){
	a.a-=b.a;a.b-=b.b;return a;}
template<class t,class u>
pair<t,u> operator+(pair<t,u> a,pair<t,u> b){return mp(a.a+b.a,a.b+b.b);}
template<class t,class u>
pair<t,u> operator-(pair<t,u> a,pair<t,u> b){return mp(a.a-b.a,a.b-b.b);}

template<class t>
t gpp(vc<t>&vs){
	assert(si(vs));
	t res=move(vs.back());
	vs.pop_back();
	return res;
}

template<class t,class u>
void pb(vc<t>&a,const vc<u>&b){
	a.insert(a.ed,all(b));
}

template<class t,class...Args>
vc<t> cat(vc<t> a,Args&&...b){
	(pb(a,forward<Args>(b)),...);
	return a;
}

template<class t,class u>
vc<t>& operator+=(vc<t>&a,u x){
	for(auto&v:a)v+=x;
	return a;
}

template<class t,class u>
vc<t> operator+(vc<t> a,u x){
	return a+=x;
}

template<class t,class u>
vc<t>& operator-=(vc<t>&a,u x){
	for(auto&v:a)v-=x;
	return a;
}

template<class t,class u>
vc<t>& operator-(vc<t> a,u x){
	return a-=x;
}

template<class t,class u>
void remval(vc<t>&a,const u&v){
	a.erase(remove(all(a),v),a.ed);
}

template<class t,class u>
void fila(vc<t>&vs,const u&a){
	fill(all(vs),a);
}

template<class t,class u>
int findid(const vc<t>&vs,const u&a){
	auto itr=find(all(vs),a);
	if(itr==vs.ed)return -1;
	else return itr-vs.bg;
}

template<class t>
void rtt(vc<t>&vs,int i){
	rotate(vs.bg,vs.bg+i,vs.ed);
}

bool dbg=false;

void slv(){
	int n,s;cin>>n>>s;
    // 1 2 3
	vi a=readvi(n);
	
    // 0 1 2
    // 0 1 3 6
	vi b=presum(a);
	

	vi dp(n+1);
	per(i,n){ // 2 1 0

    	// Sum(A[i....j]) <= S
        // b[j] - b[i - 1] < = s
	    // b[j] - b[i] <= S
	    // b[j] <= b[i] + S
	    // lower_bound(b, x) is used to find the first element which does not compare less than val.
	    // what
		int j=lwb(b,b[i]+s+1)-1;
		dp[i]=dp[j]+(n-i);
        // printf("i: %d, j: %d, b[i]: %d, b[i] + s + 1 : %d, dp[i]: %d\n", i, j, b[i], b[i] + s + 1, dp[i]);
	}
	
	print(SUM(dp));
}

signed main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout<<fixed<<setprecision(20);
	
	if(dbg){
		while(1)slv();
	}else{
		//int t;cin>>t;rep(_,t)
		slv();
	}
}
