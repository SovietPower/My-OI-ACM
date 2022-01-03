/*
10296kb	3476ms
$Description$
给定两个串$S,T$以及一个数$k$，求$T$中有多少个子串，满足和$S$的编辑距离不超过$k$。
$|S|+|T|\leq10^5,\ k\leq 5$。

$Solution$
考虑枚举$T$的每个后缀$i$~~（注意后缀是指啥= =）~~，求后缀$i$中有哪些前缀满足条件。
怎么处理编辑距离呢？$k$很小，直接搜。
设$S,T$分别匹配到$x,y$位置，可以用$SA$求$LCP(x,y)$，然后直接跳到下一个不匹配位置。
如果$S_x\neq T_y$，那么有三种选择：删掉$T_y\to x,y+1$，在$T_y$前插入一个$S_x\to x+1,y$，把$T_y$替换成$S_x\to x+1,y+1$。
所以$DFS$的复杂度是$3^k$的。
匹配完$S$串后，如果还剩下一些可用编辑距离$rest$，显然此时前缀$[y-rest,y+rest]$都满足条件，差分一下即可。注意这些前缀不要算重（一个位置只能算一次）。

复杂度$O(n\log n+n3^k)$。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=1e5+7;

int na,nb,Now,L,R,sum[N];
char s[N];
struct Suffix_Array
{
	int sa[N],sa2[N],rk[N],tm[N],ht[N],Log[N],st[17][N];
	inline int LCP(int l,int r)
	{
		l=rk[l], r=rk[r]; if(l>r) std::swap(l,r);
		++l; int k=Log[r-l+1];
		return std::min(st[k][l],st[k][r-(1<<k)+1]);
	}
	void Build(const char *s,const int n)
	{
		int m=27,*x=rk,*y=sa2;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'A'+1];
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
		for(int i=1,k=0; i<=n; ++i)
		{
			if(rk[i]==1) continue;
			if(k) --k;
			int p=sa[rk[i]-1];
			while(i+k<=n && p+k<=n && s[i+k]==s[p+k]) ++k;
			ht[rk[i]]=k;
		}
		st[0][1]=ht[1];
		for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1, st[0][i]=ht[i];
		for(int j=1; j<=Log[n]; ++j)
			for(int t=1<<j-1,i=n-t; i; --i)
				st[j][i]=std::min(st[j-1][i],st[j-1][i+t]);
	}
}sa;

inline void Upd(int l,int r)
{
	l=std::max(l,Now), r=std::min(r,nb), L=std::min(l,L), R=std::max(r+1,R);
	++sum[l], --sum[r+1];//注意可行前缀位置的限制（在Now~nb内）
}
void DFS(int x,int y,int rest)
{
	int t=sa.LCP(x,y+na+1);
	x+=t, y+=t;
	if(x>na||y>nb)
	{
		int d=rest-(na-x+1);
		if(d>=0) Upd(y-1-d,y-1+d);
		return;
	}
	if(rest) --rest, DFS(x+1,y,rest), DFS(x,y+1,rest), DFS(x+1,y+1,rest);
}

int main()
{
	int K; scanf("%d%s",&K,s+1);
	na=strlen(s+1), s[na+1]='[';
	scanf("%s",s+na+2), nb=strlen(s+na+2);
	const int n=na+nb+1; sa.Build(s,n);
	int ans=0;
	for(int i=1,delta=std::max(0,na-K); i+delta<=nb; ++i)
	{
		Now=i, L=N, R=0, DFS(1,i,K);
		for(int j=L; j<=R; ++j) ans+=(sum[j]+=sum[j-1])>0;
		for(int j=L; j<=R; ++j) sum[j]=0;
	}
	printf("%d\n",ans);

	return 0;
}
