/*
1144ms	486.4MB
$Description$
给定长为$n$的序列$A_i$，两种操作：
1. 将某个数$A_i$修改为$v$。
2. 查询用区间$[l,r]$内的数不能组成的最小的数（能组成$v$是指存在一个$[l,r]$的子集$s$使$s$的和等于$v$）。
$n,A_i\leq 2\times10^5$。
$Solution$
[BZOJ(CodeChef)原题树套树版]？/whl
先考虑询问。设区间$[l,r]$内已经可以组成的数为$[1,v]$，$[l,r]$中最小的大于$v$的数为$mx$，若$mx>v+1$则区间的答案即为$v+1$；否则$mx=v+1$，$v$可以更新为$Sum(1,v+1)$（$[l,r]$中值在$[1,v+1]$的所有数的和），继续重复上述过程。
求$mx$的时候可以求$Sum(1,v+1)$，若$Sum=mx$则显然$mx>v+1$；否则$mx=v+1$。
容易发现$v$每次至少增加$v+1$，且这个过程可以用主席树实现。所以查询复杂度为$O(\log V\log n)$。
对于修改，改成[带修改主席树（树状数组套主席树）]或树状数组套线段树就可以了。复杂度$O(n\log V\log^2n)$。
这个带修改主席树，用线段树写每个位置维护一个前缀和即可，查询是单点查询。（不太懂他们麻烦的写法/whl）
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=2e5+5,V=2e5;

int A[N];
struct President_Tree
{
	#define S N*155//N*18*18*2 //注意MLE。。
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	int tot,son[S][2];
	LL pre[S];
	#define R(x) (rs?rs:(rs=++tot))
	void Insert(int &x,int l,int r,int p)
	{
		!x&&(x=++tot);
		if(l==r) {pre[x]+=l; return;}
		int m=l+r>>1; p<=m?(pre[R(x)]+=p,Insert(lson,p)):Insert(rson,p);
	}
	void Delete(int &x,int l,int r,int p)
	{
//		!x&&(x=++tot);
		if(l==r) {pre[x]-=l; return;}
		int m=l+r>>1; p<=m?(pre[R(x)]-=p,Delete(lson,p)):Delete(rson,p);
	}
	LL Query(int x,int l,int r,int p)
	{
		if(!x) return 0;
		if(l==r) return pre[x];
		int m=l+r>>1; return pre[x]+(p<=m?Query(lson,p):Query(rson,p));
	}
};
struct BIT
{
	President_Tree T;
	int n,root[N];
	std::vector<int> vl,vr;
	#define lb(x) (x&-(x))
	void Modify(int p,int a,int v)
	{
		for(; p<=n; p+=lb(p))
		{
			if(a) T.Delete(root[p],1,V,a);
			T.Insert(root[p],1,V,v);
		}
	}
	void Query0(int l,int r)
	{
		vl.clear(), vr.clear();
		for(int p=r; p; p^=lb(p)) vr.emplace_back(p);
		for(int p=l-1; p; p^=lb(p)) vl.emplace_back(p);		
	}
	LL Query(int v)
	{
		LL res=0;
		for(auto p:vr) res+=T.Query(root[p],1,V,v);
		for(auto p:vl) res-=T.Query(root[p],1,V,v);
		return res;
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	int n=read(),Q=read(); T.n=n;
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) T.Modify(i,0,A[i]);
	for(int p,v; Q--; )
	{
		if(read()==1) p=read(),v=read(),T.Modify(p,A[p],v),A[p]=v;
		else
		{
			LL v=0; int l=read(),r=read(); T.Query0(l,r);//树状数组节点可以先求出来 
			while(1)
			{
				LL s=T.Query((int)std::min(LL(V),v+1));//不需要离散化 
				if(s==v) break;
				v=s;
			}
			printf("%lld\n",v+1);
		}
	}

	return 0;
}
