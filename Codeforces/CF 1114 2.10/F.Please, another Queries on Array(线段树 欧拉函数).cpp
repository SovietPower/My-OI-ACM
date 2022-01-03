/*
1809ms	42100KB
$Description$
给定长为$n$的序列$A_i$，要求支持两种操作：
1. $l,r,v$，区间$[l,r]$乘一个数$v$；
2. $l,r$，输出$\varphi(\prod_{i=l}^rA_i)$。
$n\leq4\times10^5,\ q\leq2\times10^5,\ A_i,v\leq300$。

$Solution$
听旁边dalao讨论好像特别可做，扔掉E看F。
忘了欧拉函数怎么求。。去百度百科看了下，发现这不是线段树裸题吗。。
![来自百度百科](https://img2018.cnblogs.com/blog/1143196/201902/1143196-20190211124850298-1331995463.png)
设$\prod_{i=l}^rA_i=n=\prod_{i=1}^kp_i^{a_i}$，那$\varphi(n)=\prod_{i=1}^kp_i^{a_i}\frac{p_i-1}{p_i}=n\prod_{i=1}^k\frac{p_i-1}{p_i}$。
$k$是$300$以内质数个数，就是$62$。所以我们维护一个区间乘积、区间某个质因子是否出现过就完了。
后者可以用`bitset`维护，或者因为只有$62$个用`long long`也行。
复杂度$O(q(\log^2n+62))$（区间乘积竟然第一次写...要快速幂所以多个$\log$。但是其实有方法可以省掉快速幂）。
*/
#include <cstdio>
#include <cctype>
#include <bitset>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
typedef long long LL;
const int N=4e5+5,M=301,LIM=62;
const int P[LIM]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293};
const int ref[M]={0,0,0,1,0,2,0,3,0,0,0,4,0,5,0,0,0,6,0,7,0,0,0,8,0,0,0,0,0,9,0,10,0,0,0,0,0,11,0,0,0,12,0,13,0,0,0,14,0,0,0,0,0,15,0,0,0,0,0,16,0,17,0,0,0,0,0,18,0,0,0,19,0,20,0,0,0,0,0,21,0,0,0,22,0,0,0,0,0,23,0,0,0,0,0,0,0,24,0,0,0,25,0,26,0,0,0,27,0,28,0,0,0,29,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,31,0,0,0,0,0,32,0,33,0,0,0,0,0,0,0,0,0,34,0,35,0,0,0,0,0,36,0,0,0,0,0,37,0,0,0,38,0,0,0,0,0,39,0,0,0,0,0,40,0,41,0,0,0,0,0,0,0,0,0,42,0,43,0,0,0,44,0,45,0,0,0,0,0,0,0,0,0,0,0,46,0,0,0,0,0,0,0,0,0,0,0,47,0,0,0,48,0,49,0,0,0,50,0,0,0,0,0,51,0,52,0,0,0,0,0,0,0,0,0,53,0,0,0,0,0,54,0,0,0,0,0,55,0,0,0,0,0,56,0,57,0,0,0,0,0,58,0,0,0,59,0,60,0,0,0,0,0,0,0,0,0,61};
//为什么const之后慢了不少= = 

inline int read();
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int val[S],tag[S];
	LL now,Ans,f[S],tagf[S];
	#undef S
	#define Upd(rt,v,l,vf) val[rt]=1ll*val[rt]*FP(v,l)%mod, tag[rt]=1ll*tag[rt]*v%mod, f[rt]|=vf, tagf[rt]|=vf
	#define Update(rt) f[rt]=f[ls]|f[rs], val[rt]=1ll*val[ls]*val[rs]%mod
	inline int FP(int x,int k)
	{
		int t=1;
		for(; k; k>>=1,x=1ll*x*x%mod)
			if(k&1) t=1ll*t*x%mod;
		return t;
	}
	void Build(int l,int r,int rt)
	{
		tag[rt]=1;
		if(l==r)
		{
			int v=read(); val[rt]=v;
			for(int i=0; i<LIM&&P[i]*P[i]<=v; ++i)
				if(!(v%P[i]))
				{
					f[rt]|=1ll<<i, v/=P[i];//1ll!!!
					while(!(v%P[i])) v/=P[i];
				}
			if(v!=1) f[rt]|=1ll<<ref[v];
			return;
		}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(rt);
	}
	inline void PushDown(int rt,int m)
	{
		int l=ls,r=rs;
		Upd(l,tag[rt],m-(m>>1),tagf[rt]), Upd(r,tag[rt],m>>1,tagf[rt]), tag[rt]=1, tagf[rt]=0;
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R)
		{
			Upd(rt,v,r-l+1,now);
			return;
		}
		if(tag[rt]!=1) PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return Ans|=f[rt],val[rt];
		if(tag[rt]!=1) PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return 1ll*Query(lson,L,R)*Query(rson,L,R)%mod;
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
//void Init(int n)
//{
//	static int P[N];
//	static bool notP[M];
//	for(int i=2,cnt=0; i<=n; ++i)
//	{
//		if(!notP[i]) ref[i]=cnt, P[cnt++]=i;
//		for(int j=0; j<cnt && i*P[j]<=n; ++j)
//		{
//			notP[i*P[j]]=1;
//			if(!(i%P[j])) break;
//		}
//	}
//}
inline char GetOpt()
{
	register char c;
	while(!isalpha(c=gc()));
	return c;
}

int main()
{
	static int inv[N],coef[N];
//	Init(M-1);
	inv[1]=1;
	for(int i=2; i<M; ++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=0; i<LIM; ++i) coef[i]=1ll*(P[i]-1)*inv[P[i]]%mod;

	int n=read(),q=read();
	T.Build(1,n,1);
	while(q--)
	{
		if(GetOpt()=='T')
		{
			T.Ans=0;
			int l=read(),r=read(),val=T.Query(1,n,1,l,r);
			for(int i=0; i<LIM; ++i)
				if(T.Ans>>i&1) val=1ll*val*coef[i]%mod;
			printf("%d\n",val);
		}
		else
		{
			int l=read(),r=read(),x=read(),v=x;
			LL now=0;
			for(int i=0; i<LIM&&P[i]*P[i]<=v; ++i)
				if(!(v%P[i]))
				{
					now|=1ll<<i, v/=P[i];
					while(!(v%P[i])) v/=P[i];
				}
			if(v!=1) now|=1ll<<ref[v];
			T.now=now, T.Modify(1,n,1,l,r,x);
		}
	}
	return 0;
}
