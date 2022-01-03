/*
13228kb	1000ms
后缀数组是可以做的: 本质不同的字符串的个数为 $子串个数-\sum_{ht[i]}$，即 $\frac{n(n+1)}{2}-\sum_{ht[i]}$.
如果是每次往后边插入字符，会改变SA[]。但如果向前边插入字符，相当于只加入了一个后缀。
所以离线，把原串反过来。
每次插入一个字符，即新增一个前缀i，它的贡献是$len-max(lcp(pre,i),lcp(i,nxt))$，其中$pre,nxt$为与后缀$i$(当前)排名相邻的两个串。
用set维护当前的排名，RMQ求lcp。（懒得写$O(n)$的维护单调栈正反跑两遍）
做了几道后缀数组了，竟然真没写过lcp(~~也许是太简单了~~)。
$10^5$很容易爆int!
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5,B=17;

int n,cnt,A[N],ref[N],tm[N],sa[N],sa2[N],rk[N],ht[N],log2[N],st[N][18];
std::set<int> set_rk;
std::set<int>::iterator it;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
void Get_SA()
{
	int *x=rk,*y=sa2,m=n+1;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=A[i]];
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
	for(int k=0,p,i=1; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n && p+k<=n && A[i+k]==A[p+k]) ++k;
		ht[rk[i]]=k;
	}
}
void Init_RMQ()
{
	for(int i=1; i<=n; ++i) st[i][0]=ht[i];
	log2[1]=0;
	for(int i=2; i<=n; ++i) log2[i]=log2[i>>1]+1;
	for(int j=1; j<=log2[n]; ++j)
		for(int i=n-(1<<j-1); i; --i)
			st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int LCP(int l,int r)
{
	if(l>r) std::swap(l,r);
	++l; int k=log2[r-l+1];
	return std::min(st[l][k],st[r-(1<<k)+1][k]);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);
//	for(int i=1,lim=n>>1; i<=lim; ++i) std::swap(A[i],A[n-i+1]);//惊了 竟然写错了 还是写reverse吧  
	std::reverse(A+1,A+1+n);//reverse好像快不少？ 差不多。
	Get_SA(), Init_RMQ();
	long long res=0;
	set_rk.insert(0);
	for(int tmp,i=n; i; --i)//从头开始加入字符(前缀)。
	{
		tmp=0, it=set_rk.upper_bound(rk[i]);
		if(it!=set_rk.end()) tmp=LCP(rk[i],*it);
		if((--it)!=set_rk.begin()) tmp=std::max(tmp,LCP(*it,rk[i]));
		res+=n-i+1-tmp, set_rk.insert(rk[i]);
		printf("%lld\n",res);
	}

	return 0;
}
