/*
860K	125MS
$Description$
给定一段数字序列(Ai∈[1,88])，求最长的两个子序列满足： 
1.长度至少为5 
2.一个子序列可以通过全部加或减同一个数来变成另一个子序列 
3.两个子序列没有重叠部分 
$Solution$
求不重叠最长重复子序列:  
首先二分k，判断是否存在长度为k的不重叠的相同子序列 
把排序后的后缀按ht分组，每组中后缀的ht>=k，这样满足相同序列长度至少为k的两个后缀一定在同一组中(且同一组中任意两个都满足) 
然后在每组中判断是否有max{sa[]}-min{sa[]}>=k，这样可以满足没有重叠部分。若有一组满足，则存在。

对于要求2，其实可以看做两个子序列相邻两项差值都相等，如1,2,4,6与4,5,7,9，相邻两项差值的序列都为1,2,2，那么可以满足条件 
原序列转化为差值序列，长度最后时要+1 
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e4+5,MAX=88;

int n,sa[N],ht[N],rk[N],sa2[N],A[N],tm[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Get_SA()
{
	int *x=rk,*y=sa2,m=200;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=A[i]];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i) sa[tm[x[i]]--]=i;
	for(int p=0,k=1; k<n; k<<=1,m=p,p=0)
	{
		for(int i=n-k+1; i<=n; ++i) y[++p]=i;
		for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

		std::swap(x,y), p=x[sa[1]]=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p:++p;
		if(p>=n) break;
	}
}
void Get_ht()
{
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int k=0,p,i=1; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n&&p+k<=n&&A[i+k]==A[p+k]) ++k;
		ht[rk[i]]=k;
	}
	
}
bool Check(int k)
{
	int mx=sa[1],mn=sa[1];
	for(int i=2; i<=n; ++i)
		if(ht[i]>=k) mx=std::max(mx,sa[i]),mn=std::min(mn,sa[i]);
		else if(mx-mn>=k) return 1;
		else mn=mx=sa[i];
	return mx-mn>=k;
}
int Solve()
{
	int l=4,r=n,mid,res=-1;
	while(l<r)
		if(Check(mid=l+r>>1)) res=mid,l=mid+1;
		else r=mid;
	return res+1;
}

int main()
{
	while(n=read(),n)
	{
		for(int i=1; i<=n; ++i) A[i]=read();
		--n;
		for(int i=1; i<=n; ++i) A[i]=A[i+1]-A[i]+MAX;
		Get_SA(), Get_ht();
		printf("%d\n",Solve());
	}
	return 0;
}
