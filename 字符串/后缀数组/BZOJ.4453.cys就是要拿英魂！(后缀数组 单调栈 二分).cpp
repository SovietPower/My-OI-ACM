/*
12640kb	1028ms
https://www.cnblogs.com/SovietPower/p/10197738.html
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

struct Node
{
	int l,r,p;
}sk[N];
struct Quries
{
	int id,l,r;
	inline bool operator <(const Quries &x)const
	{
		return l<x.l;
	}
}q[N];
struct Suffix_Array
{
	int tm[N],rk[N],sa[N],sa2[N],ht[N],Log[N],st[N][17];
	char s[N];

	inline void Init_ST(const int n)
	{
		for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
		for(int i=1; i<=n; ++i) st[i][0]=ht[i];
		for(int j=1; j<=Log[n]; ++j)
			for(int t=1<<j-1,i=n-t; i; --i)
				st[i][j]=std::min(st[i][j-1],st[i+t][j-1]);
	}
	inline int LCP(int l,int r)
	{
		l=rk[l], r=rk[r]; if(l>r) std::swap(l,r);
		++l;
		int k=Log[r-l+1];
		return std::min(st[l][k],st[r-(1<<k)+1][k]);
	}
	int Build()
	{
		scanf("%s",s+1);
		const int n=strlen(s+1);
		int *x=rk,*y=sa2,m=300;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[i]]--]=i;
		for(int k=1,p=0; k<n; k<<=1,m=p,p=0)
		{
			for(int i=n-k+1; i<=n; ++i) y[++p]=i;
			for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

			for(int i=0; i<=m; ++i) tm[i]=0;
			for(int i=1; i<=n; ++i) ++tm[x[i]];
			for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
			for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

			std::swap(x,y), x[sa[1]]=p=1;
			for(int i=2; i<=n; ++i)
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
			if(p>=n) break;
		}
		for(int i=1; i<=n; ++i) rk[sa[i]]=i;
		ht[1]=0;
		for(int i=1,k=0,p; i<=n; ++i)
		{
			if(rk[i]==1) continue;
			if(k) --k;
			p=sa[rk[i]-1];
			while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
			ht[rk[i]]=k;
		}
		Init_ST(n);
		return n;
	}
}sa;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool Check(int i,int j,int r)
{
	return sa.rk[i]>sa.rk[j]||sa.LCP(i,j)>=r-j+1;
}

int main()
{
	static int Ans[N];
	const int n=sa.Build(),Q=read();
	for(int i=1; i<=Q; ++i) q[i]=(Quries){i,read(),read()};
	std::sort(q+1,q+1+Q); q[0].l=0, sk[0].l=n+1;
	int top=1,now=Q; sk[1]=(Node){n,n,n};
	while(q[now].l==n) Ans[q[now--].id]=n;
	for(int i=n-1; i; --i)
	{
		bool f=0;
		while(top)
		{
			if(Check(i,sk[top].p,sk[top].r)) --top;
			else if(Check(i,sk[top].p,sk[top].l)) {f=1; break;}
			else break;
		}
		if(f)
		{
//			int j=sk[top].p,l=sk[top].l,r=sk[top].r,mid;
//			while(l<r)
//			{
//				if(Check(i,j,mid=l+r>>1)) l=mid+1;
//				else r=mid;
//			}
//			sk[top].l=l;
			sk[top].l=sk[top].p+sa.LCP(i,sk[top].p);//这里不需要二分。。=-= 
		}
		sk[++top]=(Node){i,sk[top-1].l-1,i};
		while(q[now].l==i)
		{
			int p=q[now].r,l=1,r=top,mid;
			while(l<=r)
			{
				mid=l+r>>1;
				if(p>=sk[mid].l && p<=sk[mid].r) break;
				else if(p>sk[mid].r) r=mid-1;
				else l=mid+1;
			}
			Ans[q[now--].id]=sk[mid].p;
		}
	}
	for(int i=1; i<=Q; printf("%d\n",Ans[i++]));

	return 0;
}
