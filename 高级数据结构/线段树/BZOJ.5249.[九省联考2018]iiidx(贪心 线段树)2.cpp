/*
28656kb	4280ms
��С����ö��ÿ��λ��$x$������Ҫ��һ�����������$v$��������ڵ���$v$��û�б��ù�����������$sz[x]$����
�������λ��$x$�������ҵ������$v$�����Ǵ��ڵ���$v$�������ܲ�ֻ��$sz[x]$���������ǲ�֪��Ҫѡ����$sz[x]$����

���������Ӵ�С����ÿ��λ��$i$ά����������߻�����ѡ������$A_i$����ʼ$A_i=i$����
����λ��$x$�ҵ����ʵ���$v$ʱ��$v$��ߵ�������Щ��ȷ������$v$��$v$�ұߵ�������߱��õ���$sz[x]$����ȷ���ģ����Ը�$A_v\sim A_{d_n}$������$sz[x]$��
����������$v$������߻������õ����ĸ�������$\min\{A_v,A_{v+1},...,A_{d_n}\}$.
�����Ϳ������߶����϶������ʺ�$x$��$v$�ˡ��������������������Сֵ$<sz[x]$��˵�������䲻���㣬��������϶�Ҳ�����㣬�ݹ鵽�����䣻�������$\geq sz[x]$����������У�������Ҫ�ݹ鵽�����俴���Ƿ���У�������о�ֱ�ӷ�������������ĵ�һ��λ�á�

ö�ٵ�һ����$x$ʱ��������и��ף���Ҫ��������$fa[x]$Ϊ��Щ����Ԥ����ֵɾ������Ϊ֮ǰ����Ϊ�˸���Щ�������ռ䰡��ö�ٵ���Щ������ʱ��ȻҪ��֮ǰռ��λ�ÿճ����ˣ���Ȼ���Ҹ����ʵ�λ�ø�$x$����Ԥ��$sz[x]$�Ĵ�С����ע��ÿ��ֵ��ɾ�˶�Σ�
�����һЩ��ͬ����$v$����ѡ����Ȼ���ڰ����ұߵ��Ǹ�$v$�ŵ���ǰλ�ø��š�Ҳ���Ƕ�����ͬ����Ҫ�����������η֡�

���Ӷ�$O(n\log n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define eps 1e-9
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int mn[S],tag[S];
	#undef S
	#define Upd(rt,v) mn[rt]+=v, tag[rt]+=v
	#define Update(rt) mn[rt]=std::min(mn[ls],mn[rs])
	inline void PushDown(int rt)
	{
		Upd(ls,tag[rt]), Upd(rs,tag[rt]), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		mn[rt]=l;
		if(l!=r)
		{
			int m=l+r>>1;
			Build(lson), Build(rson);
		}
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(p<=l) {Upd(rt,v); return;}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		Modify(rson,p,v);
		if(p<=m) Modify(lson,p,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int k)
	{
		while(l!=r)
		{
			if(tag[rt]) PushDown(rt);
			int m=l+r>>1;
			mn[rs]>=k ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return mn[rt]>=k?l:l+1;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline double readdb()
{
	double x=0,y=0.1;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);x=x*10+c-48,c=gc());
	for(c=='.'&&(c=gc());isdigit(c);x+=y*(c-48),y*=0.1,c=gc());
	return x;
}

int main()
{
	static int A[N],Ans[N],sz[N],fa[N],R[N],cnt[N];
	const int n=read(); const double K=readdb();
	for(int i=1; i<=n; ++i) A[i]=read(), sz[i]=1;
	std::sort(A+1,A+1+n,std::greater<int>());
	T.Build(1,n,1);
	for(int i=n; i; --i) sz[fa[i]=(int)(i/K+eps)]+=sz[i], R[i]=A[i]==A[i+1]?R[i+1]:i;
	for(int i=1; i<=n; ++i)
	{
		if(fa[i] && fa[i]!=fa[i-1]) T.Modify(1,n,1,Ans[fa[i]],sz[fa[i]]-1);
		int p=T.Query(1,n,1,sz[i]);
		p=R[p], ++cnt[p], p-=(cnt[p]-1), Ans[i]=p;
		T.Modify(1,n,1,p,-sz[i]);
	}
	for(int i=1; i<=n; ++i) printf("%d ",A[Ans[i]]);

	return 0;
}
