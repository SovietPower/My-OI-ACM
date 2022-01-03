/*
5892kb	784ms
令$st[i]$表示以$i$为开头有多少个$AA$这样的子串，$ed[i]$表示以$i$结尾有多少个$AA$这样的子串。那么$Ans=\sum_{i=1}^{n-1}ed[i]*st[i+1]$。
考虑如何求$st[i],ed[i]$。暴力的话可以枚举$i$，然后哈希判一下。这样$O(n^2)$就有$95$分了。。
正解是，枚举长度$len$，判断每个位置是否存在长为$2*len$的$AA$这样的子串。
每隔$len$的距离放一个关键点，这样一个长度为$2*len$的串一定会经过两个相邻的关键点。
考虑枚举两个相邻的关键点，即令$i=k*len,\ j=i+len$。再令$x$表示$i,j$所代表的前缀的最长公共后缀（与$len$取$\min$），$y$表示$i,j$所代表的后缀的最长公共前缀（与$len$取$\min$）。
（不想画图了，注意别看错，可以拿个串比如`aabaabab`试一下）
当$x+y-1<len$时，因为中间没有相同的部分所以找不到一个经过$i,j$长为$2*len$的$AA$串。
当$x+y-1\geq len$时，我们发现因为$i,j$是两个相距为$len$的点，我们取$i-x+len,\ j-x+len$，这两个点之间能形成长$2*len$的$AA$子串。同时将两个点不断向右移动，直到$i+y-1,\ j+y-1$，都能形成一个$AA$子串。
也就是当$p$取$[j-x+len,\ j+y-1]$中的某个位置时，都能得到以$p$为结尾的长为$2*len$的$AA$串。同理当$p$在$[i-x+1,\ i+y-len]$中时，也都能得到以$p$开头的长为$2*len$的$AA$串。
所以就是区间加一，差分一下就可以了。
只是枚举$len$，然后每隔$len$放一个点，统计相邻两点间的贡献。所以复杂度还是$O(n\log n)$。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int N=3e4+5;

int Log[N];
struct Suffix_Array
{
	int tm[N],sa[N],sa2[N],rk[N],ht[N],st[N][15];

	inline void Init_ST(const int n)
	{
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
	void Build(char *s,const int n)
	{
		memset(rk,0,sizeof rk);
		memset(sa2,0,sizeof sa2);//要清空...! 因为下面比较懒得加<=n了。
		int m=26,*x=rk,*y=sa2;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]=s[i]-'a'+1];
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
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;//because of this
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
	}
}sa1,sa2;

inline void Init_Log(const int n)
{
	for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
}
void Solve()
{
	static int st[N],ed[N];
	static char s[N];
	scanf("%s",s+1); const int n=strlen(s+1);
	sa1.Build(s,n), std::reverse(s+1,s+1+n), sa2.Build(s,n);

	memset(st,0,n+1<<2), memset(ed,0,n+1<<2);
	for(int len=1,lim=n>>1; len<=lim; ++len)
		for(int i=len,j=len<<1; j<=n; i=j,j+=len)
		{
			int x=std::min(len,sa2.LCP(n-i+1,n-j+1)),y=std::min(len,sa1.LCP(i,j));
			if(x+y-1>=len)
				++st[i-x+1], --st[i+y-len+1], ++ed[j-x+len], --ed[j+y];
		}
	LL ans=0;
	for(int i=1; i<n; ++i) st[i+1]+=st[i], ed[i+1]+=ed[i], ans+=1ll*ed[i]*st[i+1];
	printf("%lld\n",ans);
}

int main()
{
	Init_Log(30000);
	int T; scanf("%d",&T);
	while(T--) Solve();
	return 0;
}
