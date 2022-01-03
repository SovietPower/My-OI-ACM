//2924kb	3464ms
//http://www.cnblogs.com/SovietPower/p/8716998.html
#include <cstdio>
#include <cctype>
#include <algorithm>
#define lb(x) (x)&-(x)
#define gc() getchar()
#define pr std::pair<int,int>
const int N=1e5+5,M=2e4+5,INF=0x7fffffff;

int Q,Max,cnt,P[N>>3],mu[N],Ans[M];
std::pair<int,int> F[N];
bool Not_P[N];
struct Ques{
	int n,m,a,id;
	bool operator <(const Ques x)const{
		return a<x.a;
	}
}q[M];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Init()
{
	mu[1]=1;
	for(int i=2; i<=Max; ++i)
	{
		if(!Not_P[i]) P[++cnt]=i,mu[i]=-1;//mu[]别漏！
		for(int t,j=1; j<=cnt&&(t=i*P[j])<=Max; ++j)
		{
			Not_P[t]=1;
			if(i%P[j]) mu[t]=-mu[i];
			else {mu[t]=0; break;}
		}
	}
	for(int i=1; i<=Max; ++i)
		for(int j=i; j<=Max; j+=i) F[j].first+=i;
	for(int i=1; i<=Max; ++i) F[i].second=i;
	std::sort(F+1,F+1+Max);
}
namespace BIT
{
	int t[N+3];
	inline void Add(int p,int v){
		while(p<=Max) t[p]+=v,p+=lb(p);
	}
	inline int Query(int p){
		int res=0;
		while(p) res+=t[p],p^=lb(p);
		return res;
	}
	inline int Sum(int l,int r){
		return Query(r)-Query(l-1);
	}
}
int Calc(int n,int m)
{
//	if(n>m) std::swap(n,m);
	int res=0;
	for(int i=1,nxt; i<=n; i=nxt+1)
		nxt=std::min(n/(n/i),m/(m/i)),res+=(n/i)*(m/i)*BIT::Sum(i,nxt);//这不需要*(nxt-i+1)！BIT::Sum就是区间的值。
	return res;
}

int main()
{
	Q=read();
	for(int n,m,i=1; i<=Q; ++i)
	{
		n=read(),m=read(),q[i].a=read(),q[i].id=i;
		if(n>m) std::swap(n,m);
		q[i].n=n, q[i].m=m, Max=std::max(Max,m);
	}
	std::sort(q+1,q+1+Q);
	Init();
	int now=1; F[Max+1].second=INF;
	for(int i=1; i<=Q; ++i){
		for(; F[now].first<=q[i].a; ++now)
			for(int v=0,d=1; (v+=F[now].second)<=Max; ++d)
				BIT::Add(v,F[now].first*mu[d]);
		Ans[q[i].id]=Calc(q[i].n,q[i].m);
	}
	for(int i=1; i<=Q; ++i) printf("%d\n",Ans[i]&INF);

	return 0;
}
