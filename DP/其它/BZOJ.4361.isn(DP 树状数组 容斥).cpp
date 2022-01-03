/*
32268kb	1256ms
����Ϊ$i$�Ĳ��������и����ǿ���DP��ġ�
��$f[i][j]$��ʾ����Ϊ$i$����βԪ��Ϊ$a_j$�Ĳ��������и�����ת��Ϊ$f[i][j]=\sum f[i-1][k]$������$k$����$k<j$��$a_k\leq a_j$����������״����$O(n^2\log n)$�����
��ô����ΪΪ$i$�Ĳ��������и���$sum[i]=\sum_{j=i}^nf[i][j]$��
�Ƚ��鷳���ǵõ��������к������ֹͣ���������û��������ƣ��𰸾���$\sum_{i=1}^nsum[i]\times (n-i)!$��
���Ǻܼ򵥵��ǣ������Ϊ$i$�Ĳ�������������һ���������м���ɾ���õ��ģ������Ϸ��ķ���������ô�������������$sum[i+1]\times (i+1)\times (n-i+1)!$��
��ÿ��$i$�������Ϸ������Ĺ��׾Ϳ����ˣ���$Ans=\sum_{i=1}^nsum[i]\times (n-i)!-sum[i+1]\times (i+1)\times (n-i+1)!$��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod 1000000007
#define Mod(x) x>=mod&&(x-=mod)
typedef long long LL;
const int N=2005;

int fac[N],A[N],ref[N],f[N][N],g[N];
struct Bit
{
	int n,t[N];
	#define lb(x) (x&-x)
	inline void Add(int p,int v)
	{
		for(; p<=n; p+=lb(p)) t[p]+=v, Mod(t[p]);
	}
	inline int Query(int p)
	{
		LL res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res%mod;
	}
}T[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}

int main()
{
	int n=read(),mx=0;
	fac[0]=fac[1]=1;
	for(int i=2; i<=n; ++i) fac[i]=1ll*fac[i-1]*i%mod;

	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	std::sort(ref+1,ref+1+n); int cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) mx=std::max(mx,A[i]=Find(A[i],cnt));

	for(int i=1; i<=n; ++i) f[1][i]=1;
	for(int i=2; i<=n; ++i)
	{
		T[i-1].n=mx, T[i-1].Add(A[i-1],f[i-1][i-1]);
		for(int j=i; j<=n; ++j)
			f[i][j]=T[i-1].Query(A[j]), T[i-1].Add(A[j],f[i-1][j]);
	}
	for(int i=1; i<=n; ++i)
	{
		LL sum=0;
		for(int j=i; j<=n; ++j) sum+=f[i][j];
		g[i]=1ll*sum%mod*fac[n-i]%mod;
	}
	LL ans=0;
	for(int i=1; i<=n; ++i) ans+=g[i]-1ll*g[i+1]*(i+1)%mod;
	printf("%lld\n",(ans%mod+mod)%mod);

	return 0;
}
